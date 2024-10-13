
// （1）顺序队列原理及实现

// 约定，队头指针指向实际队头元素所在位置的前一位置，所以队头指针指向的位置没有元素
// 队尾指针指向实际队尾元素所在的位置，

// 从队头到队尾，位置依次增大，比如 0,1,2,3,4
// 入队操作是在队尾 rear 的后一个位置插入一个元素，
// 比如队尾是 3 ，那么就在 4 的位置插入元素，队头不变。

// 出队操作是在队头删除一个元素，有两种方法。
// 第一种是将所有的队列元素向前移一位，rear 减 1, front 始终指向 0 位置不变，
// 就像排队时，队头总是固定在一个位置不变，每出队列一个人，其余的人向前走一个位置；
// 另一种方法是不需要移动元素，修改队列头指针 front 加 1 ，一般常采用第二种方法。

// 但是第二种方法存在假溢出。

// 溢出有两种。
// 一种是元素所占空间超过实际分配的空间时溢出，这是正常现象。
// 第二种就是假溢出。出队删除元素时，为了避免移动元素，只是修改了队头指针（加 1 ），
// 这样随着出队、入队的进行，队列就会整体向后移动，队尾指针已经移动到最后，
// 再加入元素就会溢出，但事实上此时的队并未满员，头指针之前的位置都是空的，造成假溢出。

// 解决假溢出的方法之一是将队列的数据区看成头尾相接的循环结构，
// 头尾指针的关系不变，将其称为“循环队列”​。

// 因为是头尾相接的循环结构，
// 入队时的队尾指针加 1 操作修改为：rear=(rear+1)%size; （size为顺序队列空间的大小）​，
// 出队时的队头指针加 1 操作修改为：front=(front+1)% size。​

// 下面讨论队列空和满的条件。
// 队空的条件：front=rear；
// 队满的条件：如果队列的入队比出队快，队列中元素逐渐增多，
//  rear 会追上 front ，此时队满 front=rear。
// 因此，队空的条件和队满的条件相同，无法判断。这显然是必须要解决的一个问题。

// 判断循环队列空还是满的方法之一是附设一个存储队中元素个数的变量，
// 如 num，当 num=0 时为队空，当 num=size 时为队满。

// 另一种方法是少用一个元素空间，使队尾指针 rear 永远赶不上 front ，
// 即当队尾指针加 1 就会从后面赶上队头指针时，就视为队满。
// 在这种情况下，队满的条件是：(rear+1)% size=front ，就能和空队区别开。

// 循环队列利用第二种判断队空和队满条件的类
#include <iostream>
using namespace std;
typedef int DataType;

// 注意：队头指针指向实际队头元素所在位置的前一位置。

// 顺序队列
class SeqQueue
{
private:
    DataType *base; // 保存所开辟空间的地址
    int front;
    int rear;
    int size;

public:
    SeqQueue(int Queuesize = 100)
    {
        base = new DataType[Queuesize]; // 创建空间
        front = 0;                      // 空队列的头尾相等且为 0
        rear = 0;
        size = Queuesize;
    }
    ~SeqQueue()
    {
        delete[] base; // 释放空间
    }

    int Empty_Queue();            // 判断队列是否为空
    int En_Queue(DataType e);     // 元素 e 入队
    int De_Queue(DataType &e);    // 将出队元素保存到 e
    int Front_Queue(DataType &e); // 取出队头元素并保存到 e
};

// 判断顺序队列是否为空
int SeqQueue::Empty_Queue()
{
    return (front == rear);
}

// 将元素 e 插入顺序队列
int SeqQueue::En_Queue(DataType e)
{
    if ((rear + 1) % size != front)
    {
        rear = (rear + 1) % size;
        base[rear] = e;
        return (1);
    }
    else
    {
        cout << "Queue is full" << endl;
        return (0);
    }
}

// 顺序队列的队头元素出队，并保存到 e 中进行返回
int SeqQueue::De_Queue(DataType &e)
{
    if (front != rear)
    {
        // 由于队头指针指向的位置没有元素，第一个元素在队头指针后面一个位置
        // 所以删除第一个元素是删除队头指针后一个位置的元素，
        // 即 (front + 1) % size 位置的元素，要先执行加 1 操作之后才能取到第一个元素的值
        front = (front + 1) % size;
        e = base[front];
        return (1);
    }
    else
    {
        cout << "Queue is empty" << endl;
        return (0);
    }
}

// 获取顺序队列的队头元素，保存到 e 中进行返回
int SeqQueue::Front_Queue(DataType &e)
{
    if (front != rear)
    {
        front = (front + 1) % size;
        e = base[front];
        return (1);
    }
    else
    {
        return (0);
    }
}

// （2）链队列

// 注意：约定链队列的头指针不再指向第一个元素的前一个位置，而是直接指向第一个元素。
// 而上面实现的顺序队列约定头指针指向第一个元素的前一个位置
// 链队列的头指针和尾指针指向的是第一个元素和最后一个元素。

// 链队列结点
class QueueNode
{
public:
    DataType data;   // 数据域
    QueueNode *next; // 指针域
    QueueNode()
    {
        next = NULL; // 指针域初始化空
    }
};

// 链队列
class LinkQueue
{
private:
    QueueNode *front; // front 指向第一个元素的位置
    QueueNode *rear;  // rear 指向最后一个元素的位置

public:
    LinkQueue()
    {
        front = NULL;
        rear = NULL;
    }
    ~LinkQueue()
    {
        QueueNode *p, *q;
        p = front; // front 指向第一个元素位置，所以 p 也是
        while (p)  // 链队列非空时
        {
            q = p;       // 第一次循环时 q 也指向第一个元素位置
            p = p->next; // 更新 p ，p 指向 p 的下一个元素位置。
            delete q;    // 删除当前结点
        }
        front = NULL; // 头尾指针置空
        rear = NULL;
    }
    int Empty_Queue();            // 判断链队列是否为空
    int En_Queue(DataType e);     // 元素 e 入队
    int De_Queue(DataType &e);    // 将出队元素保存到 e
    int Front_Queue(DataType &e); // 取出队头元素并保存到 e
};

// 判断链队列是否为空
int LinkQueue::Empty_Queue()
{
    return ((front == NULL) && (rear == NULL));
}

// 元素 e 插入链队列
int LinkQueue::En_Queue(DataType e)
{
    QueueNode *p = new QueueNode; // 申请结点
    if (p)                        // 如果申请结点成功
    {
        p->data = e;

        if (rear) // 如果原队列非空，入队元素直接插入队列的尾部
        {
            rear->next = p;
        }
        else // 原队列为空，那么插入的元素既是队头元素，也是队尾元素。
        {
            front = rear = p;
        }
        return (1);
    }
    else // 申请结点失败
    {
        return (0);
    }
}

// 将出队元素保存到 e 中进行返回
int LinkQueue::De_Queue(DataType &e)
{
    if (!Empty_Queue()) // 如果队列非空
    {
        QueueNode *p; // 创建指针保存即将出队结点的地址
        p = front;
        e = front->data;
        front = front->next; // 头指针指向即将出队结点的下一个结点
        if (front == NULL)   // 如果出队后列表变空
        {
            rear = NULL; // 修改队尾指针为空
        }
        delete p; // 删除出队的结点
        return (1);
    }
    else
    {
        cout << "Queue is empty" << endl;
        return (0);
    }
}

// 获取链队列的队头元素，保存到 e 中进行返回
int LinkQueue::Front_Queue(DataType &e)
{
    // 只是获取队头元素的话就不用更新结点那些操作
    if (!Empty_Queue())
    {
        e = front->data;
        return (1);
    }
    else
    {
        cout << "Queue is empty" << endl;
        return (0);
    }
}