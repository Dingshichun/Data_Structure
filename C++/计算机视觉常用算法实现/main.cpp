#include"head1.h"

int main()
{
	/*vector<vector<float>>input = {
		{1,2,3},{4,5,6},{7,8,9}
	};
	vector<vector<float>>kernel = { {0.5,0.5,0.5},{0.5,0.5,0.5},{0.5,0.5,0.5} };

	auto result = convolu2D(input, kernel,1,1);
	for (const auto& row : result)
	{
		for (float val : row)
			cout << val << " ";
		cout << "\n";
	}*/

    //try {
    //    // 示例输入 (2x3x3)
    //    vector<vector<vector<float>>> input = {
    //        {{1,2,3}, {4,5,6}, {7,8,9}},  // depth=0
    //        {{9,8,7}, {6,5,4}, {3,2,1}}   // depth=1
    //    };

    //    // 示例卷积核 (2x2x2)
    //    vector<vector<vector<float>>> kernel = {
    //        {{0.5,0.5}, {0.5,0.5}},  // depth=0
    //        {{0.2,0.2}, {0.2,0.2}}   // depth=1
    //    };

    //    // 执行卷积（步长2，各维度padding1）
    //    auto result = convolu3D(input, kernel, { 2,2,2 }, { 1,1,1 });

    //    // 打印结果
    //    cout << "Convolution Result:\n";
    //    for (const auto& depth : result) {
    //        for (const auto& row : depth) {
    //            for (float val : row) {
    //                cout << val << " ";
    //            }
    //            cout << endl;
    //        }
    //        cout << "-----------------\n";
    //    }
    //}
    //catch (const exception& e) {
    //    cerr << "Error: " << e.what() << endl;
    //}

    /*vector<vector<float>>input = { {10,20},{30,40} };
    int scale_x = 2;
    int scale_y = 2;
    vector<vector<float>>output = nearestNeighbor(input, scale_x, scale_y);
    for (const auto& row : output)
    {
        for (float col : row)
            cout << col << " ";
        cout << "\n";
    }*/

    /*vector<BBox> boxes = {
        {300, 300, 500, 500, 0.9, 0},
        {310, 310, 510, 510, 0.85, 0},
        {290, 320, 490, 520, 0.8, 0},
        {500, 500, 800, 800, 0.95, 1}
    };
    vector<BBox> result = nms(boxes, 0.5);
    for (const auto& box : result)
    {
        cout << "x1: " << box.x1 << ", y1: " << box.y1 << ", x2: " << box.x2 << endl;
    }*/


	return 0;
}

