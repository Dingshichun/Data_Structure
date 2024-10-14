#include <iostream>
#include "head.h"
using namespace std;

// 因为其它文件中有些函数可能只有声明，但是没有定义，所以可能会无法运行
// 注释掉 #include "head.h" 即可运行 main.cpp
int main()
{
    int arr[] = {3, 5, 7, 9, 99};
    int k = 3;
    int len = length(arr);                  // 数组长度
    cout << BinSearch(arr, len, k) << endl; // 普通二分查找
    int low = 0;
    int high = length(arr) - 1;
    cout << Recur_BinSearch(arr, low, high, k) << endl; // 递归二分查找
    return (0);
}