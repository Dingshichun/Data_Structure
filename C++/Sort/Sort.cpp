// 排序

// 排序分为内排序和外排序。

// 内排序是指排序的整个过程中，数据全部存放在内存储器中，
// 并且在内存储器中调整记录间的相对位置，适合记录个数不太多的元素序列。
// 外排序是指在排序过程中，数据的主要部分存放在外存储器中，
// 借助内存储器逐步调整记录之间的相对位置，
// 适用于记录个数较多、无法一次将其全部记录都放入内存的元素序列。

// 内排序方法有5种：插入排序、交换排序、选择排序、归并排序和分配排序。

// （1）插入排序

// （1.1）直接插入排序

typedef int KeyType;
typedef struct
{
    KeyType key; // 关键码
} Node;

// 方法 1
void Dinsert_sort1(Node r[], int n)
{
    int i, j, k;
    for (i = 2; i <= n; i++)
    {
        r[0] = r[i]; // 设置监视哨
        for (j = i - 1; r[0].key < r[j].key; j--)
            ; // 寻找R[i]的插入位置
        for (k = i - 1; k > j; k--)
            r[k + 1] = r[k]; // 元素后移
        r[j + 1] = r[0];     // 元素插入正确位置
    }
}

// 合并方法 1 中的两个循环
void Dinsert_sort2(Node r[], int n)
{
    int i, j;
    for (i = 2; i <= n; i++)
    {
        r[0] = r[i];                              // 设置监视哨
        for (j = i - 1; r[0].key < r[j].key; j--) // 边寻找插入位置边移动元素
            r[j + 1] = r[j];
        r[j + 1] = r[0]; // 元素插入正确位置
    }
}

// （1.2）二分插入排序。

// 对有序表的插入排序，只适合顺序存储的排序表，不适合链式存储排序表

void Bi_insertsort(Node r[], int n)
{
    int i, j, low, high, mid;
    for (i = 2; i <= n; i++)
    {
        r[0] = r[i];
        low = 1;
        high = i - 1;       // 比较范围初始化
        while (low <= high) // 确定插入位置
        {
            mid = (low + high) / 2;
            if (r[0].key < r[mid].key)
                high = mid - 1;
            else
                low = mid + 1;
        } // 循环结束，low为插入位置
        for (j = i - 1; j >= low; j--)
            r[j + 1] = r[j]; // 元素后移
        r[low] = r[0];       // 第i个元素进行插入
    }
}

// （2）交换排序

// （2.1）冒泡排序

// （1）将整个排序表r划分成两部分：​（已按关键码值从小到大排序的有序区）​[无序区]​。
//      初始状态下，所有记录都处在无序区。初始状态：( )[r[1] r[2]…r[n]​]​。
// （2）从无序区右边开始，依次对相邻记录的关键码进行两两比较，不满足顺序要求的进行交换。
// （3）将无序区的第一个记录移入有序区的尾部。
// （4）重复步骤（2）和步骤（3）​，直至全部记录有序，为最终状态。

void Bubble_sort(Node r[], int n)
{
    int i, j, flag;
    for (i = 1; i < n; i++)
    {
        flag = 0; // 是否发生交换的标志
        for (j = n; j >= i + 1; j--)
            if (r[j].key < r[j - 1].key)
            {
                r[0] = r[j];
                r[j] = r[j - 1];
                r[j - 1] = r[0];
                flag = 1; // 发生了交换
            }
        if (!flag)
            break;
    }
}

// （2.2）快排

// 快速排序是冒泡排序的一种改进。
// 快速排序的基本思想是：以某个记录为标准（也称为支点）​，
// 其余记录都与支点记录进行比较，比支点记录大或相等的元素交换到支点记录之后，
// 小的交换到支点记录之前，通过一趟快速排序将待排序列分成两组。

// 一趟快速排序
int Partition(Node r[], int low, int high)
{
    if (low == high)
        return low;
    r[0] = r[low]; // 缓存支点记录
    while (low < high)
    {
        while (low < high && r[high].key >= r[0].key)
            high--;
        if (low < high)
        {
            r[low] = r[high];
            low++;
        }
        while (low < high && r[low].key <= r[0].key)
            low++;
        if (low < high)
        {
            r[high] = r[low];
            high--;
        }
    }
    r[low] = r[0]; // 支点记录最终位置
    return low;
}

// 快排，利用递归
void Qsort(Node r[], int s, int t)
{
    int i;
    if (s >= t)
        return;
    i = Partition(r, s, t);
    Qsort(r, s, i - 1);
    Qsort(r, i + 1, t);
}
void Quick_sort(Node r[], int n)
{
    Qsort(r, 1, n);
}

// （2.3）选择排序

void Select_sort(Node r[], int n)
{
    int i, j, k;
    for (i = 1; i < n; i++)
    {
        for (k = i, j = i + 1; j <= n; j++) // 选择最小的记录序号k
            if (r[j].key < r[k].key)
                k = j;
        if (i != k)
        {
            r[0] = r[k];
            r[k] = r[i];
            r[i] = r[0];
        }
    }
}

// （2.4）堆排序

// 堆排序的筛选算法
void Sift(Node r[], int s, int t)
{
    int i, j;
    r[0] = r[s]; // 堆顶元素暂存在r[0]
    i = s;
    j = 2 * i;
    while (j <= t) // 堆顶元素下筛
    {
        if (j + 1 <= t && r[j + 1].key > r[j].key)
            j++; // 确定下筛方向
        if (r[0].key < r[j].key)
        {
            r[i] = r[j];
            i = j;
            j = 2 * i;
        } // r[j]往堆顶方向上移
        else
            break;
    }
    r[i] = r[0]; // 原堆顶元素的最后位置
}

// 堆排序算法
void Heat_sort(Node r[], int n)
{
    int i;
    for (i = n / 2; i >= 1; i--)
        Sift(r, i, n);       // 建立初始堆
    for (i = n; i >= 2; i--) // n-1次筛选
    {
        r[0] = r[i];
        r[i] = r[1];
        r[1] = r[0];
        Sift(r, 1, i - 1);
    }
}

// （3）归并排序，一般是二路归并

// 一次归并
void Mergeone(Node r1[], Node r2[], int s, int m, int t)
{
    int i, j, k;
    i = s;
    j = m + 1;
    k = s;
    while (i <= m && j <= t)
        if (r1[i].key <= r1[j].key)
        {
            r2[k] = r1[i];
            i++;
            k++;
        }
        else
        {
            r2[k] = r1[j];
            j++;
            k++;
        }
    while (i <= m)
        r2[k++] = r1[i++];
    while (j <= t)
        r2[k++] = r1[j++];
}

// 一趟归并排序算法
void Mergepass(Node r1[], Node r2[], int L, int n)
{ // r1中子表长为L，进行一趟归并到r2
    int i = 1;
    while (i + 2 * L - 1 <= n) // 两个子表长度都为L的合并
    {
        Mergeone(r1, r2, i, i + L - 1, i + 2 * L - 1);
        i = i + 2 * L;
    }
    if (i + L - 1 < n) // 剩下两个子表，其中一个表长为L，另一个不足L
        Mergeone(r1, r2, i, i + L - 1, n);
    else // 剩下一个子表长≤L
        for (; i <= n; i++)
            r2[i] = r1[i];
}

#define MAX 100
// 二路归并排序算法
void Merge_sort(Node r[], int n)
{
    Node r1[MAX];
    int len = 1;
    while (len < n)
    {
        Mergepass(r, r1, len, n);
        len = 2 * len;
        Mergepass(r1, r, len, n);
        len = 2 * len;
    }
}

// 二路归并排序的递归算法
void Msort(Node r1[], int s, int t)
{
    Node r2[MAX];
    int m;
    if (s == t)
        return;
    else
    {
        m = (s + t) / 2;
        Msort(r1, s, m);
        Msort(r1, m + 1, t);
        Mergeone(r1, r2, s, m, t);
        Mergeone(r2, r1, s, t, t);
    }
}
void Merge1_sort(Node r[], int n)
{
    Msort(r, 1, n);
}