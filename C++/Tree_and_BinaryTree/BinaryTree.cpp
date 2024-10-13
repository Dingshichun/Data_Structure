// 二叉树

// 二叉树的每个结点最多有两棵子树，子树有左右之分

// 二叉树也可以用递归的形式定义，即二叉树是 n(n≥0) 个结点的有限集合。
// 当 n=0 时，称为空二叉树；
// 当 n>0 时，有且仅有一个结点为二叉树的根，其余结点被分成两个互不相交的子集，
// 一个作为左子集，另一个作为右子集，每个子集又是一个二叉树。

// （1）二叉树的顺序存储
// 一般情况下二叉树是非线性结构，用线性存储难以表达数据之间的从逻辑关系
// 但当二叉树是完全二叉树时，可使用顺序存储，
// 将完全二叉树按照从上到下、从左到右的顺序进行编号，依次存入连续的存储单元

#include <iostream>
#include "Stack.cpp"
using namespace std;
typedef int Datatype;
#define maxsize 100

class QbTree
{
public:
    Datatype elem[maxsize]; // 根存储在下标为 1 的数组单元中
    int n;                  // 当前完全二叉树的结点个数
    void CreatBTree(int m); // 构造一棵完全二叉树
    int LeftChild(int i);   // 获取给定结点的左孩子
    int RightChild(int i);  // 获取给定结点的右孩子
    int Parent(int i);      // 获取给定结点的双亲
};

// （2）二叉树的链式存储
// 顺序存储，当二叉树不是完全二叉树时，为了体现数据之间的关系，
// 会空出许多位置，浪费空间

// 二叉树的数据结点一般包括数据域 data、左指针域 left、右指针域 right
class BinTreeNode
{
public:
    Datatype data;
    BinTreeNode *LeftChild;
    BinTreeNode *RightChild;
    BinTreeNode() // 构造一个空结点
    {
        LeftChild = NULL;
        RightChild = NULL;
    }
};

class BinaryTree
{
public:
    BinTreeNode *root;
    BinaryTree()
    {
        root = NULL;
    }
    ~BinaryTree() { DeleteTree(); }
    bool InsertLeft(BinTreeNode *current, Datatype x);  // 将 x 插入作为 current 结点的左孩子
    bool InsertRight(BinTreeNode *current, Datatype x); // 将 x 插入作为 current 结点的右孩子

    void PreOrder_Recur(BinTreeNode *current);  // 先序遍历，使用递归
    void PreOrder_Stack(BinTreeNode *current);  // 先序遍历，使用栈
    void InOrder_Recur(BinTreeNode *current);   // 中序遍历，使用递归
    void InOrder_Stack(BinTreeNode *current);   // 中序遍历，使用栈
    void PostOrder_Recur(BinTreeNode *current); // 后序遍历，使用递归
    void PostOrder_Stack(BinTreeNode *current); // 后序遍历，使用栈

    BinTreeNode *Find(BinTreeNode *current, Datatype x); // 从结点 current 开始查找值为 x 的结点
    void Destroy(BinTreeNode *current);                  // 删除指定子树
    void DeleteTree()                                    // 删除整棵树
    {
        Destroy(root);
        root = NULL;
    }
    bool IsEmpty() { return root == NULL; }      // 判断二叉树是否为空
    BinTreeNode *CreatBinTree();                 // 创建一棵二叉树
    int Height(BinTreeNode *current);            // 计算二叉树的高度
    BinTreeNode *CopyTree(BinTreeNode *current); // 将链式存储的二叉树复制为另外一棵树
};

// 将 x 插入作为 current 结点的左孩子
bool BinaryTree::InsertLeft(BinTreeNode *current, Datatype x)
{
    if (current == NULL)
        return false;
    BinTreeNode *p = new BinTreeNode;
    p->data = x;
    current->LeftChild = p;
    return true;
}

// 将 x 插入作为 current 结点的右孩子
bool BinaryTree::InsertRight(BinTreeNode *current, Datatype x)
{
    if (current == NULL)
        return false;
    BinTreeNode *p = new BinTreeNode;
    p->data = x;
    current->RightChild = p;
    return true;
}

// 删除指定子树
void BinaryTree::Destroy(BinTreeNode *current)
{
    if (current != NULL)
    {
        Destroy(current->LeftChild);
        Destroy(current->RightChild);
        delete current;
    }
}

// 先序遍历，使用递归
void BinaryTree::PreOrder_Recur(BinTreeNode *current)
{
    if (current != NULL)
    {
        cout << current->data << endl;
        PreOrder_Recur(current->LeftChild);  // 遍历左子树
        PreOrder_Recur(current->RightChild); // 遍历右子树
    }
}

/*
// 先序遍历，使用栈。不能使用
void BinaryTree::PreOrder_Stack(BinTreeNode *current)
{
    // SeqStack 在 Stack.cpp 中，需要修改为存储二叉树结点指针的类型这个函数才能运行
    SeqStack S;
    while (current || (!S.IsEmpty()))
    {
        if (current)
        {
            cout << current->data << endl;
            S.Push_Stack(current); // 预留 current 指针在栈中
            current = current->LeftChild;
        }
        else
        {
            // 左子树为空，进右子树
            S.Pop_Stack(current);
            current = current->RightChild;
        }
    }
}
*/

// 中序遍历，使用递归
void BinaryTree::InOrder_Recur(BinTreeNode *current)
{
    if (current != NULL)
    {
        InOrder_Recur(current->LeftChild);
        cout << current->data << endl;
        InOrder_Recur(current->RightChild);
    }
}

/*
// 中序遍历，使用栈
void BinaryTree::InOrder_Stack(BinTreeNode *current)
{
    // SeqStack 在 Stack.cpp 中，需要修改为存储二叉树结点指针的类型这个函数才能运行
    SeqStack S;
    while (current || (!S.IsEmpty()))
    {
        if (current)
        {
            S.Push_Stack(current); // 预留 current 指针在栈中
            current = current->LeftChild;
        }
        else
        {
            // 左子树为空，进右子树
            S.Pop_Stack(current);
            cout << current->data << endl;
            current = current->RightChild;
        }
    }
}
*/
// 后序遍历，使用递归
void BinaryTree::PostOrder_Recur(BinTreeNode *current)
{
    if (current != NULL)
    {
        PostOrder_Recur(current->LeftChild);
        PostOrder_Recur(current->RightChild);
        cout << current->data << endl;
    }
}

/*
// 后序遍历，使用栈
void BinaryTree::PostOrder_Stack(BinTreeNode *current)
{
    // SeqStack 在 Stack.cpp 中，需要修改为存储二叉树结点指针的类型这个函数才能运行
    SeqStack S1; // S1存放结点指针
    SeqStack S2; // S2存放标志flag
    int flag;
    while (current || (!S1.IsEmpty()))
    {
        if (current)
        {
            S1.Push_Stack(current); // current 指针第一次进栈
            S2.Push_Stack(flag);    // 标志 flag 进栈
            current = current->LeftChild;
        }
        else
        {
            S1.Pop_Stack(current); // current 指针出栈
            S2.Pop_Stack(flag);    // 标志 flag 出栈
            if (flag == 0)
            {
                flag = 1;
                S1.Push_Stack(current); // curren 第二次进栈
                S2.Push_Stack(flag);    // 标志 flag 进栈
                current = current->RightChild;
            }
            // 左子树为空，进右子树
            else
            {
                // flag 为 1 说明是第二次出栈，访问结点
                cout << current->data << endl;
                current = NULL;
            }
        }
    }
}
*/

// 从结点 current 开始查找值为 x 的结点
BinTreeNode *BinaryTree::Find(BinTreeNode *current, Datatype x)
{
    if (current == NULL)
        return NULL;
    if (current->data == x)
        return current;

    BinTreeNode *p = Find(current->LeftChild, x);
    if (p != NULL)
        return p;
    else
        return Find(current->RightChild, x);
}

// 计算二叉树的高度
int BinaryTree::Height(BinTreeNode *current)
{
    if (current == NULL)
        return (0);
    else
        return max(Height(current->LeftChild), Height(current->RightChild)) + 1;
}

// 将链式存储的二叉树复制为另外一棵树
BinTreeNode *CopyTree(BinTreeNode *current)
{
    if (current == NULL)
        return NULL;
    BinTreeNode *p = new BinTreeNode;
    p->data = current->data;
    p->LeftChild = CopyTree(p->LeftChild);
    p->RightChild = CopyTree(p->RightChild);
    return p;
}
