#include <iostream>
#define MAXSIZE 100
typedef int DataType;
using namespace std;

// （1）顺序栈
class SeqStack
{
private:
    DataType *base; // 栈底指针
    DataType *top;  // 栈顶指针，始终指向栈顶元素的后一个位置
    int size;

public:
    SeqStack(int stacksize = 100)
    {
        base = new DataType[stacksize]; // 开辟空间
        top = base;                     // 栈顶指针始终指向栈顶元素的后一个位置
        size = stacksize;
    }
    ~SeqStack() // 销毁一个存在的栈
    {
        delete[] base;
        top = NULL;
        base = NULL;
    }
    int IsEmpty();                 // 判断栈是否为空
    int Push_Stack(DataType e);    // 将元素 e 插入栈顶
    int Pop_Stack(DataType &e);    // 从栈顶删除一个元素并保存到 e 中
    int GetTop_Stack(DataType &e); // 从栈顶取出一个元素并保存到 e 中
};

int SeqStack::IsEmpty()
{
    return ((top <= base));
}

int SeqStack::Push_Stack(DataType e)
{
    if ((top - base) < size) // 判断栈是否已满
    {
        *top = e;
        top++;
        return 1;
    }
    else
        return 0;
}

int SeqStack::Pop_Stack(DataType &e)
{
    if (top > base) // 判断栈是否为空
    {
        // 由于top指向的是栈顶元素的后一个位置，所以 top-- 才是栈顶元素的位置
        top--;
        e = *top;
        return 1;
    }
    else
        return 0;
}

int SeqStack::GetTop_Stack(DataType &e)
{
    if (base < top) // 判断栈是否为空
    {
        top--;
        e = *top;
        return 1;
    }
    else
        return 0;
}

// （2）链栈
// 定义链栈的结点
class StackNode
{
public:
    DataType data;
    StackNode *next;
    StackNode()
    {
        next = NULL;
    }
};

// 定义链栈
class LinkStack
{
private:
    StackNode *top;

public:
    LinkStack()
    {
        top = NULL;
    }
    ~LinkStack()
    {
        StackNode *p;
        while (top)
        {
            p = top;
            top = top->next;
            delete p;
        }
        top = NULL;
    }
    int IsEmpty();                 // 判断链栈是否为空
    int Push_Stack(DataType e);    // 将数据 e 插入栈顶
    int Pop_Stack(DataType &e);    // 从栈顶删除一个元素并保存到 e 中
    int GetTop_Stack(DataType &e); // 取出栈顶元素保存到 e 中
};

int LinkStack::IsEmpty()
{
    return (!top);
}

int LinkStack::Push_Stack(DataType e)
{
    StackNode *p = new StackNode(); // 申请结点
    if (p)                          // 申请结点成功
    {
        p->data = e;
        p->next = top;
        top = p; // 修改栈顶指针
        return 1;
    }
    else
        return 0;
}

int LinkStack::Pop_Stack(DataType &e)
{
    StackNode *p;
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

int LinkStack::GetTop_Stack(DataType &e)
{
    if (top)
    {
        e = top->data;
        return 1;
    }
    else
        return 0;
}

// （3）顺序栈解决进制转换问题

// 十进制数 N 转换为 r 进制，r 小于 10。辗转相除法
int DecConversion(int N, int r, int NumR[])
{
    SeqStack S; // 定义顺序栈
    DataType x; // x 用于保存顺序栈中弹出的栈顶元素
    int i = 0;
    if ((r < 2) || (r > 10))
    {
        // 限定为十进制以下
        return (0);
    }
    while (N) // 当 N 非 0 时
    {
        S.Push_Stack(N % r); // 以余数 N % r 入栈
        N = N / r;           // 更新 N 为 N / r ，即商
    }
    while (!S.IsEmpty()) // 当顺序栈 S 不为空时
    {
        S.Pop_Stack(x); // 弹出的栈顶元素赋给 x
        NumR[i++] = x;  // 将 x 加入到数组中
    }
    return (1);
}
