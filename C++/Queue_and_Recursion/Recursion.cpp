// 递归。时间效率低，通常用来分析问题，然后以非递归方法解决问题

// （1）问题具有类同自身的子问题的性质，被定义项在定义中的应用具有更小的尺度。
// （2）被定义项在最小尺度上有直接解。

// 设计递归算法的方法是：
// （1）寻找方法，将问题化为原问题的子问题求解（例如n! =n*(n-1)! ）​。
// （2）设计递归出口，确定递归终止条件（例如求解n！时，当n=1时，n! =1）​。

// （1）简单递归计算阶乘
#include <iostream>
#include "Stack.cpp"
using namespace std;

int fact(int n)
{
    if (n == 0) // 递归终止条件
        return (1);
    else
        return (n * fact(n - 1)); // 分解为子问题
}

// （2）消除递归

// 理解递归机制是掌握递归程序技能的必要前提。消除递归要基于对问题的分析。

// 常用的消除递归方法有两类：
// 一类是简单递归问题的转换，可用循环结构的算法替代；
// 另一类是基于栈的方式，即将递归中隐含的栈机制转化为由用户直接控制的明显的栈，利用堆栈保存参数。
// 由于堆栈的后进先出特性吻合递归算法的执行过程，因而可以用非递归算法替代递归算法。

// （2.1）简单递归问题的转换

// 循环求 n 的阶乘的非递归算法
int recur_fact(int n)
{
    int result = 1;
    for (; n > 0; n--)
    {
        result *= n;
    }
    return result;
}

// （2.2）利用栈求 n 的阶乘的非递归算法

// 利用栈求 n 的阶乘
int stack_fact(int n)
{
    int result, temp; // result 保存计算结果， temp 保存出栈的数
    SeqStack S;       // Stack.cpp 中的顺序栈
    while (n > 0)     // 元素 n,(n-1),(n-2),……,2,1 依次入栈
    {
        S.Push_Stack(n);
        n--;
    }
    result = 1;
    while (!(S.IsEmpty())) // 栈非空的时候，出栈
    {
        S.Pop_Stack(temp);
        result *= temp; // 计算阶乘结果
    }
    return result;
}