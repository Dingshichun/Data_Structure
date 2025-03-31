#include"head1.h"

// 实现非极大值抑制
// 1、首先定义一个结构体，用于存储检测框的坐标和置信度
//struct BBox 
//{
// 定义左上角和右下角坐标是因为图像中 y 轴是向下为正，x 轴是向右为正
//    int x1, y1;       // 左上角坐标(x1,y1)
//    int x2, y2;       // 右下角坐标(x2,y2)
//    float confidence; // 置信度
//    int class_id;     // 类别标识（可选）
//};

// 3、计算两个检测框的交并比（IoU）
float calculateIoU(const BBox& box1, const BBox& box2) 
{
    // 计算交集区域坐标
    int x1 = max(box1.x1, box2.x1);//交集区域左上角
    int y1 = max(box1.y1, box2.y1);
    int x2 = min(box1.x2, box2.x2);//交集区域右下角
    int y2 = min(box1.y2, box2.y2);

    // 计算交集面积
    int inter_area = max(0, x2 - x1) * max(0, y2 - y1);
    if (inter_area == 0) return 0.0f;

    // 计算并集面积
    int area1 = (box1.x2 - box1.x1) * (box1.y2 - box1.y1);
    int area2 = (box2.x2 - box2.x1) * (box2.y2 - box2.y1);
    float union_area = area1 + area2 - inter_area;

    return inter_area / union_area;
}

// 3、定义非极大值抑制函数
vector<BBox> nms(vector<BBox>& boxes, float iou_threshold) 
{
    //将检测框按照置信度从高到低排序，这里使用了 lambda 表达式
    sort(boxes.begin(), boxes.end(),
        [](const BBox& a, const BBox& b) {return a.confidence > b.confidence; 
        });
    
    vector<BBox> keep_boxes; // 保存保留的检测框
    vector<bool> suppressed(boxes.size(), false); // 标记是否被抑制

    // 这里是使用了两层循环，外层循环遍历每个检测框，内层循环遍历当前检测框后面的检测框
    // 即对于每个检测框，都要对比它和置信度比它低的检测框的 iou，抑制不符合的检测框。
    for (int i = 0; i < boxes.size(); ++i) 
    {
        if (suppressed[i]) continue; // 如果当前检测框已经被抑制，则跳过
        keep_boxes.push_back(boxes[i]); // 保留当前检测框

        for (int j = i + 1; j < boxes.size(); ++j) 
        {
            if (suppressed[j]) continue; // 如果下一个检测框已经被抑制，则跳过
            float iou = calculateIoU(boxes[i], boxes[j]); // 计算 IoU
            if (iou > iou_threshold) {
                suppressed[j] = true; // 如果 IoU 大于阈值，则抑制下一个检测框
            }
        }
    }
    return keep_boxes; // 返回保留的检测框
}
