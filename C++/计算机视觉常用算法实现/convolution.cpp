#include"head1.h"

// 1、二维卷积函数
// 输入:
//   input: 输入矩阵 (height x width)
//   kernel: 卷积核 (k_height x k_width)
//   stride: 步长 (默认 1)
//   padding: 边界填充 (默认 0)，padding 等于多少就在输入矩阵外围添加多少层 0
// 输出: 卷积结果矩阵
vector<vector<float>>convolu2D(
	const vector<vector<float>>& input,
	const vector<vector<float>>& kernel,
	int stride = 1,
	int padding = 0) // stride 和 padding 是默认参数，默认值只能在声明或定义中标明，不能同时标
{
	// 验证输入的合法性
	if (input.empty() || input[0].empty())
		throw invalid_argument("input can not be empty");
	if (kernel.empty() || kernel[0].empty())
		throw invalid_argument("kernel can not be empty");
	if (stride < 0 || padding < 0)
		throw invalid_argument("stride and padding can not be negative");

	// 输入尺寸
	int in_height = input.size();
	int in_width = input[0].size();

	// 卷积核尺寸。一般是方阵
	int k_height = kernel.size();
	int k_width = kernel[0].size();

	// 计算经过卷积后应该输出的大小。公式：(n + 2p - k)/stride + 1
	int out_height = (in_height + 2 * padding - k_height) / stride + 1;
	int out_width = (in_width + 2 * padding - k_width) / stride + 1;

	// 创建输出矩阵，先全部初始化为 0
	vector<vector<float>>output(out_height, vector<float>(out_width, 0));

	// 给输入矩阵添加 padding ，padding 等于多少就在输入矩阵外围添加多少层 0，
	// 即 长和宽都要加上 2*padding
	// padding 默认值为 0
	vector<vector<float>>padded_input(in_height + 2 * padding,
		vector<float>(in_width + 2 * padding, 0));
	for (int i = 0; i < in_height; ++i)
	{
		for (int j = 0; j < in_width; ++j)
		{
			padded_input[i + padding][j + padding] = input[i][j];
		}
	}

	// 执行卷积运算
	for (int i = 0; i < out_height; ++i)
	{
		for (int j = 0; j < out_width; ++j)
		{
			float sum = 0.0;
			for (int m = 0; m < k_height; ++m)
			{
				for (int n = 0; n < k_width; ++n)
				{
					int x = i * stride + m;
					int y = j * stride + n;
					sum += padded_input[x][y] * kernel[m][n];
				}
			}
			output[i][j] = sum;
		}
	}
	return output;
}

// 2、三维卷积函数
vector<vector<vector<float>>>convolu3D(
	const vector<vector<vector<float>>>& input,
	const vector<vector<vector<float>>>& kernel,
	const vector<int>& stride = { 1,1,1 },
	const vector<int>& padding = { 0,0,0 })
{
	// 验证输入有效性
	if (input.empty() || input[0].empty() || input[0][0].empty())
		throw invalid_argument("Input tensor must be 3D");
	if (kernel.empty() || kernel[0].empty() || kernel[0][0].empty())
		throw invalid_argument("Input tensor must be 3D");

	// 获取输入尺寸 [depth, height, width]
	const int in_depth = input.size();
	const int in_height = input[0].size();
	const int in_width = input[0][0].size();

	// 获取卷积核尺寸 [k_depth, k_height, k_width]
	const int k_depth = kernel.size();
	const int k_height = kernel[0].size();
	const int k_width = kernel[0][0].size();

	// 验证卷积核与输入深度是否匹配
	if (k_depth > in_depth + 2 * padding[0])
		throw invalid_argument("Kernel depth exceeds padded input depth");

	// 参数验证。步长 stride 和填充 padding 不能为负数。
	// 按理说步长也不能大于某个值，这里暂不讨论
	for (int s : stride)
		if (s <= 0)throw invalid_argument("stride must be positive");
	for (int p : padding)
		if (p < 0)throw invalid_argument("padding must be positive .");

	// 计算输出尺寸 [out_depth, out_height, out_width]
	// floor 函数返回不大于所给浮点数的最大整数值
	const int out_depth = floor((in_depth + 2 * padding[0] - k_depth) / float(stride[0]) + 1);
	const int out_height = floor((in_height + 2 * padding[1] - k_height) / float(stride[1]) + 1);
	const int out_width = floor((in_width + 2 * padding[2] - k_width) / float(stride[2]) + 1);

	if (out_depth <= 0 || out_height <= 0 || out_width <= 0)
		throw invalid_argument("Output dimension must be non-positive");

	// 创建带 padding 的输入张量
	vector<vector<vector<float>>>padded_input(
		in_depth + 2 * padding[0], vector<vector<float>>(
			in_height + 2 * padding[1], vector<float>(in_width + 2 * padding[2], 0)));

	// 填充原始数据
	for (int d = 0; d < in_depth; ++d)
	{
		for (int h = 0; h < in_height; ++h)
		{
			for (int w = 0; w < in_width; ++w)
				padded_input[d + padding[0]][h + padding[1]][w + padding[2]] = input[d][h][w];
		}
	}

	// 初始化输出张量
	vector<vector<vector<float>>>output(
		out_depth, vector<vector<float>>(
			out_height, vector<float>(out_width, 0)));

	// 三维卷积计算
	for (int od = 0; od < out_depth; ++od)
	{
		for (int oh = 0; oh < out_height; ++oh)
		{
			for (int ow = 0; ow < out_width; ++ow)
			{
				float sum = 0.0f;

				// 计算输入起始位置
				const int d_start = od * stride[0];
				const int h_start = oh * stride[1];
				const int w_start = ow * stride[2];

				// 卷积遍历窗口
				for (int kd = 0; kd < k_depth; ++kd)
				{
					for (int kh = 0; kh < k_height; ++kh)
					{
						for (int kw = 0; kw < k_width; ++kw)
						{
							// 计算输入位置
							const int id = d_start + kd;
							const int ih = h_start + kh;
							const int iw = w_start + kw;

							// 边界检查（理论上不需要，因为输出尺寸已正确计算）
							if (id < padded_input.size() &&
								ih < padded_input[0].size() &&
								iw < padded_input[0][0].size())
							{
								sum += padded_input[id][ih][iw] * kernel[kd][kh][kw];
							}
						}
					}
				}
				output[od][oh][ow] = sum;
			}
		}
	}
	return output;
}


