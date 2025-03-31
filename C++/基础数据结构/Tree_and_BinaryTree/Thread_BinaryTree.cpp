// （3）线索二叉树

// 在二叉树中经常会求解某结点在某种次序下的前驱或后继结点，
// 各结点在每种次序下的前驱、后继的差异较大。

// 有以下几种方法：
// （一）直接从头开始遍历。费时
// （二）在每个结点中增设前驱和后继指针，分别指示该结点在指定次序下的前驱和后继
//      但是以额外的空间作为代价
// （三）利用二叉链表中的空指针域，将二叉链表中的空的指针域改为指向其前驱和后继。
//      在每个结点中需再引入两个区分标志 ltag 和 rtag ，并且约定如下。
//      ltag=0:lchild 指示该结点的左孩子。
//      ltag=1:lchild 指示该结点的前驱。
//      rtag=0:rchild 指示该结点的右孩子。
//      rtag=1:rchild 指示该结点的后继。

#include <iostream>
using namespace std;

// 线索二叉树的结点，继承自 BinaryTree.cpp 中的 BinTreeNode
class ThreadNode
{
public:
    int data;
    ThreadNode *LeftChild;
    ThreadNode *RightChild;
    int ltag, rtag; // 左右标志
    ThreadNode()    // 默认构造函数
    {
        LeftChild = NULL;
        RightChild = NULL;
        ltag = 0;
        rtag = 0;
    }
};

// 中序线索化二叉树
class ThreadTree
{
public:
    ThreadNode *root;                                 // 根结点指针
    ThreadTree() { root = NULL; }                     // 构造函数
    ~ThreadTree() { DeleteTree(root); }               // 析构函数
    void DeleteTree(ThreadNode *root);                // 删除线索化二叉树
    void InThread(ThreadNode *root);                  // 非递归中序线索化二叉树
    void InThread(ThreadNode *root, ThreadNode *pre); // 递归中序线索化二叉树
    void InOrder(ThreadNode *root);                   // 中序遍历中序线索化二叉树
};

// 递归中序线索化二叉树
void ThreadTree::InThread(ThreadNode *root)
{
    static ThreadNode *pre = NULL;
    if (root != NULL)
    {
        // 这里调用的是上面声明的递归中序线索化二叉树函数，
        // 但是这个函数只进行了声明，没定义，所以不能运行
        InThread(root->LeftChild, pre); // 中序线索化左子树
        if (root->LeftChild == NULL)
        {
            // 建立前驱线索
            root->ltag = 1;
            root->LeftChild = pre;
        }
        if ((pre) && (pre->RightChild) == NULL)
        {
            // 建立后继线索
            pre->rtag = 1;
            pre->RightChild = root;
        }
        pre = root;
        InThread(root->RightChild, pre); // 中序线索化右子树
    }
}