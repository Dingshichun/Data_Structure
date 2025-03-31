#include"head1.h"

// 插值算法。包括最近邻、双线性、三线性

// 1、最近邻插值
vector<vector<float>> nearestNeighbor(
	const vector<vector<float>>& input,
	float scale_x,
	float scale_y)
{
	if (input.empty() || input[0].empty())
		throw invalid_argument("Input matrix is empty");
	if (scale_x <= 0 || scale_y <= 0)
		throw invalid_argument("Scale factors must be positive");

	const int in_h = input.size();
	const int in_w = input[0].size();
	const int out_h = ceil(in_h * scale_y);  // 输出图像的高度
	const int out_w = ceil(in_w * scale_x);  // 输出图像的宽度

	vector<vector<float>> output(out_h, vector<float>(out_w, 0));

	for (int y = 0; y < out_h; ++y) {
		for (int x = 0; x < out_w; ++x) {
			// 计算目标图像中的坐标所对应的输入图像的坐标（可能超出范围）
			float src_y = y / scale_y;
			float src_x = x / scale_x;

			// 取最近的整数坐标，
			// 最好使用 floor，而不是 round，因为 floor 总是向下取整，满足要求。
			// 这里同时还限定了取值范围
			int nearest_y = min(max(static_cast<int>(floor(src_y)), 0), in_h - 1);
			int nearest_x = min(max(static_cast<int>(floor(src_x)), 0), in_w - 1);

			output[y][x] = input[nearest_y][nearest_x];
		}
	}
	return output;
}

// 2、双线性插值。
// 简单说就是根据这个点周围的四个像素点进行插值。
// 具体来说，就是先根据这个点在x轴上的位置，对上下的两个点进行插值，
// 然后再根据这个点在y轴上的位置，对插值后的两个点进行插值。

// 双线性插值是一种在二维空间中进行插值的方法，它通过在两个已知点之间进行线性插值来估计未知点的值。
// 在图像处理中，双线性插值常用于图像缩放和图像旋转等操作，以获得更平滑的图像效果。
// 双线性插值的基本思想是在目标图像的每个像素位置上，根据其周围的四个已知像素的值，通过线性插值计算出该位置的
// 值。具体来说，对于目标图像中的像素 (x, y)，我们可以通过以下公式计算其值：
// f(x, y) = (1 - dx) * (1 - dy) * f(x1, y1) + dx * (1
// - dy) * f(x2, y2) + (1 - dx) * dy * f(x1, y2) + dx * dy * f(x2, y2)
// 其中，(x1, y1) 和 (x2, y2) 是目标图像中的像素 (x, y) 所对应的输入
// 图像中的四个已知像素的坐标，dx 和 dy 分别是目标图像中的像素 (x, y) 与其对应的输入图像中的像素
// (x1, y1) 在 x 和 y 方向上的距离。

// 安全获取像素值（处理边界）
float getPixelSafe(const vector<vector<float>>& mat, int row, int col) {
    // 限制坐标在有效范围内
	// static_cast<int> 是 一种类型转换操作符，
	// 它的作用是将一个表达式的类型转换为指定的目标类型
    row = max(0, min(static_cast<int>(mat.size()) - 1, row));
    col = max(0, min(static_cast<int>(mat[0].size()) - 1, col));
    return mat[row][col];
}

/**
 * 双线性插值函数
 * @param input  输入矩阵（二维vector），如果是图像就是原图
 * @param x      目标点的列坐标（浮点型，范围[0, width-1]），原图的列坐标
 * @param y      目标点的行坐标（浮点型，范围[0, height-1]），原图的行坐标
 * @return       插值计算结果。也就是目标图中应该的结果
 */
float bilinearInterpolation(const vector<vector<float>>& input, float x, float y) {
    // 输入验证
    if (input.empty() || input[0].empty()) {
        throw invalid_argument("Input matrix cannot be empty");
    }

    // 计算基准坐标。
	// 也就是目标图中的坐标点所对应到原图的坐标点，其周围四个坐标点中处于左上角的坐标点。
	//比方说目标图对应到原图的坐标点为（0.5,0.5），
	// 那么原图中，其周围四个坐标点为（0,0）（0,1）（1,0）（1,1）。左上角的就是(0,0)。
    const int x_floor = static_cast<int>(floor(x));
    const int y_floor = static_cast<int>(floor(y));

    // 计算小数部分
    const float dx = x - x_floor;
    const float dy = y - y_floor;

    // 获取坐标（x,y）四个邻近点的像素值（自动处理边界），注意传入的参数顺序
    const float Q11 = getPixelSafe(input, y_floor, x_floor);
    const float Q12 = getPixelSafe(input, y_floor, x_floor + 1);
    const float Q21 = getPixelSafe(input, y_floor + 1, x_floor);
    const float Q22 = getPixelSafe(input, y_floor + 1, x_floor + 1);

    // 双线性插值公式。自行推理
    return Q11 * (1 - dx) * (1 - dy) +
        Q12 * dx * (1 - dy) +
        Q21 * (1 - dx) * dy +
        Q22 * dx * dy;
}
