#include"head1.h"

// ��ֵ�㷨����������ڡ�˫���ԡ�������

// 1������ڲ�ֵ
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
	const int out_h = ceil(in_h * scale_y);  // ���ͼ��ĸ߶�
	const int out_w = ceil(in_w * scale_x);  // ���ͼ��Ŀ��

	vector<vector<float>> output(out_h, vector<float>(out_w, 0));

	for (int y = 0; y < out_h; ++y) {
		for (int x = 0; x < out_w; ++x) {
			// ����Ŀ��ͼ���е���������Ӧ������ͼ������꣨���ܳ�����Χ��
			float src_y = y / scale_y;
			float src_x = x / scale_x;

			// ȡ������������꣬
			// ���ʹ�� floor�������� round����Ϊ floor ��������ȡ��������Ҫ��
			// ����ͬʱ���޶���ȡֵ��Χ
			int nearest_y = min(max(static_cast<int>(floor(src_y)), 0), in_h - 1);
			int nearest_x = min(max(static_cast<int>(floor(src_x)), 0), in_w - 1);

			output[y][x] = input[nearest_y][nearest_x];
		}
	}
	return output;
}

// 2��˫���Բ�ֵ��
// ��˵���Ǹ����������Χ���ĸ����ص���в�ֵ��
// ������˵�������ȸ����������x���ϵ�λ�ã������µ���������в�ֵ��
// Ȼ���ٸ����������y���ϵ�λ�ã��Բ�ֵ�����������в�ֵ��

// ˫���Բ�ֵ��һ���ڶ�ά�ռ��н��в�ֵ�ķ�������ͨ����������֪��֮��������Բ�ֵ������δ֪���ֵ��
// ��ͼ�����У�˫���Բ�ֵ������ͼ�����ź�ͼ����ת�Ȳ������Ի�ø�ƽ����ͼ��Ч����
// ˫���Բ�ֵ�Ļ���˼������Ŀ��ͼ���ÿ������λ���ϣ���������Χ���ĸ���֪���ص�ֵ��ͨ�����Բ�ֵ�������λ�õ�
// ֵ��������˵������Ŀ��ͼ���е����� (x, y)�����ǿ���ͨ�����¹�ʽ������ֵ��
// f(x, y) = (1 - dx) * (1 - dy) * f(x1, y1) + dx * (1
// - dy) * f(x2, y2) + (1 - dx) * dy * f(x1, y2) + dx * dy * f(x2, y2)
// ���У�(x1, y1) �� (x2, y2) ��Ŀ��ͼ���е����� (x, y) ����Ӧ������
// ͼ���е��ĸ���֪���ص����꣬dx �� dy �ֱ���Ŀ��ͼ���е����� (x, y) �����Ӧ������ͼ���е�����
// (x1, y1) �� x �� y �����ϵľ��롣

// ��ȫ��ȡ����ֵ������߽磩
float getPixelSafe(const vector<vector<float>>& mat, int row, int col) {
    // ������������Ч��Χ��
	// static_cast<int> �� һ������ת����������
	// ���������ǽ�һ�����ʽ������ת��Ϊָ����Ŀ������
    row = max(0, min(static_cast<int>(mat.size()) - 1, row));
    col = max(0, min(static_cast<int>(mat[0].size()) - 1, col));
    return mat[row][col];
}

/**
 * ˫���Բ�ֵ����
 * @param input  ������󣨶�άvector���������ͼ�����ԭͼ
 * @param x      Ŀ���������꣨�����ͣ���Χ[0, width-1]����ԭͼ��������
 * @param y      Ŀ���������꣨�����ͣ���Χ[0, height-1]����ԭͼ��������
 * @return       ��ֵ��������Ҳ����Ŀ��ͼ��Ӧ�õĽ��
 */
float bilinearInterpolation(const vector<vector<float>>& input, float x, float y) {
    // ������֤
    if (input.empty() || input[0].empty()) {
        throw invalid_argument("Input matrix cannot be empty");
    }

    // �����׼���ꡣ
	// Ҳ����Ŀ��ͼ�е����������Ӧ��ԭͼ������㣬����Χ�ĸ�������д������Ͻǵ�����㡣
	//�ȷ�˵Ŀ��ͼ��Ӧ��ԭͼ�������Ϊ��0.5,0.5����
	// ��ôԭͼ�У�����Χ�ĸ������Ϊ��0,0����0,1����1,0����1,1�������Ͻǵľ���(0,0)��
    const int x_floor = static_cast<int>(floor(x));
    const int y_floor = static_cast<int>(floor(y));

    // ����С������
    const float dx = x - x_floor;
    const float dy = y - y_floor;

    // ��ȡ���꣨x,y���ĸ��ڽ��������ֵ���Զ�����߽磩��ע�⴫��Ĳ���˳��
    const float Q11 = getPixelSafe(input, y_floor, x_floor);
    const float Q12 = getPixelSafe(input, y_floor, x_floor + 1);
    const float Q21 = getPixelSafe(input, y_floor + 1, x_floor);
    const float Q22 = getPixelSafe(input, y_floor + 1, x_floor + 1);

    // ˫���Բ�ֵ��ʽ����������
    return Q11 * (1 - dx) * (1 - dy) +
        Q12 * dx * (1 - dy) +
        Q21 * (1 - dx) * dy +
        Q22 * dx * dy;
}
