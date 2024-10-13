#include <iostream>
#include <vector>
#define MAXSIZE 100
typedef int DataType;
using namespace std;

/* 1. 线性表的顺序存储 */

// define sequenlist
class SequenList
{
public:
    void Initiate();
    int Length();
    int Insert(DataType x, int i);
    int Delete(int i);
    int Locate(DataType x);
    DataType Get(int i);

private:
    DataType data[MAXSIZE];
    int len;
};

void SequenList::Initiate()
{
    len = 0;
}

int SequenList::Length()
{
    return len;
}

// 在 i 位置插入元素 x
int SequenList::Insert(DataType x, int i)
{
    int j;
    if (len >= MAXSIZE)
    {
        cout << "overflow" << endl;
        return 0;
    }
    else if ((i < 1) || (i > len + 1))
    {
        cout << "position is not correct" << endl;
        return 0;
    }
    else
    {
        for (j = len; j >= i; j--)
        {
            data[j] = data[j - 1];
        }
        data[i - 1] = x;
        len++;
        return 1;
    }
}

// 删除第 i 个位置的元素
int SequenList::Delete(int i)
{
    int j;
    if ((i < 1) || (i > len))
    {
        cout << "position is not correct" << endl;
        return 0;
    }
    else
    {
        for (j = i; j < len; j++)
        {
            data[j - 1] = data[j];
        }
        len--;
        return 1;
    }
}

// 查找元素 x 所在的位置
int SequenList::Locate(DataType x)
{
    int i = 0;
    for (; i <= len - 1; i++)
    {
        if (data[i] == x)
        {
            return i + 1;
        }
    }
    return 0;
}

// 获取第 i 个位置的元素
DataType SequenList::Get(int i)
{
    if ((i < 1) || (i > len))
    {
        cout << "position is not correct" << endl;
        return NULL;
    }
    else
    {
        return data[i - 1];
    }
}

/*
2. 线性表的链式存储
首先使用结构体或类定义结点，然后使用类定义链表。
*/
// 创建结点 Item
class Item
{
public:
    DataType data;          // 数据域
    Item *next;             // 指针域
    Item() { next = NULL; } // 构造函数，指针域初始化为空。
};

// 创建链表
class Link
{
public:
    Item *head;                            // 链表头指针
    Link() { head = NULL; }                // 构造函数
    ~Link() { DeleteAll(); }               // 析构函数
    void Initiate();                       // 初始化
    void DeleteAll();                      // 删除所有结点
    void HeadCreate(int n);                // 头插法建立链表，不含数据域为空的头结点
    void TailCreate(int n);                // 尾插法建立链表，不含数据域为空的头结点
    void HeadCreateWithHead(int n);        // 头插法建立链表，包含数据域为空的头结点
    void TailHeadWithHead(int n);          // 尾插法建立链表，包含数据域为空的头结点
    int Length();                          // 求链表长度
    Item *Locatex(DataType x);             // 查找值为 x 的元素
    Item *Locatei(int i);                  // 查找第 i 个元素
    DataType Get(int i);                   // 获取第 i 个元素的值
    bool Insert(DataType x, int i);        // 在第 i 个位置插入元素 x
    bool Deleted(int i);                   // 删除第 i 个元素
    void Print();                          // 打印链表
    void reverse(Link &L);                 // 反转链表
    void merge(Link &A, Link &B, Link &C); // 合并两个有序链表
};

void Link::Initiate()
{
    DeleteAll(); // 删除所有结点
    head = NULL; // 头指针置空
}

// 删除所有结点，从第一个有效结点开始删。
void Link::DeleteAll()
{
    Item *p = head, *q;
    while (p != NULL)
    {
        q = p->next;
        delete p;
        p = q;
    }
    head = NULL;
}

void Link::HeadCreate(int n)
{
    DeleteAll();                 // 删除所有结点
    Item *new_item, *first_item; // 创建插入的结点的指针 new_item 和第一个结点的指针 first_item
    int i;
    first_item = NULL; // 第一个节点指针置空
    for (i = 1; i <= n; i++)
    {
        new_item = new Item();       // 创建一个新结点，new_item 保存新结点的地址
        cin >> new_item->data;       // 输入新结点的数据
        new_item->next = first_item; // 从头插入，新结点指向第一个结点
        first_item = new_item;       // 将第一个结点更新为新建的结点 new_item
    }
    head = first_item; // 头指针保存第一个结点的地址，即指向第一个结点
}
void Link::TailCreate(int n)
{
    DeleteAll(); // 删除所有结点

    // 三个指针分别保存第一个结点 first_item 、新建结点 new_item 、尾结点tail_item 的地址
    Item *first_item, *new_item, *tail_item;
    first_item = NULL; // 第一个结点的地址置空。表示空链表
    int i;
    for (i = 1; i <= n; i++)
    {
        new_item = new Item(); // 创建新结点
        cin >> new_item->data; // 输入结点的数据
        new_item->next = NULL; // 新建结点的指针域置空
        if (first_item == NULL)
        {
            // 如果链表为空，那么新建的第一个结点既是头结点，也是尾结点。
            first_item = new_item = tail_item;
        }
        else
        {
            // 如果链表不为空，将新建的结点添加到尾结点后
            tail_item->next = new_item;
            tail_item = new_item; // 将创建的新结点更新为尾结点
        }
    }
    head = first_item; // 头指针保存第一个结点的地址
}

void Link::HeadCreateWithHead(int n)
{
    DeleteAll();
    // 两个指针保存新建结点的地址和头结点的地址
    Item *new_item, *head_item;
    head_item = new Item(); // 创建头结点
    head_item->next = NULL; // 头结点指针域置空
    int i;
    for (i = 1; i <= n; i++)
    {
        new_item = new Item(); // 创建添加的结点
        cin >> new_item->data; // 输入数据

        // 注意这里的顺序不能更改，必须现将新建的结点和其后的结点进行链接，最后再和前面的结点进行链接。
        // 注意这里在第一次循环的时候将尾结点的指针域置为 NULL
        // 新建结点的指针域指向头结点之后的第一个结点
        new_item->next = head_item->next;
        // 头结点的指针域指向创建的结点
        head_item->next = new_item;
    }
    head = head_item; // 头指针保存的是头结点的地址
}
void Link::TailHeadWithHead(int n)
{
    // 三个指针分贝保存头结点、新建结点、尾结点的地址
    Item *head_item, *new_item, *tail_item;
    head_item = new Item(); // 创建头结点
    head_item->next = NULL; // 头结点指针域置空
    tail_item = head_item;  // 此时头结点也是尾结点
    int i;
    for (i = 1; i <= n; i++)
    {
        new_item = new Item();      // 创建添加的结点
        cin >> new_item->data;      // 输入数据
        tail_item->next = new_item; // 尾结点的指针域指向新建的结点
        tail_item = new_item;       // 更新尾结点，将新建的结点视为尾结点
    }
    // 由于每执行一次循环尾结点都要更新，所以循环结束后要将其指针域置为 NULL
    tail_item->next = NULL;
    head = head_item; // 头指针指向头结点
}

int Link::Length()
{
    if (head == NULL)
    {
        return 0;
    }
    else
    {
        int i = 0;
        while (head != NULL)
        {
            i++;
            head = head->next;
        }
        return i;
    }
}

Item *Link::Locatex(DataType x)
{
    Item *p;
    p = head->next;
    while ((p != NULL) && (p->data != x))
    {
        p = p->next;
    }
    if (p)
    {
        return p;
    }
    else
    {
        cout << x << "is noot exist" << endl;
        return NULL;
    }
}

Item *Link::Locatei(int i)
{
    // 第 0 个位置是头节点，存储数据的第一个有效结点是头结点之后的第一个结点
    if (i == 0)
    {
        return head;
    }
    // 指针 p 指向头结点之后的第一个结点
    Item *p;
    p = head->next;

    int j = 1;
    while ((p != NULL) && (j < i))
    {
        p = p->next;
        j++;
    }
    if (j == i)
    {
        return p;
    }
    else
    {
        cout << "position is not correct" << endl;
        return NULL;
    }
}
DataType Link::Get(int i)
{
    Item *p;        // 创建结点指针 p
    p = head->next; // p 指向头结点之后的第一个结点
    int j = 1;
    while ((p != NULL) && (j < i))
    {
        j++;
        p = p->next;
    }
    if ((p == NULL) || (j > i))
    {
        cout << "position is not correct" << endl;
        return NULL;
    }
    else
    {
        return p->data;
    }
}

// 前插
bool Link::Insert(DataType x, int i)
{
    Item *p, *s;
    p = Locatei(i - 1); // 调用 Locatei()，直接返回第 i 个结点的前序结点的地址，赋给 p
    if (p == NULL)      // 空链表不能插入
    {
        cout << "position is not correct" << endl;
        return false;
    }
    s = new Item();
    s->data = x;

    // 需要将新建的结点 s 和和后序结点进行链接，再将 s 和其前序结点进行链接。
    s->next = p->next;
    p->next = s;
    return true;
}

bool Link::Deleted(int i)
{
    // 调用 Locatei 定位到第 i-1 个结点
    Item *p = Locatei(i - 1);
    Item *q;
    if (p == NULL)
    {
        cout << "position is not correct" << endl;
        return false;
    }
    q = p->next; // q 是第 i 个结点
    if (q != NULL)
    {
        // 如果第 i 个结点 q 非空，即是有效结点
        // 那么第 i-1 个结点 p 的指针域指向第 i+1 个结点 q->next
        // 最后删除第 i 个结点 q
        p->next = q->next;
        delete q;
        return true;
    }
    else
    {
        cout << "position is not correct" << endl;
        return false;
    }
}

void Link::Print()
{
    Item *p;
    p = head->next;
    while (p != NULL)
    {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void Link::reverse(Link &L)
{
    Item *p, *q;
    p = L.head->next;    // p 指向存储数据的第一个结点
    L.head->next = NULL; // 将原链表置为空表
    while (p)
    {
        q = p;                  // q 等于数据结点
        p = p->next;            // p 更新为下一个数据结点
        q->next = L.head->next; // 将当前结点插入到头结点的后面
        L.head->next = q;
    }
}

// 将非递减排列的链表 A 和链表 B 合并到链表 C 中，C 为非递增。
void Link::merge(Link &A, Link &B, Link &C)
{
    Item *p, *q, *s;
    p = A.head->next;    // p 指向 A 链表的第一个数据结点
    q = B.head->next;    // q 指向 B 链表的第一个数据结点
    C.head->next = NULL; // C 的第一个数据结点置空
    while ((p != NULL) && (q != NULL))
    {
        // 采用的是头插法，所以将值小的结点先插入
        if (p->data <= q->data)
        {
            s = p;
            p = p->next;
        }
        else
        {
            s = q;
            q = q->next;
        }
        // 将 s 结点以头插的方式插入到链表 C 中
        s->next = C.head->next;
        C.head->next = s;
    }

    // 如果 A 的长度比 B 短，即 A 里的结点先插入完了
    // 那么 A 就等于 B 剩余的结点，将剩余的节点继续以头插的方式插入 C。
    if (p == NULL)
        p = q;
    while (p != NULL)
    {
        s = p;
        p = p->next;
        s->next = C.head->next;
        C.head->next = s;
    }
    A.head = NULL;
    B.head = NULL;
}

// 将容器 a 以其第一个元素为界重新排列，小于第一个的在 a1 之前，大于的在之后。
void Rank(vector<int> &vec)
{
    int i, j;
    DataType a = vec[0];
    i = 0;
    j = vec.size() - 1;
    while (i < j)
    {
        while ((i < j) && (vec[j] >= a))
            j--;
        vec[i] = vec[j];
        while ((i < j) && (vec[i] <= a))
            i++;
        vec[j] = vec[i];
    }
    vec[i] = a;
}

// 传引用交换两数的值
// 如果要重构，比如重新命名函数，就将光标放在函数名上，按 F2 ，即可实现所有位置的重构。
void quote_exchange(int &num1, int &num2)
{
    int temp;
    temp = num1;
    num1 = num2;
    num2 = temp;
}

void pointer_exchange(int *num1, int *num2)
{
    int temp;
    temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}