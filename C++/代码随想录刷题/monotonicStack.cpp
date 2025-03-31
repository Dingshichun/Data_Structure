#include"head.h"

//单调栈。
// 通常是一维数组，要寻找任一个元素的右边或者左边第一个比自己大或者小的元素的位置，
// 此时我们就要想到可以用单调栈了。时间复杂度为O(n)。

//单调栈的本质是空间换时间，因为在遍历的过程中需要用一个栈来记录右边第一个比当前元素高的元素，
//优点是整个数组只需要遍历一次。

//在使用单调栈的时候首先要明确如下几点：
//1.单调栈里存放的元素是什么？
//单调栈里只需要存放元素的下标 i 就可以了，如果需要使用对应的元素，直接 T[i] 就可以获取。
//2.单调栈里元素是递增呢？ 还是递减呢？需要根据实际情况决定

// 1、每日温度
//请根据每日 气温 列表，重新生成一个列表。
//对应位置的输出为：要想观测到更高的气温，至少需要等待的天数。
//如果气温在这之后都不会升高，请在该位置用 0 来代替。
//例如，给定一个列表 temperatures = [73, 74, 75, 71, 69, 72, 76, 73]，
//你的输出应该是[1, 1, 4, 2, 1, 1, 0, 0]。
class monotonicStack1
{
public:
	vector<int>dailyTemprature(vector<int>& tem)
	{
		stack<int>stk; // 创建栈用来保存元素索引
		vector<int>result(tem.size(), 0); // 保存结果
		stk.push(0); // 第一个元素的索引 0 入栈
		for (int i = 1; i < tem.size(); ++i) // 从第二个元素开始遍历，仅遍历一次
		{
			if (tem[i] < tem[stk.top()])stk.push(i); // 情况一
			else if (tem[i] == tem[stk.top()])stk.push(i); // 情况二
			else // 情况三
			{
				// 当栈非空且当前遍历的元素大于栈顶元素时
				while (!stk.empty() && tem[i] > tem[stk.top()])
				{
					result[stk.top()] = i - stk.top(); // 将结果存入 result
					stk.pop(); // 栈顶元素出栈
				}
				stk.push(i); // 元素入栈
			}
		}
		return result;
	}
	// 拓展，要想观测到更低的气温，至少需要等待的天数。
	vector<int>dailyTemprature1(vector<int>& tem)
	{
		stack<int>stk; // 创建栈用来保存元素索引
		vector<int>result(tem.size(), 0); // 保存结果
		stk.push(0); // 第一个元素的索引 0 入栈
		for (int i = 1; i < tem.size(); ++i) // 从第二个元素开始遍历，仅遍历一次
		{
			if (tem[i] > tem[stk.top()])stk.push(i); // 情况一
			else if (tem[i] == tem[stk.top()])stk.push(i); // 情况二
			else // 情况三
			{
				// 当栈非空且当前遍历的元素小于栈顶元素时
				while (!stk.empty() && tem[i] < tem[stk.top()])
				{
					result[stk.top()] = i - stk.top(); // 将结果存入 result
					stk.pop(); // 栈顶元素出栈
				}
				stk.push(i); // 元素入栈
			}
		}
		return result;
	}
};