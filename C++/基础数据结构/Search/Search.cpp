// 查找

// 无序查找。主要是顺序查找

// （1）二分查找

// 有序查找。通常是折半查找，也叫二分查找
// 其基本思想是：设表中的结点按关键字递增有序，
// 首先将待查值 k 和表中间位置上的结点关键字进行比较，若两者相等，则查找成功；
// 否则，若 k 值小，则在表的前半部分继续利用折半查找法查找，
// 若 k 值大，则在表的后半部分继续利用折半查找法查找。
// 这样，经过一次关键字比较就缩小一半的查找区间，
// 如此进行下去，直到查找到该关键字或查找失败。

// 二分查找也可以用二叉树描述

typedef int DataType;

// 求长度的模板
template <class T>
int length(T &arr)
{
    return (sizeof(arr) / sizeof(arr[0]));
}

// 二分查找，参数分别为数组、长度、查找值
int BinSearch(int arr[], int len, DataType k)
{
    int low, mid, high;
    low = 0;
    high = len - 1;
    while (low <= high)
    {
        mid = (low + high) / 2; // 注意数组下标是从 0 开始的
        if (arr[mid] == k)
            return (mid);
        else if (arr[mid] > k)
            high = mid - 1;
        else
            low = mid + 1;
    }
    return (-1); // 查找失败
}

// 二分查找的递归实现。参数分别为数组、第一位序号、第二位序号、查找的值
int Recur_BinSearch(int arr[], int low, int high, DataType k)
{
    if (low > high)
        return (-1);
    int mid;
    mid = low + (high - low) / 2; // 注意数组下标是从 0 开始的
    if (arr[mid] == k)
        return (mid);
    else if (arr[mid] > k)
        // 在左半部分递归查找
        return Recur_BinSearch(arr, low, mid - 1, k);
    else
        // 在右半部分递归查找
        return Recur_BinSearch(arr, mid + 1, high, k);

    return (-1); // 查找失败
}

// （2）动态查找表

// 静态查找，主要适用于顺序表结构，并且对表中的结点仅做查找操作，而不做插入和删除操作。
// 动态查找不仅要查找结点，还要不断地插入和删除结点。
// 当表采用顺序结构时，这需要花费大量的时间用于结点的移动，效率很低。

// 用树结构存储结点的动态查找算法，即树表。
// 树表本身也是在查找过程中动态生成的。
// 树表主要有二叉排序树、平衡二叉树、B- 树和 B+ 树等。

// （2.1）二叉排序树

// 二叉排序树又称二叉查找树，它或者是一棵空树，或者是具有以下性质的二叉树：
// 若任一结点的左子树非空，则左子树中的所有结点的值都不大于根结点的值；
// 若任一结点的右子树非空，则右子树中的所有结点的值都不小于根结点的值。

// 对二叉排序树进行中序遍历就可得到集合中所有记录按关键字从小到大的一个递增有序序列。

#include <iostream>
using namespace std;

// 二叉排序树的结点类
class BinSTreeNode
{
public:
    DataType data;
    BinSTreeNode *Lchild;
    BinSTreeNode *Rchild;
    BinSTreeNode()
    {
        Lchild = NULL;
        Rchild = NULL;
    }
};

class BinSTree
{
public:
    BinSTreeNode *root;
    BinSTree() { root = NULL; }
    ~BinSTree() { DeleteTree(); }
    void Destroy(BinSTreeNode *current); // 删除指定子树
    void DeleteTree()                    // 删除整棵树
    {
        Destroy(root);
        root = NULL;
    }

    // 二叉排序树的查找
    BinSTreeNode *BSTreeSearch(BinSTreeNode *bt, DataType k, BinSTreeNode *&p);
    void BSTreeInsert(BinSTreeNode *&bt, DataType k); // 二叉排序树的插入
    int BSTreeDelete(BinSTreeNode *&bt, DataType k);  // 二叉排序树的删除
    bool IsEmpty() { return (root == NULL); }         // 判断树是否空
};

// 二叉排序树的查找
// 在根指针为 bt 的二叉排序树中查找元素 k ，查找成功，则返回指向该结点的指针，
// 参数 p 指向查找到的结点，否则返回空指针，参数 p 指向 k 应插入的父结点，
// p 是指针的引用
BinSTreeNode *BinSTree::BSTreeSearch(BinSTreeNode *bt, DataType k, BinSTreeNode *&p)
{
    BinSTreeNode *q;
    q = bt;    // 从根结点开始
    while (bt) // 根结点不为空时
    {
        q = bt;
        if (bt->data == k) // 查找到 k
        {
            p = bt; // p 是元素 k 所在结点的地址
            return (bt);
        }
        if (bt->data > k) // 所查结点存储的值大于 k ，则在左子树继续查找
            bt = bt->Lchild;
        else // 所查结点存储的值小于 k ，则在右子树继续查找
            bt = bt->Rchild;
    }
    p = q; // p 保存查找值所在结点的地址，若根指针 bt 为空，那么 p 也为空
    return (bt);
}

// 二叉排序树的插入。插入元素 k ，bt 指向二叉排序树的根结点
// 插入的结点一定是一个新添加的叶子结点
void BinSTree::BSTreeInsert(BinSTreeNode *&bt, DataType k)
{
    // p 用来保存查询 k 是否在二叉树中的结果，初始化为空
    // q 指向根结点 bt
    BinSTreeNode *p = NULL, *q;
    q = bt;

    // 在二叉树中没有查到 k 。可能树为空，也可能树不为空，但没有元素 k
    if (BSTreeSearch(q, k, p) == NULL)
    {
        // 创建插入的结点 en_node
        BinSTreeNode *en_node = new BinSTreeNode;
        en_node->data = k;
        en_node->Lchild = NULL;
        en_node->Rchild = NULL;
        if (p == NULL) // 二叉树为空时，被插入的结点作为树的根结点
            bt = en_node;
        else if (k < p->data) // 二叉树不为空时，分情况插入
            p->Lchild = en_node;
        else
            p->Rchild = en_node;
    }
}

// 在二叉排序树中删除元素为 k 的结点，*bt 指向二叉排序树的根结点。
// 删除成功则返回 1 ,不成功则返回 0
int BinSTree::BSTreeDelete(BinSTreeNode *&bt, DataType k)
{
    BinSTreeNode *f, *p, *q, *s;
    p = bt;
    f = NULL;
    while (p && p->data != k) // 查找关键字为k的结点，同时将此结点的双亲找出来
    {
        f = p; // f 为指向结点 *p 的双亲结点的指针
        if (p->data > k)
            p = p->Lchild; // 搜索左子树
        else
            p = p->Rchild; // 搜索右子树
    }
    if (p == NULL)
        return (0);        // 找不到待删的结点时返回
    if (p->Lchild == NULL) // 待删结点的左子树为空
    {
        if (f == NULL)
            bt = p->Rchild; // 待删结点为根结点
        else if (f->Lchild == p)
            f->Lchild = p->Rchild; // 待删结点是其双亲结点的左结点
        else
            f->Rchild = p->Rchild; // 待删结点是其双亲结点的右结点
        delete p;
        return 1;
    }
    else
    { // 待删结点有左子树
        q = p;
        s = p->Lchild;
        while (s->Rchild) // 在待删结点的左子树中查找最右下结点
        {
            q = s;
            s = s->Rchild;
        }
        if (q == p)
            q->Lchild = s->Lchild; // 将最右下结点的左子树链到待删结点上
        else
            q->Rchild = s->Lchild;
        p->data = s->data;
        delete s;
        return 1;
    }
}

// （3）平衡二叉树（AVL树）

// 二叉排序树的查找效率和树的形态密切相关。当树的形态比较均衡时，查找效率最好；
// 而当树的形态明显偏向某一个方向时，查找效率会迅速下降。
// 而一棵二叉排序树的形态取决于结点的插入顺序，
// 因此在实际应用中，用前面所述的方法构造一棵比较均衡的二叉排序树是比较困难的。

// 平衡二叉树是 Adelson-Velskii 和 Landis 在 1962 年提出的，所以又称 AVL 树。
// 其性质是：或者是一棵空树，或者是满足下列性质的二叉树；
// 树的左子树和右子树的深度之差的绝对值不大于 1，且左、右子树也需满足上述性质。
// 把二叉树上任一结点的左子树深度减去右子树的深度称为该结点的平衡因子。
// 易知，平衡二叉树中所有结点的因子只可能为 0、-1 和 1。

// 一棵树既是平衡二叉树，又是二叉排序树，则该树就叫平衡二叉排序树

// 平衡二叉排序树的存储结构如下

// 平衡二叉排序树结点类型
class AVLNode
{
public:
    DataType data;   // 数据域
    int bf;          // 平衡因子（结点的左子树深度减去右子树的深度）
    AVLNode *Lchild; // 左右指针域
    AVLNode *Rchild;
    AVLNode() // 构造空结点
    {
        Lchild = NULL;
        Rchild = NULL;
    }
};

// 平衡二叉排序树
class AVLTree
{
public:
    AVLNode *root;
    AVLTree() { root = NULL; }
    ~AVLTree() { DeleteTree(); }

    // 四种调整方式
    AVLNode *LL_Rotate(AVLNode *a);
    AVLNode *RR_Rotate(AVLNode *a);
    AVLNode *LR_Rotate(AVLNode *a);
    AVLNode *RL_Rotate(AVLNode *a);

    void AVLInsert(AVLNode *&pavlt, AVLNode *s); // 插入一个新结点
    void Destroy(AVLNode *current);              // 删除指定子树
    void DeleteTree()                            // 删除整棵树
    {
        Destroy(root);
        root = NULL;
    }
    bool IsEmpty() { return (root == NULL); }
};
// 由于在结点 A 的左孩子（L）的左子树（L）中插入结点，
// 结点 A 的平衡因子由 1 变为 2 而失去平衡。

// 对以 a 为当前结点的最小不平衡子树进行 LL 型调整
AVLNode *AVLTree::LL_Rotate(AVLNode *a)
{
    AVLNode *b;            // 结点指针 b
    b = a->Lchild;         // b 指向 a 的左子树的根结点
    a->Lchild = b->Rchild; // 将 b 的右子树挂接为 a 的左子树
    b->Rchild = a;         // 将 b 作为根节点，将 a 挂接为 b 的右子树
    a->bf = b->bf = 0;     // 调整平衡因子
    return (b);            // 返回根节点
}

// 由于在结点 A 的右孩子（R）的右子树（R）中插入结点，
// 结点 A 的平衡因子由 -1 变为 -2 而失去平衡。

// 对以 a 为当前结点的最小不平衡子树进行 RR 型调整
AVLNode *AVLTree::RR_Rotate(AVLNode *a)
{
    AVLNode *b;            // 结点指针 b
    b = a->Rchild;         // b 指向 a 的右子树的根结点
    a->Rchild = b->Lchild; // 将 b 的左子树挂接为 a 的右子树
    b->Lchild = a;         // 将 b 作为根节点，将 a 挂接为 b 的左子树
    a->bf = b->bf = 0;     // 调整平衡因子
    return (b);            // 返回根节点
}

// 由于在结点 A 的左孩子（L）的右子树（R）中插入结点，
// 结点 A 的平衡因子由 1 变为 2 而失去平衡。

// 对以 a 为当前结点的最小不平衡子树进行 LR 型调整
AVLNode *AVLTree::LR_Rotate(AVLNode *a)
{
    AVLNode *b, *c;
    b = a->Lchild;         // b 是最小不平衡子树的根结点 a 的左结点
    c = a->Lchild->Rchild; // c 是 b 的右结点
    b->Rchild = c->Lchild; // 将 c 的左子树挂接为 b 的右子树
    a->Lchild = c->Rchild; // 将 c 的右子树挂接为 a 的左子树
    c->Lchild = b;         // 将 c 作为根结点，其左右结点分别为 b 和 a
    c->Rchild = a;

    // 不同插入情况的平衡因子
    if (c->bf == 1)
    {
        a->bf = -1;
        b->bf = 0;
    }
    else if (c->bf = -1)
    {
        a->bf = 0;
        b->bf = 1;
    }
    else
    {
        a->bf = b->bf = 0;
    }
    c->bf = 0;
    return (c);
}

// 由于在 A 的右孩子（R）的左子树（L）中插入结点，
// A 的平衡因子由 -1 变为 -2 而失去平衡。

// 对以 a 为当前结点的最小不平衡子树进行 RL 型调整
AVLNode *AVLTree::RL_Rotate(AVLNode *a)
{
    AVLNode *b, *c;
    b = a->Rchild;         // b 是最小不平衡子树的根结点 a 的右结点
    c = a->Rchild->Lchild; // c 是 b 的左结点
    a->Rchild = c->Lchild; // 将 c 的左子树挂接为 a 的右子树
    b->Lchild = c->Rchild; // 将 c 的右子树挂接为 b 的左子树
    c->Lchild = a;         // 将 c 作为根结点，其左右结点分别为 a 和 b
    c->Rchild = b;

    // 调整结点的平衡因子
    if (c->bf == 1)
    {
        a->bf = 0;
        b->bf = -1;
    }
    else if (c->bf == -1)
    {
        a->bf = 1;
        b->bf = 0;
    }
    else
    {
        a->bf = b->bf = 0;
    }
    c->bf = 0;
    return (c);
}

// 将结点 s 插入以 *pavlt 为根结点的平衡二叉排序树中
void AVLTree::AVLInsert(AVLNode *&pavlt, AVLNode *s)
{
    AVLNode *f, *a, *b, *p, *q;
    if (pavlt == NULL) // AVL 树为空
    {
        pavlt = s;
        return;
    }
    a = pavlt;
    f = NULL; // 指针 a 记录离 *s 最近的平衡因子不为0的
              // 结点，f 指向 *a 的父结点
    p = pavlt;
    q = NULL;
    while (p != NULL) // 寻找插入结点的位置及最小不平衡子树
    {
        if (p->data == s->data)
            return;     // AVL 树中已存在该关键字
        if (p->bf != 0) // 寻找最小不平衡子树
        {
            a = p;
            f = q;
        }
        q = p;
        if (s->data < p->data)
            p = p->Lchild;
        else
            p = p->Rchild;
    }
    if (s->data < q->data) // 将结点 *s 插入合适的位置
        q->Lchild = s;
    else
        q->Rchild = s;
    p = a;
    while (p != s) // 插入结点后，修改相关结点的平衡因子
    {
        if (s->data < p->data)
        {
            p->bf++;
            p = p->Lchild;
        }
        else
        {
            p->bf--;
            p = p->Rchild;
        }
    }
    if (a->bf > -2 && a->bf < 2)
        return; // 插入结点后，没有破坏树的平衡性
    if (a->bf == 2)
    {
        b = a->Lchild;
        if (b->bf == 1)       // 结点插在 *a 的左孩子的左子树中
            p = LL_Rotate(a); // LL型调整
        else                  // 结点插在 *a 的左孩子的右子树中
            p = LR_Rotate(a); // LR型调整
    }
    else
    {
        b = a->Rchild;
        if (b->bf == 1)       // 结点插在 *a 的右孩子的左子树中
            p = RL_Rotate(a); // RL 型调整
        else                  // 结点插在 *a 的右孩子的右子树中
            p = RR_Rotate(a); // RR 型调整
    }
    if (f == NULL) // 原 *a 是 AVL 树的根
        pavlt = p;
    else if (f->Lchild == a) // 将新子树链到原结点 *a 的双亲结点上
        f->Lchild = p;
    else
        f->Rchild = p;
}