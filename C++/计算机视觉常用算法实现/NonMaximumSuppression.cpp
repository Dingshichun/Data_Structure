#include"head1.h"

// ʵ�ַǼ���ֵ����
// 1�����ȶ���һ���ṹ�壬���ڴ洢�������������Ŷ�
//struct BBox 
//{
// �������ϽǺ����½���������Ϊͼ���� y ��������Ϊ����x ��������Ϊ��
//    int x1, y1;       // ���Ͻ�����(x1,y1)
//    int x2, y2;       // ���½�����(x2,y2)
//    float confidence; // ���Ŷ�
//    int class_id;     // ����ʶ����ѡ��
//};

// 3��������������Ľ����ȣ�IoU��
float calculateIoU(const BBox& box1, const BBox& box2) 
{
    // ���㽻����������
    int x1 = max(box1.x1, box2.x1);//�����������Ͻ�
    int y1 = max(box1.y1, box2.y1);
    int x2 = min(box1.x2, box2.x2);//�����������½�
    int y2 = min(box1.y2, box2.y2);

    // ���㽻�����
    int inter_area = max(0, x2 - x1) * max(0, y2 - y1);
    if (inter_area == 0) return 0.0f;

    // ���㲢�����
    int area1 = (box1.x2 - box1.x1) * (box1.y2 - box1.y1);
    int area2 = (box2.x2 - box2.x1) * (box2.y2 - box2.y1);
    float union_area = area1 + area2 - inter_area;

    return inter_area / union_area;
}

// 3������Ǽ���ֵ���ƺ���
vector<BBox> nms(vector<BBox>& boxes, float iou_threshold) 
{
    //�����������ŶȴӸߵ�����������ʹ���� lambda ���ʽ
    sort(boxes.begin(), boxes.end(),
        [](const BBox& a, const BBox& b) {return a.confidence > b.confidence; 
        });
    
    vector<BBox> keep_boxes; // ���汣���ļ���
    vector<bool> suppressed(boxes.size(), false); // ����Ƿ�����

    // ������ʹ��������ѭ�������ѭ������ÿ�������ڲ�ѭ��������ǰ�������ļ���
    // ������ÿ�����򣬶�Ҫ�Ա��������Ŷȱ����͵ļ���� iou�����Ʋ����ϵļ���
    for (int i = 0; i < boxes.size(); ++i) 
    {
        if (suppressed[i]) continue; // �����ǰ�����Ѿ������ƣ�������
        keep_boxes.push_back(boxes[i]); // ������ǰ����

        for (int j = i + 1; j < boxes.size(); ++j) 
        {
            if (suppressed[j]) continue; // �����һ�������Ѿ������ƣ�������
            float iou = calculateIoU(boxes[i], boxes[j]); // ���� IoU
            if (iou > iou_threshold) {
                suppressed[j] = true; // ��� IoU ������ֵ����������һ������
            }
        }
    }
    return keep_boxes; // ���ر����ļ���
}
