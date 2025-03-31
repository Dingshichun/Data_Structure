// 特殊矩阵的压缩存储

// 有许多值相同，或有许多 0 元素，且分布具有一定规律的矩阵称为特殊矩阵。
// 为了节省存储空间，可以对这类特殊矩阵进行压缩存储，
// 即多个相同的非零元素只分配一个存储空间；对零元素不分配空间。

// （1）对称矩阵（针对方阵）
// 对称矩阵的元素关于主对角线对称，
// 所以只需要存储上三角或下三角中的元素即可，让对称的元素共享存储空间

// （2）三角矩阵（方阵）
// n 阶上（下）三角矩阵是对应的下（上）三角的元素均为常数或 0 的 n 方阵

// （3）稀疏矩阵
//  0 元素的数量远远大于非 0 元素的数量

// 由于非零元素的分布一般是没有规律的，
// 因此在存储非零元素的同时，还必须记下元素所在的行和列的位置（i, j）​。
// 因此，稀疏矩阵 A 中的一个非零元素可由一个三元组（i, j, aij）唯一确定。

// 假设非零元素的三元组以按行优先的原则顺序排列，
// 一个稀疏矩阵就可转换成用一个对应的线性顺序表来表示，
// 其中每个元素由一个上述的三元组构成，该线性表称为三元组表，记为（i, j,v）​。

typedef int DataType;
#define maxsize 1000 // 注意，这里末尾不加 ";"，否则 maxsize 代表的就是 "1000;" ，

// 表示一个非零元素三元组的结构体
struct Triple
{
    int i, j;   // 非零元素的行、列号
    DataType v; // 非零元素的值
};

// 存储三元组的类
class SparseMatrix
{
public:
    int rows, cols, terms; // 稀疏矩阵的行、列数和非零元素的个数
    Triple data[maxsize];  // 创建三元组表

public:
    // SparseMatrix(int MaxRow, int MaxCol) // 构造函数
    // {
    // }
    SparseMatrix Transmatrix(); // 矩阵转置 1
    // SparseMatrix FastTranstri(); // 矩阵转置 2
};

// 矩阵转置 1
SparseMatrix SparseMatrix::Transmatrix()
{                    // 将稀疏矩阵 a(＊this指示) 转置，结果在稀疏矩阵 b 中
    SparseMatrix b;  // 创建一个稀疏矩阵类对象 b
    b.rows = cols;   // 矩阵 b 的行数 = 矩阵 a 的列数
    b.cols = rows;   // 矩阵 b 的列数 = 矩阵 a 的行数
    b.terms = terms; // 矩阵 b 的非零元素数 = 矩阵 a 的非零元素数
    if (b.terms > 0) // 非零元素个数不为零
    {
        int position = 0;                     // 存放位置指针
        for (int col = 1; col <= cols; col++) // 按列号作扫描，做 cols 趟
            for (int p = 0; p < terms; p++)   // 在数据中找列号为 col 的三元组
                if (this->data[p].j == col)   // 第 p 个三元组中元素的列号为 col
                {
                    b.data[position].i = col;             // 新三元组的行号
                    b.data[position].j = this->data[p].i; // 新三元组的列号
                    b.data[position].v = this->data[p].v; // 新三元组的值
                    position++;                           // 位置指针增 1
                }
    }
    return b;
}

// 传统矩阵转置算法
/*
for(col=1; col<=n; ++col)
for(row=1; row<=m; ++row)
        b[col][row]=a[row][col];
*/

/*
// 矩阵转置 2
SparseMatrix SparseMatrix::FastTranstri()
{ // 将稀疏矩阵 a(＊this指示) 做快速转置，结果在稀疏矩阵 b 中
    int p, q, col, k;
    int num[cols + 1], pot[cols + 1]; // 建立辅助数组
    SparseMatrix b;                   // 创建一个稀疏矩阵类对象b
    b.rows = cols;
    b.cols = rows;
    b.terms = terms;
    if (b.terms > 0)
    {
        for (col = 1; col <= cols; ++col) // 对数组num初始化
            num[col] = 0;
        for (k = 0; k < terms; ++k) // 计算a中每一列含非零元素的个数
            ++num[this->data[k].j];
        pot[1] = 0; // 计算矩阵a中第col列中第一个非零元素在b中的序号
        for (col = 2; col <= cols; ++col)
            pot[col] = pot[col - 1] + num[col - 1];
        for (p = 0; p <= terms; ++p) // 把a中每一个非零元素插入b中
        {
            col = this->data[p].j;
            q = pot[col];
            b.data[q].i = this->data[p].j;
            b.data[q].j = this->data[p].i;
            b.data[q].v = this->data[p].v;
            ++pot[col];
        }
    }
    return b;
}
*/