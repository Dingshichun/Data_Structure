// 哈希表的查找

// 哈希表与哈希表查找方法又名杂凑法或散列法，因其英文单词 Hash 而得名。

// 哈希法的基本思想是：
// 根据结点的键值确定结点的存储位置，
// 即以待查的结点关键字 K 为自变量，通过一个确定的函数 H，
// 计算出对应的函数值 H(K) ，并以这个函数值作为该结点的存储地址，
// 将结点存入 H(K) 所指的存储位置上。查找时再以要查找的关键字 K 为自变量，
// 用同样的函数计算地址，然后到相应的单元里取要查找的结点。
#include <iostream>
using namespace std;
typedef int DataType;
class HashTable
{
public:
    DataType *HT; // 哈希表
    int maxsize;  // 哈希表的大小
    int current;  // 哈希表中现有元素个数
public:
    HashTable(int n)
    { // 构造函数
        maxsize = n;
        HT = new DataType[maxsize];
        current = 0;
    }
    ~HashTable() { delete[] HT; }      // 析构函数
    int H(DataType k);                 // 哈希函数
    int HashSearch(DataType k);        // 哈希表的查找
    void HashInsert(DataType k);       // 哈希表的插入
    void HashDelete(DataType k);       // 哈希表的删除
    int HashSize() { return current; } // 哈希表中现有元素个数
    void Clear();                      // 清空
};

int HashTable::HashSearch(DataType k)
// 查找成功，返回所在的下标，不成功则返回-1
{
    int d, i;
    d = H(k); // 计算哈希地址，哈希函数为H(key)
    for (i = 0; i < maxsize; i++)
    {
        if (HT[d] == k)
            return (d); // 检索成功，返回哈希地址
        if (HT[d] == NULL)
            return (-1);       // 检索失败
        d = (d + i) % maxsize; // 用解决冲突的方法求下一个哈希地址
    }
    return (-1);
}

void HashTable::HashInsert(DataType k) // 将关键字k插入哈希表中
{
    int d, j;
    d = H(k); // 计算k的插入位置
    if (HT[d] != NULL)
    {
        j = d;
        d = (d + 1) % maxsize;
        while ((d != j) && HT[d] != NULL)
            d = (d + 1) % maxsize;
    }
    if (HT[d] == NULL)
    {
        HT[d] = k; // 将关键字插入哈希表中
        current++;
    }
    else
        cout << "哈希表已满！" << endl; // 表已满
}