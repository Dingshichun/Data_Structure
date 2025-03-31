#include"head.h"

// 排序算法总结
// 选择、冒泡、插入、归并、快速、堆、计数、桶、基数、希尔排序

// 1、选择排序
// 每次从未排序的部分选择一个最小（或最大）的元素，将其放到已排序部分的末尾。
// 通过重复这个过程，最终使整个数组变得有序。

void selectionSort(int arr[], int n)
{
    // int n = sizeof(arr) / sizeof(arr[0]);
    // 这种获取数组长度的方式是错误的，因为 arr 是一个指针，
    // 保存的是数组第一个元素的地址，而不是整个数组 
    // 解决办法是在函数参数中传入数组的大小

    // 遍历数组，每次从未排序的部分选择一个最小元素，只需要遍历到倒数第二个
    for (int i = 0; i < n-1 ; ++i) 
    {
        int minIndex = i; // 假设当前元素是最小的
        for (int j = i + 1; j < n; ++j) // 遍历未排序的部分，找到最小的元素
        {
            if (arr[j] < arr[minIndex]) // 如果找到更小的元素，更新最小元素的索引
                minIndex = j;
        }
        swap(arr[i], arr[minIndex]); // 将最小元素放到已排序部分的末尾
    }
}

void selectionSort2(vector<int>& arr)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
    {
        int minIndex = i;
        for (int j = i + 1;j < n;++j)
        {
            if (arr[j] < arr[minIndex])
                minIndex = j;
        }
        int temp = arr[i];
        arr[i] = arr[minIndex];
        arr[minIndex] = temp;
    }
}

// 2、冒泡排序
// 每次遍历数组，比较相邻的两个元素，如果它们的顺序错误，则交换它们。
// 通过重复这个过程，最终使整个数组变得有序。
void bubbleSort(vector<int>& arr)
{
    int n = arr.size(); // 获取数组长度
    bool swapped; // 定义一个标志位，用于判断是否发生了交换
    for (int i = 0; i < n - 1; ++i) // 外层循环， n-1 次遍历
    {
        swapped = false; // 每次外层遍历开始时，将标志位设置为 false
        // 内层循环，每次遍历后，最大的元素会被放到数组的末尾，所以可以减少比较的次数
        for (int j = 0; j < n - 1 - i; ++j) 
        {
            if (arr[j] > arr[j + 1])  // 如果当前元素大于下一个元素，则交换它们
            {
                swap(arr[j], arr[j + 1]);
                swapped = true; // 内层遍历发生了交换，将标志位设置为 true
            }
        }
        if (swapped == false)break; // 如果没有发生交换，说明已经有序，可以提前结束排序
    }
}

// 3、快速排序。没太懂怎么实现
class solu3
{
private:
    // 划分。选择一个基准值（pivot），将数组分为两部分，一部分包含小于等于基准值的元素，另一部分包含大于基准值的元素。
    int partition(vector<int>& arr, int low, int high) 
    {
        int pivot = arr[high];  // 选择最后一个元素作为基准值
        int i = low - 1;        // i 指向小于等于基准值的区域的末尾
        for (int j = low; j < high; ++j) 
        {
            if (arr[j] <= pivot) 
            {
                ++i;
                swap(arr[i], arr[j]);  // 将小于等于基准值的元素交换到左边
            }
        }
        swap(arr[i + 1], arr[high]);  // 将基准值放到中间
        return i + 1;  // 返回基准值的最终位置
    }
public:
    // 快速排序
    void quickSort(vector<int>& arr, int low, int high) 
    {
        if (low < high) 
        {
            int pivotIndex = partition(arr, low, high);  // 划分数组
            quickSort(arr, low, pivotIndex - 1);         // 递归排序左边子数组
            quickSort(arr, pivotIndex + 1, high);        // 递归排序右边子数组
        }
    }
};

// 4、插入排序
//插入排序的工作原理类似于整理扑克牌。
//假设你手中有一张牌，然后从桌子上依次拿牌并插入到手中合适的位置，使得手中的牌始终保持有序。插入排序的过程如下：
//从第一个元素开始，该元素可以认为已经被排序。
//取出下一个元素，在已经排序的元素序列中从后向前扫描。
//如果该元素（已排序）大于新元素，将该元素移到下一位置。
//重复步骤3，直到找到已排序的元素小于或等于新元素的位置。
//将新元素插入到该位置后。
//重复步骤2 - 5，直到所有元素都被插入到已排序的序列中。
void insertionSort(vector<int>& arr) 
{
    int n = arr.size();
    for (int i = 1; i < n; ++i) 
    {  // 外层循环：从第二个元素开始
        int key = arr[i];  // 当前要插入的元素
        int j = i - 1;     // 已排序序列的最后一个元素的索引

        // 内层循环：在已排序序列中从后向前扫描
        while (j >= 0 && arr[j] > key) 
        {
            arr[j + 1] = arr[j];  // 将大于key的元素向后移动
            --j;
        }
        // 插入 key 到合适位置
        arr[j + 1] = key;
    }
}

// 5、归并排序
// 归并排序是一种分治算法，它将数组分成两半，分别对它们进行排序，然后将它们合并在一起。

// 分解：将数组分成两部分，直到每个子数组只有一个元素（一个元素的数组是有序的）。
// 解决：递归地对每个子数组进行排序。
// 合并：将排序好的子数组合并成一个有序数组。
// 归并排序的关键在于合并操作，即将两个有序数组合并成一个有序数组。

// 将两个有序数组合并成一个有序数组的过程如下：
// 使用两个指针分别指向两个有序数组的起始位置。
// 比较指针所指向的元素，将较小的元素放入结果数组，并移动对应指针。
// 重复上述步骤，直到一个数组的所有元素都被放入结果数组。
// 将另一个数组中剩余的元素直接复制到结果数组中。
class solu5
{
private:
    // 合并两个有序数组
    void merge(vector<int>& arr, int left, int mid, int right) 
    {
        int n1 = mid - left + 1;  // 左半部分的大小
        int n2 = right - mid;     // 右半部分的大小

        // 创建临时数组存储左右两部分
        vector<int> L(n1), R(n2);

        // 复制数据到临时数组
        for (int i = 0; i < n1; ++i) 
        {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; ++j) 
        {
            R[j] = arr[mid + 1 + j];
        }

        // 合并两个有序数组
        int i = 0, j = 0, k = left;
        while (i < n1 && j < n2) 
        {
            if (L[i] <= R[j]) 
            {
                arr[k] = L[i];
                ++i;
            }
            else 
            {
                arr[k] = R[j];
                ++j;
            }
            ++k;
        }

        // 复制剩余的元素
        while (i < n1) 
        {
            arr[k] = L[i];
            ++i;
            ++k;
        }
        while (j < n2) 
        {
            arr[k] = R[j];
            ++j;
            ++k;
        }
    }
public:
    // 归并排序
    void mergeSort(vector<int>& arr, int left, int right) 
    {
        if (left < right) 
        {
            int mid = left + (right - left) / 2;  // 分解数组

            // 递归排序左右两部分
            mergeSort(arr, left, mid);
            mergeSort(arr, mid + 1, right);

            // 合并排序好的两部分
            merge(arr, left, mid, right);
        }
    }
};

// 6、堆排序
// 堆排序是一种基于堆数据结构的排序算法。
// 堆是一种完全二叉树，其中每个节点的值都大于或等于（或小于或等于）其子节点的值。
// 堆排序的基本思想是先将数组构建成一个最大堆（或最小堆），
// 然后将堆顶元素与最后一个元素交换，然后对剩余的元素重新构建堆，
// 重复这个过程直到堆中只剩下一个元素。
// 堆排序的时间复杂度为O(nlogn)，空间复杂度为O(1)。