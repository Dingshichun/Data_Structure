#include"head1.h"

// 1����ά�������
// ����:
//   input: ������� (height x width)
//   kernel: ����� (k_height x k_width)
//   stride: ���� (Ĭ�� 1)
//   padding: �߽���� (Ĭ�� 0)��padding ���ڶ��پ������������Χ��Ӷ��ٲ� 0
// ���: ����������
vector<vector<float>>convolu2D(
	const vector<vector<float>>& input,
	const vector<vector<float>>& kernel,
	int stride = 1,
	int padding = 0) // stride �� padding ��Ĭ�ϲ�����Ĭ��ֵֻ�������������б���������ͬʱ��
{
	// ��֤����ĺϷ���
	if (input.empty() || input[0].empty())
		throw invalid_argument("input can not be empty");
	if (kernel.empty() || kernel[0].empty())
		throw invalid_argument("kernel can not be empty");
	if (stride < 0 || padding < 0)
		throw invalid_argument("stride and padding can not be negative");

	// ����ߴ�
	int in_height = input.size();
	int in_width = input[0].size();

	// ����˳ߴ硣һ���Ƿ���
	int k_height = kernel.size();
	int k_width = kernel[0].size();

	// ���㾭�������Ӧ������Ĵ�С����ʽ��(n + 2p - k)/stride + 1
	int out_height = (in_height + 2 * padding - k_height) / stride + 1;
	int out_width = (in_width + 2 * padding - k_width) / stride + 1;

	// �������������ȫ����ʼ��Ϊ 0
	vector<vector<float>>output(out_height, vector<float>(out_width, 0));

	// ������������ padding ��padding ���ڶ��پ������������Χ��Ӷ��ٲ� 0��
	// �� ���Ϳ�Ҫ���� 2*padding
	// padding Ĭ��ֵΪ 0
	vector<vector<float>>padded_input(in_height + 2 * padding,
		vector<float>(in_width + 2 * padding, 0));
	for (int i = 0; i < in_height; ++i)
	{
		for (int j = 0; j < in_width; ++j)
		{
			padded_input[i + padding][j + padding] = input[i][j];
		}
	}

	// ִ�о������
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

// 2����ά�������
vector<vector<vector<float>>>convolu3D(
	const vector<vector<vector<float>>>& input,
	const vector<vector<vector<float>>>& kernel,
	const vector<int>& stride = { 1,1,1 },
	const vector<int>& padding = { 0,0,0 })
{
	// ��֤������Ч��
	if (input.empty() || input[0].empty() || input[0][0].empty())
		throw invalid_argument("Input tensor must be 3D");
	if (kernel.empty() || kernel[0].empty() || kernel[0][0].empty())
		throw invalid_argument("Input tensor must be 3D");

	// ��ȡ����ߴ� [depth, height, width]
	const int in_depth = input.size();
	const int in_height = input[0].size();
	const int in_width = input[0][0].size();

	// ��ȡ����˳ߴ� [k_depth, k_height, k_width]
	const int k_depth = kernel.size();
	const int k_height = kernel[0].size();
	const int k_width = kernel[0][0].size();

	// ��֤���������������Ƿ�ƥ��
	if (k_depth > in_depth + 2 * padding[0])
		throw invalid_argument("Kernel depth exceeds padded input depth");

	// ������֤������ stride ����� padding ����Ϊ������
	// ����˵����Ҳ���ܴ���ĳ��ֵ�������ݲ�����
	for (int s : stride)
		if (s <= 0)throw invalid_argument("stride must be positive");
	for (int p : padding)
		if (p < 0)throw invalid_argument("padding must be positive .");

	// ��������ߴ� [out_depth, out_height, out_width]
	// floor �������ز������������������������ֵ
	const int out_depth = floor((in_depth + 2 * padding[0] - k_depth) / float(stride[0]) + 1);
	const int out_height = floor((in_height + 2 * padding[1] - k_height) / float(stride[1]) + 1);
	const int out_width = floor((in_width + 2 * padding[2] - k_width) / float(stride[2]) + 1);

	if (out_depth <= 0 || out_height <= 0 || out_width <= 0)
		throw invalid_argument("Output dimension must be non-positive");

	// ������ padding ����������
	vector<vector<vector<float>>>padded_input(
		in_depth + 2 * padding[0], vector<vector<float>>(
			in_height + 2 * padding[1], vector<float>(in_width + 2 * padding[2], 0)));

	// ���ԭʼ����
	for (int d = 0; d < in_depth; ++d)
	{
		for (int h = 0; h < in_height; ++h)
		{
			for (int w = 0; w < in_width; ++w)
				padded_input[d + padding[0]][h + padding[1]][w + padding[2]] = input[d][h][w];
		}
	}

	// ��ʼ���������
	vector<vector<vector<float>>>output(
		out_depth, vector<vector<float>>(
			out_height, vector<float>(out_width, 0)));

	// ��ά�������
	for (int od = 0; od < out_depth; ++od)
	{
		for (int oh = 0; oh < out_height; ++oh)
		{
			for (int ow = 0; ow < out_width; ++ow)
			{
				float sum = 0.0f;

				// ����������ʼλ��
				const int d_start = od * stride[0];
				const int h_start = oh * stride[1];
				const int w_start = ow * stride[2];

				// �����������
				for (int kd = 0; kd < k_depth; ++kd)
				{
					for (int kh = 0; kh < k_height; ++kh)
					{
						for (int kw = 0; kw < k_width; ++kw)
						{
							// ��������λ��
							const int id = d_start + kd;
							const int ih = h_start + kh;
							const int iw = w_start + kw;

							// �߽��飨�����ϲ���Ҫ����Ϊ����ߴ�����ȷ���㣩
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


