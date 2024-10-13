// 图
// 有向图、无向图

// 在一个无向图中，如果任意两个顶点都有一条直接边相连接，
// 则称该图为无向完全图（Undireted Complete Graph）​。

// 在一个有向图中，如果任意两个顶点之间都有方向互为相反的两条弧相连接，
// 则称该图为有向完全图（Directed Complete Graph）​。

// 顶点的度（Degree）是指依附于某顶点 v 的边数，通常记为 D(v)。
// 在有向图中，要区别顶点的入度与出度的概念。
// 顶点 v 的入度（Indegree）是指以顶点 v 为终点的弧的数目，记为 ID(v)；
// 顶点 v 出度（Outdegree）是指以顶点 v 为始点的弧的数目，记为 OD(v)。

// 连通
// 在无向图中，如果从一个顶点 vi 到另一个顶点 vj（i≠j）有路径，则称顶点 vi 和 vj 是连通的。
// 如果图中任意两个顶点都是连通的，则称该图是连通图（Connected Graph）​。
// 无向图的极大连通子图称为连通分量（Connected Component）​。
// 基本特征表现为：顶点数达到极大，如果再增加一个顶点就不再连通。

// 图的存储。重点
// 包括邻接矩阵和邻接表

// （1）邻接矩阵
// 包含 n 个顶点的图，其邻接矩阵大小为 n*n ，
// 对于无权图，元素为 A[i][j] ，当顶点 i 和 j 之间有边或弧时，A[i][j]=1 ，没有则为 0 。
// 对有权图，元素为 A[i][j] ，当顶点 i 和 j 之间有边或弧时，A[i][j]=权值 ，
// 对角线位置的 A[i][j]=0 ，没有边或弧时， A[i][j]=无穷，

// 图的邻接矩阵是对称矩阵，只需要存储其上三角或下三角

// 在用邻接矩阵存储图时，除了用一个二维数组存储用于表示顶点间相邻关系的邻接矩阵外，
// 还需用一个一维数组存储顶点信息，另外还有图的顶点数和边数。

#include <iostream>
#include "Queue.cpp"
using namespace std;
typedef int VertexType;
typedef int EdgeType;
#define MaxVertexNum 30

class MatrixGraph
{
public:
    MatrixGraph();                // 默认构造函数
    ~MatrixGraph();               // 默认析构函数
    void CreatGraph();            // 建立无权图的存储矩阵成员函数
    void Visit(int v);            // 访问顶点 v
    void BFStraverse();           // 广度遍历图
    void BFS(int v);              // 从顶点 v 开始广度遍历
    int MaxOutDegree();           // 最大出度
    int IsPath_DFS(int i, int j); // 以深度优先遍历方法判断顶点之间是否有路径
    int IsPath_BFS(int i, int j); // 以广度优先遍历方法判断顶点之间是否有路径
    void Init_Visit_Flag();       // 初始化访问数组标志

private:
    VertexType vertexs[MaxVertexNum];          // 存储顶点的表
    EdgeType arcs[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，即边表
    int vertexNum, edgeNum;                    // 顶点数和边数
    int visited[MaxVertexNum];                 // 访问标志数组
};

void MatrixGraph::CreatGraph()
{
    int i, j, k;
    cin >> vertexNum >> edgeNum;    // 输入顶点数和边数
    for (i = 0; i < vertexNum; i++) // 建立顶点表
        cin >> vertexs[i];
    for (i = 0; i < vertexNum; i++) // 初始化邻接矩阵所有元素为 0
    {
        for (j = 0; j < vertexNum; j++)
            arcs[i][j] = 0;
    }
    for (k = 0; k < edgeNum; k++)
    {
        cin >> i >> j;  // 输入边，建立邻接矩阵
        arcs[i][j] = 1; // 若再加入 arcs[j][i]=1 则表示无向图的邻接矩阵存储建立
    }
}

// （2）邻接表
// 将每个顶点的邻接顶点分别存储在对应的单链表中，这个单链表就叫邻接表
// 再将所有邻接表的表头放到数组中，就构成了图的邻接表，
// 其中，单链表中的结点称为表结点，每个单链表设的一个头结点称为顶点结点。

// 顶点结点结构，由顶点域（vertex）和指向第一条邻接边的指针域（firstedge）构成；
// 另一种是表结点结构，它由邻接点域（adjvertex）和指向下一条邻接边的指针域（next）构成。
// 对于带权图的边表，需再增设一个存储边上信息（如权值等）的域（info）​。

typedef int InfoType;

typedef struct node // 表结点
{
    int adjVertex;     // 邻接点域，一般存放顶点对应的序号或顶点在表头向量中的下标
    InfoType info;     // 和边（或弧）相关的信息
    struct node *next; // 指向下一邻接点的指针域
} EdgeNode;            // 定义别名

typedef struct vnode // 顶点结点
{
    VertexType vertex;   // 顶点域
    EdgeNode *firstEdge; // 边表头指针
} VertexNode;

class ALGraph // 以邻接表方式存储的图类型
{
public:
    void CreatALGraph();
    void DFStraverse(); // 深度遍历
    void DFS(int v);    // 从顶点 v 开始深度遍历
    void BFS(int v);    // 从顶点 v 开始广度遍历
    void Visit(int v);  // 访问结点 v

private:
    VertexNode adjList[MaxVertexNum]; // 邻接表
    int vertexNum, edgeNum;           // 结点数和边数
    int visited[MaxVertexNum];        // 访问标志数组
};

void ALGraph::CreatALGraph()
{
    int i, j, k;
    EdgeNode *p;
    cout << "请输入顶点数和边数" << endl;
    cin >> vertexNum >> edgeNum;    // 输入顶点数和边数
    for (i = 0; i < vertexNum; i++) // 建立顶点表
    {
        cout << "请输入第" << i << "个顶点信息" << endl;
        cin >> adjList[i].vertex;    // 输入顶点信息
        adjList[i].firstEdge = NULL; // 顶点的边表头指针设为空
    }
    cout << "下面输入边表的信息" << endl;
    for (k = 0; k < edgeNum; k++) // 建立边表
    {
        cout << "输入边<i,j>对应的顶点编号 i,j" << endl;
        cin >> i >> j;    // 读入边<vi,vj>的顶点对应序号
        p = new EdgeNode; // 生成新边表结点 p
        p->adjVertex = j; // 邻接点序号为 j

        // 将新边表结点 p 插入顶点 vi 的链表头部
        p->next = adjList[i].firstEdge;
        adjList[i].firstEdge = p;
    }
}

// （3）十字链表
// 是邻接表与逆邻接表的结合，
// 即把每一条弧的两个结点分别组织到以弧尾顶点为头结点的链表和以弧头顶点为头结点的链表中。

// 在弧结点中有 5 个域，
// 其中尾域（tailvertex）和头域（headvertex）分别指示弧尾和弧头这两个顶点在图中的位置，
// 链域 hlink 指向弧头相同的下一条弧，
// 链域 tlink 指向弧尾相同的下一条弧，info 域指向该弧的相关信息。
// 弧头相同的弧在同一链表上，弧尾相同的弧也在同一链表上。

// 弧结点的头结点即为顶点结点。它由 3 个域组成，
// 其中 vertex 域存储和顶点相关的信息，如顶点的名称等，firstin 和 firstout 为两个链域，
// 分别指向以该顶点为弧头或弧尾的第一个弧结点。

typedef struct ArcNode // 弧结点
{
    int tailvertex, headvertex;    // 弧的尾顶点和头顶点的位置
    struct ArcNode *hlink, *tlink; // 弧头和弧尾的链域
    InfoType info;                 // 该弧相关信息的指针
} ArcNode;

typedef struct vertexNode // 顶点结点
{
    VertexType vertex;
    ArcNode *firsIn, *firsOut; // 指向顶点第一条入弧和出弧的指针
} vertexNode;

class OLGraph
{
public:
    OLGraph() {}
    void CreatOLGraph();
    int LocateVertex(OLGraph &G, int v1); // 定位 v1 在图 G 中的位置

private:
    vertexNode xList[MaxVertexNum]; // 表头向量
    int vertexNum, edgeNum;         // 有向图的顶点数和弧数
};

void OLGraph::CreatOLGraph()
{
    int i, j, k;
    int v1, v2;
    OLGraph G;
    ArcNode *p;
    cin >> vertexNum >> edgeNum;
    for (i = 0; i < vertexNum; i++)
    {
        cin >> xList[i].vertex;
        xList[i].firsIn = NULL;
        xList[i].firsOut = NULL;
    }
    for (k = 0; k < edgeNum; k++)
    {
        cin >> v1 >> v2;

        i = LocateVertex(G, v1);
        j = LocateVertex(G, v2);

        p = new ArcNode;
        p->tailvertex = i;
        p->headvertex = j;

        p->tlink = xList[i].firsOut;
        xList[i].firsOut = p;
        p->hlink = xList[i].firsIn;
        xList[i].firsIn = p;
    }
}

// （4）图的遍历

// 图的遍历操作较为复杂，主要表现在以下四方面。

// 1）在图结构中，没有一个特定的首结点，图中任意一个顶点都可作为第一个被访问的结点。
// 2）在非连通图中，从一个顶点出发，只能访问它所在的连通分量上的所有顶点，
//    因此，还需考虑如何选取下一个出发点以访问图中其余的连通分量。
// 3）在图结构中，如果有回路存在，那么一个顶点被访问之后，有可能沿回路又回到该顶点。
// 4）在图结构中，一个顶点可以和其他多个顶点相连，
//    当这样的顶点访问过后，存在如何选取下一个要访问的顶点的问题。
//    图的遍历通常有深度优先搜索和广度优先搜索两种方式，它们对无向图和有向图都适用。

// （4.1）深度优先搜索
// 类似于树的先序遍历，是树的先序遍历的推广。

void ALGraph::DFStraverse() // 深度优先搜索遍历以邻接表表示的图 G
{
    int v;
    for (v = 0; v < vertexNum; v++)
        visited[v] = false; // 初始化所有访问标志为 false
    for (v = 0; v < vertexNum; v++)
    {
        if (!visited[v]) // 递归遍历未访问的顶点
            DFS(v);
    }
}

void ALGraph::DFS(int v) // 从第 v 个顶点出发深度优先遍历图 G
{
    EdgeNode *p;
    int w;
    Visit(v);
    visited[v] = true; // 访问第 v 个结点，并将其访问标志置为 true
    for (p = adjList[v].firstEdge; p; p->next)
    {
        w = p->adjVertex;
        if (!visited[w]) // 对 v 尚未访问的邻接顶点 w 递归调用 DFS 函数
            DFS(w);
    }
}

// （4.2）广度优先搜索

// 广度优先搜索（Breadth_First Search）遍历类似于树的按层次遍历的过程。

// 假设从图中某顶点 v 出发，在访问 v 之后依次访问 v 的各未曾访问过的邻接点，
// 然后分别从这些邻接点出发依次访问它们的邻接点，
// 并使“先被访问的顶点的邻接点”先于“后被访问的顶点的邻接点”被访问，
// 直至图中所有已被访问的顶点的邻接点都被访问到。若此时图中尚有顶点未被访问，
// 则另选图中一个未曾被访问的顶点作起始点，
// 重复上述过程，直至图中所有顶点都被访问到为止。
// 换句话说，广度优先搜索遍历图的过程中以 v 为起始点，
// 由近至远，依次访问和 v 有路径相通且路径长度为 1,2, … 的顶点。

// 从 v 出发，按广度优先搜索遍历图 G ，使用辅助队列 Q 和访问标志数组 visited
void ALGraph::BFS(int v)
{
    EdgeNode *p;
    int u, w;
    SeqQueue Q; // SeqQueue 是 Queue.cpp 中的顺序队列类
    for (int v = 0; v < vertexNum; v++)
    {
        visited[v] = false;      // 标志向量初始化为 false
        Visit(v);                // 访问顶点 v
        visited[v] = true;       // 访问后标志向量变为法 true
        Q.En_Queue(v);           // v 入队
        while (!Q.Empty_Queue()) // 队列非空
        {
            Q.De_Queue(u); // 出队元素保存到 u
            for (p = adjList[u].firstEdge; p; p = p->next)
            {
                w = p->adjVertex;
                if (!visited[w])
                {
                    Visit(w);
                    visited[w] = true;
                    Q.En_Queue(w); // u 的尚未访问的邻接顶点 w 入队列 Q
                }
            }
        }
    }
}

// 深度优先搜索遍历以邻接矩阵为存储结构的图 G
void MatrixGraph::BFStraverse()
{
    int v;
    for (v = 0; v < vertexNum; v++)
        visited[v] = false; // 初始化标志向量数组
    for (v = 0; v < vertexNum; v++)
    {
        if (!visited[v])
            BFS(v);
    }
}

// 从顶点 v 开始深度优先搜索遍历以邻接矩阵为存储结构的图 G
void MatrixGraph::BFS(int v)
{
    int i, j;
    SeqQueue Q;
    for (v = 0; i < vertexNum; i++)
        visited[v] = false;
    Visit(v);
    visited[v] = true;
    Q.En_Queue(v);
    while (!Q.Empty_Queue())
    {
        Q.De_Queue(i);
        for (j = 0; j < vertexNum; j++) // 依次搜索 i 的邻接点 j
        {
            if (arcs[i][j] == 1 && !visited[j]) // 若 j 未访问
            {
                Visit(j);
                visited[j] = true;
                Q.En_Queue(j); // j 入队
            }
        }
    }
}

// （5）最小生成树

// 连通图可以转换为生成树，非联通图可以转换为生成森林
// 无向连通图的生成树不是唯一的，
// 如果无向连通图是一个网，那么它的所有生成树中必有一棵边的权值总和最小的生成树
// 这棵树就叫最小代价生成树，简称最小生成树

// （5.1）构造最小生成树的 prim 算法

// 假设 G=（V, E）为一网图，其中 V 为网图中所有顶点的集合，E为网图中所有带权边的集合。
// 设置两个新的集合 U 和 T，其中集合 U 用于存放 G 的最小生成树中的顶点，
// 集合 T 存放 G 的最小生成树中的边。
// 令集合 U 的初值为 U={u0}（假设构造最小生成树时，从顶点 u0 出发）​，集合T的初值为 T={}。
// 普里姆（Prim）算法的思想是，从所有 u∈U,v∈V-U 的顶点中，选取具有最小权值的边（u,v）​，
// 将顶点 v 加入集合 U 中，将边（u, v）加入集合 T 中，如此不断重复，
// 直到 U=V 时，最小生成树构造完毕。这时集合 T 包含最小生成树的所有边。

#define INFINITY 30000  // 定义一个权值的最大值
#define MaxVertexNum 30 // 最大顶点数为 30

typedef struct
{
    int adjvertex; // 某顶点与已构造好的部分生成树的顶点之间权值最小的顶点
    int lowcost;   // 某顶点与已构造好的部分生成树的顶点之间的最小权值
} ClosEdge;        // 定义普里姆算法求最小生成树时的辅助数组元素类型

class MGragh // MGragh是以邻接矩阵存储的图类
{
public:
    MGragh() {}         // 缺省构造函数
    void CreatGraph();  // 建立图的存储矩阵成员函数
    void BFStraverse(); // 广度遍历图
    void BFS(int v);    // 从顶点 v 开始广度遍历图
    void MiniSpanTree_PRIM(int u);

private:
    VertexType vertexs[MaxVertexNum];          // 顶点表
    EdgeType arcs[MaxVertexNum][MaxVertexNum]; // 邻接矩阵，即边表
    int vertexNum, edgeNum;                    // 顶点数和边数
    ClosEdge close_edge[MaxVertexNum];         // 存放最小生成树数组
    int visited[MaxVertexNum];                 // 访问标志数组
};

void MGragh ::MiniSpanTree_PRIM(int u)
{ // 从第 u 个顶点出发构造图 G 的最小生成树，最小生成树顶点信息存放在数组 close_edge 中
    int i, j, w, k;
    for (i = 0; i < vertexNum; i++) // 辅助数组初始化
    {
        if (i != u)
        {
            close_edge[i].adjvertex = u;
            close_edge[i].lowcost = arcs[u][i];
        }
    }
    close_edge[u].lowcost = 0;          // 初始，U={u}
    for (i = 0; i < vertexNum - 1; i++) // 选择其余的 G.vertexNum-1 个顶点
    {
        w = INFINITY;
        for (j = 0; j < vertexNum; j++) // 在辅助数组 close_edge 中选择权值最小的顶点
        {
            if (close_edge[j].lowcost != 0 && close_edge[j].lowcost < w)
            {
                w = close_edge[j].lowcost;
                k = j;
            } // 求出生成树的下一个顶点 k}
            close_edge[k].lowcost = 0;      // 第 k 个顶点并入 U 集
            for (j = 0; j < vertexNum; j++) // 新顶点并入 U 后，修改辅助数组
            {
                if (arcs[k][j] < close_edge[j].lowcost)
                {
                    close_edge[j].adjvertex = k;
                    close_edge[j].lowcost = arcs[k][j];
                }
            }
        }
        for (i = 0; i < vertexNum; i++) // 打印最小生成树的各条边
        {
            if (i != u)
                cout << i << " -> " << close_edge[i].adjvertex << ", " << arcs[i][close_edge[i].adjvertex] << endl;
        }
    }
}

// （5.2）构造最小生成树的 Kruskal 算法

// Kruskal 算法是一种按照网中边的权值递增的顺序构造最小生成树的方法。
// 其基本思想是：设无向连通网为 G=(V, E)，令 G 的最小生成树为 T，
// 其初态为 T=(V, {})，即开始时，最小生成树 T 由图 G 中的 n 个顶点构成，
// 顶点之间没有一条边，这样 T 中各顶点各自构成一个连通分量。
// 然后，按照边的权值由小到大的顺序，考察 G 的边集 E 中的各条边。
// 若被考察的边的两个顶点属于 T 的两个不同的连通分量，
// 则将此边作为最小生成树的边加入 T 中，同时把两个连通分量连接为一个连通分量；
// 若被考察的边的两个顶点属于同一个连通分量，则舍去此边，以免造成回路。
// 如此下去，当 T 中的连通分量个数为 1 时，此连通分量便为 G 的一棵最小生成树。
// 在构造过程中，按照网中边的权值由小到大的顺序，不断选取当前未被选取的边集中权值最小的边。
// 最后形成的连通分量便为 G 的一棵最小生成树。

#define MaxEdge 100
typedef int WeightType;
typedef struct ENode
{
    int vertex1, vertex2;
    WeightType weight;
} ENode;

class ELGraph
{ // 注意：此图的存储结构与前面介绍的几种不一样
public:
    void CreatGraph(); // 建立图的成员函数，具体实现略
    void Kruskal(ENode TE[]);
    void Sort(ENode[]);

private:
    int vertexNum, edgeNum;           // 顶点数，边数
    VertexType vertexs[MaxVertexNum]; // 顶点信息
    ENode edges[MaxVertexNum];        // 边的信息
};
void ELGraph ::Kruskal(ENode TE[]) // 用 Kruskal 算法构成图 G 的最小生成树，
                                   // 最小生成树存放在 TE[ ] 中
{
    int i, j, k;
    int f[MaxVertexNum];
    for (i = 0; i < vertexNum; i++)
        f[i] = i; // 初始化 f 数组
    Sort(edges);  // 对图 G 的边表按权值从小到大排序
    j = 0;
    k = 0;
    while (k < vertexNum - 1) // 选 n-1 条边
    {
        int s1 = f[edges[j].vertex1];
        int s2 = f[edges[j].vertex2];
        if (s1 != s2) // 产生一条最小边
        {
            TE[k].vertex1 = edges[j].vertex1;
            TE[k].vertex2 = edges[j].vertex2;
            TE[k].weight = edges[j].weight;
            k++;
            for (i = 0; i < vertexNum; i++)
                if (f[i] == s2)
                    f[i] = s1; // 修改连通的编号
            j++;
        }
    }
}