#include <iostream>
using namespace std;

// 迷宫结点的数据类型
typedef struct
{
    int x, y, d; // 横纵坐标 x、y 和前进方向 d
} NodeType;

// 定义迷宫的坐标结点
class MazeNode
{
public:
    NodeType data;
    MazeNode *next;
    MazeNode()
    {
        next = NULL;
    }
};

// 定义迷宫链栈
class MazeLinkStack
{
private:
    MazeNode *top;

public:
    MazeLinkStack()
    {
        top = NULL;
    }
    ~MazeLinkStack()
    {
        MazeNode *p;
        while (top)
        {
            p = top;
            top = top->next;
            delete p;
        }
        top = NULL;
    }

    int IsEmpty();              // 判断链栈是否为空
    int Push_Stack(NodeType e); // 将数据 e 插入栈顶
    int Pop_Stack(NodeType &e); // 从栈顶删除一个元素并保存到 e 中
};

int MazeLinkStack::IsEmpty()
{
    return (!top);
}

int MazeLinkStack::Push_Stack(NodeType e)
{
    MazeNode *p = new MazeNode(); // 申请结点
    if (p)                        // 申请结点成功
    {
        p->data = e;
        p->next = top;
        top = p; // 修改栈顶指针
        return 1;
    }
    else
        return 0;
}

int MazeLinkStack::Pop_Stack(NodeType &e)
{
    MazeNode *p;
    if (top)
    {
        p = top;
        e = p->data;
        top = top->next;
        return 1;
    }
    else
        return 0;
}