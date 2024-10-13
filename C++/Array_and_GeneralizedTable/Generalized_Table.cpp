// 广义表

// 线性表中数据元素的类型必须是相同的，而且只能是原子项。
// 如果允许表中的数据元素具有自身结构，
// 即数据元素也可以是一个线性表，这就是广义表，有时也称之为列表（Lists）​。

// 由于广义表（a1,a2, …,an）中的元素不是同一类型，
// 可以是原子元素，也可以是子表，因此很难用顺序结构存储。

// 通常采用模拟线性链式存储方法来存储广义表。
// 广义表中的每个元素由一个结点表示。
// 该结点既可表示原子元素，又可表示子表。为区分两者，可用一个标志位 tag 来区分。

// 当 tag=0 时，原子结点由标志域 tag 、值域 data 构成；
// 当 tag=1 时，表结点由标志域 tag 、指向表头的指针域 hp 和指向表尾的指针域 tp 三部分构成。

#include <iostream>
using namespace std;
typedef int DataType;

// 广义表的结点定义
typedef struct GenNode
{
    int tag; // 标志域
    union    // 联合体
    {
        DataType data; // 数据域
        struct
        {
            struct GenNode *hp, *tp; // 指向表头和表尾的指针
        } ptr;                       // ptr是一个实例对象
    }; // 这里要加分号
};

// 创建广义表
class Glist
{
public:
    GenNode *first;
    Glist() { first = NULL; }; // 构造函数
    ~Glist();                  // 析构函数

    GenNode *GetHead();              // 取广义表表头
    GenNode *GetTail();              // 取广义表表尾
    GenNode *GetFirst();             // 取广义表的第一个元素
    GenNode *GetNext(GenNode *elem); // 取广义表的元素 elem 后继

    int depth(GenNode *ls);            // 求广义表的深度
    int equal(GenNode *s, GenNode *t); // 判断两个表是否相等
};

// 任何一个非空广义表的表头是表中第一个元素，
// 它可能是原子，也可能是广义表，而其表尾必定是广义表。

// 取广义表表头
GenNode *Glist::GetHead()
{
    // 若广义表非空，则返回指向第一个元素的指针，否则返回空
    if ((first == NULL) || (first->tag == 0))
    {
        cout << "是空表或是单个原子" << endl;
        return NULL;
    }
    return first->ptr.hp;
}

// 取广义表表尾
GenNode *Glist::GetTail()
{
    // 空表或是单个原子，函数无意义，否则返回表尾指针
    if ((first == NULL) || (first->tag == 0))
    {
        cout << "是空表或是单个原子" << endl;
        return NULL;
    }
    return first->ptr.tp;
}

// 使用递归求广义表的深度
int Glist::depth(GenNode *ls)
{
    // 元素是原子类型，则深度为 0 ，元素是空表，则深度为 1
    if (ls == NULL) // 空表
        return (1);
    GenNode *temp = ls; // 新建指针
    if (temp->tag == 0) // 元素是原子类型
        return 0;
    int max = 0;
    while (temp != NULL) // 广义表非空
    {
        int dep = depth(temp->ptr.hp);
        if (dep > max)
            max = dep;
        temp = temp->ptr.tp;
    }
    return (max + 1); // 返回表的深度
}