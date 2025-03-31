// （1）树的双亲表示法
// 采用的是顺序存储。它的特点是寻找结点的双亲很容易，但寻找结点的孩子比较困难。

#include <iostream>
using namespace std;
typedef int DataType;
#define MAXSIZE 100

class TreeNode
{
public:
    DataType data;
    int parent; // 父结点在顺序表中的位置
};

class Tree
{
public:
    TreeNode elem[MAXSIZE];
    int n; // 树中当前的结点数目
} Tree;

// （2）树的孩子表示法

// 由于每个结点的孩子个数不定，所以利用链式存储结构更加适宜。
// 对每个结点建立一个链表，链表中的元素就是头结点的孩子。
// n 个结点就有 n 个链表，如何管理这些链表呢？
// 最好的方法是将这些链表的头结点放在一个一维数组中。

class link
{
public:
    int child;  // 孩子序号
    link *next; // 下一个孩子指针
};

class node
{
public:
    DataType data; // 结点信息
    link *first;   // 指向第一个孩子
};

class tree
{
public:
    int n; // 结点个数
    node T[MAXSIZE];
};

// （3）孩子兄弟表示法

// 通过描述每个结点的一个孩子和兄弟信息来反映结点之间的层次关系，
// firstchild 为指向该结点第一个孩子的指针，
// nextbrother 为指向该结点的下一个兄弟，
// elem 是数据元素内容。

// （4）树、森林和二叉树的转换

// 从树的孩子兄弟表示法可以看到，如果设定一定规则，就可用二叉树结构表示树和森林。
// 这样，对树的操作实现就可以借助二叉树存储，利用二叉树上的操作来实现。

// 将一棵树转换为二叉树的方法如下：
// 1）树中所有相邻兄弟之间加一条连线。
// 2）对树中的每个结点，只保留它与第一个孩子结点之间的连线，删去它与其他孩子结点之间的连线。
// 3）以树的根结点为轴心，将整棵树顺时针转动一定的角度，使之结构层次分明。

// 由森林的概念可知，森林是若干棵树的集合。
// 只要将森林中各棵树的根视为兄弟，每棵树又可以用二叉树表示。
// 这样，森林也同样可以用二叉树表示。

// 森林转换为二叉树的方法如下：
// 1）将森林中的每棵树转换成相应的二叉树。
// 2）第一棵二叉树不动，从第二棵二叉树开始，依次把后一棵二叉树的根结点作为前一棵二叉树根结点的右孩子。
// 当所有二叉树连起来后，此时所得到的二叉树就是由森林转换得到的二叉树。

// （5）哈夫曼树
// 简单说就是出现次数多的元素放在二叉树的前面，出现次数少的放在二叉树的后面。

// Huffman 针对如何减少通信系统中字符编码所需的二进制位长度，
// 提出用于产生不定长的前缀码算法（所谓前缀编码，是指任一编码都不是其他编码的前缀）​。
// 其基本思想就是对于出现概率较大的字符采用短编码方式，而出现概率较小的字符采用长编码方式。
// Huffman 提出的算法能够使得其构造出的二叉树的 WPL 值最小，
// 从而保证在通信过程中，传输二进制位总长度最短。
// 该算法主要是根据给定的不同字符的出现概率（频率）建立一棵最优二叉树。
// 通常，该算法被称作哈夫曼（Huffman）算法，而对应的最优二叉树称为哈夫曼树。

// 这里将介绍如何利用顺序表（其实是静态链表）来实现哈夫曼树的存储表示和实现方法，
// weight 域存放结点的权值；
// parent 域存放父结点在顺序表中的位置，其中根结点的 parent 值为 -1 ;
// lchild 域存放结点的左孩子在顺序表中的位置，若结点无左孩子，则 lchild 值为 -1 ;
// rchild 域存放结点的右孩子在顺序表中的位置，若结点无右孩子，则 rchild 值为 -1 。

const unsigned int n = 100;       // 假设字符数为 100
const unsigned int m = 2 * n - 1; // 结点总数

struct HTNode // 压缩用哈夫曼树结点
{
    float weight; // 权值
    int parent;   // 双亲
    int lchild;   // 左右孩子
    int rchild;
};

class HuffmanTree
{
public:
    HTNode HT[m + 1]; // 树结点表，HT[1] 到 HT[m+1]

public:
    HuffmanTree();
    ~HuffmanTree();

    // 在 HT[1] 到 HT[k] 选择 parent 为 -1 ，权值最小的两个结点 s1 和 s2
    void select(int k, int &s1, int &s2);
};

HuffmanTree::HuffmanTree()
{
    int i, j;
    int s1, s2;
    for (int i = 1; i <= m; i++) // 初始化静态链表
    {
        HT[i].weight = 0;
        HT[i].parent = -1;
        HT[i].lchild = -1;
        HT[i].rchild = -1;
    }
    cout << "输入权值：" << endl;
    for (int i = 1; i <= n; i++)
        cin >> HT[i].weight;         // 输入权值
    for (int i = n + 1; i <= m; i++) // 建Huffman树
    {
        select(i - 1, s1, s2); // 选择 parent 为 -1 且 weight 最小的两个
                               // 结点，其序号分别为：s1 和 s2
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}
void HuffmanTree::select(int k, int &s1, int &s2)
{                         // 在k个元素中选择parent为-1且权值最小的两个结点，其序号分别为s1和s2
    HT[0].weight = 32767; // 设置最大数
    s1 = s2 = 0;
    for (int i = 1; i <= k; i++)
        if ((HT[i].weight != 0) && HT[i].parent == -1)
        {
            if (HT[i].weight < HT[s1].weight)
            {
                s2 = s1;
                s1 = i;
            }
            else if (HT[i].weight < HT[s2].weight)
                s2 = i;
        }
}