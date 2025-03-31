#include"head.h"

// 1、反转字符串
// 将输入的字符串反转过来。输入字符串以字符数组 char[] 的形式给出。
// 不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。
// 你可以假设数组中的所有字符都是 ASCII 码表中的可打印字符。
// 示例 ：
// 输入：["h", "e", "l", "l", "o"]
// 输出：["o", "l", "l", "e", "h"]

// 解题思路：双指针。左、右指针依次交换，然后向中间移动。
void reverseString(vector<char>& str) // 注意，需要传引用
{
	int left = 0;
	int right = str.size() - 1;
	while (left < right) // 循环条件是左小于右即可，字符个数是奇数或偶数都能满足。
	{
		// 交换内容可以使用库函数 swap，其实现也和下面一样。
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left;
		--right;
	}
}

// 2、反转字符串 II
// 给定一个字符串 s 和一个整数 k，从字符串开头算起, 每计数至 2k 个字符，
// 就反转这 2k 个字符中的前 k 个字符。如果剩余字符少于 k 个，则将剩余字符全部反转。
// 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
// 示例 :
// 输入: s = "abcdefg", k = 2
// 输出 : "bacdfeg"

// 解题思路：
// 遍历时，只要让 i += (2 * k)，i 每次移动 2 * k 就可以了，然后判断是否需要有反转的区间。
// 因为要找的也就是每 2 * k 区间的起点，这样写，程序会高效很多。

// 先定义一个字符串反转函数
void reverseStr(string& str, int start, int end)
{
	int left = start;
	int right = end;
	while (left < right)
	{
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left;
		--right;
	}
}

// 实现题目
void reverseStringII(string& str, int k)
{
	for (int i = 0; i < str.size(); i += (2 * k))
	{
		// 1. 每隔 2k 个字符的前 k 个字符进行反转
		// 2. 剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符
		if (i + k <= str.size())
		{
			reverseStr(str, i, i + k - 1);
			continue; // 退出本次循环，开始下一次循环，直到 i+k > str.size()
		}

		// 3. 剩余字符少于 k 个，则将剩余字符全部反转。
		reverseStr(str, i, str.size() - 1);
	}
}

// 3、逐个翻转字符串中的每个单词，(*****)
// 字符串前面或者后面包含多余的空格，但是反转后的字符不能包括。
// 如果两个单词间有多余的空格，将反转后单词间的空格减少到只含一个。
// 即翻转后首尾没有空格，单词之间只能有一个空格

// 不要使用辅助空间，空间复杂度要求为O(1)。

// 解题思路 1：
// 移除多余空格 ——> 反转字符串 ——> 将每个单词反转

// 删除多余的空格，这里使用的是 erase 函数，传入的参数是迭代器
// 但是这里时间复杂度较高，erase 为 O(n)，再套上 for 循环就是 O(n^2)
void removeExtraSpaces(string& str)
{
	for (int i = 0; i < str.size()-1; ++i)
	{
		// 首先删除多余的空格，在有空格的位置只保留一个空格。
		// 从前向后删，或从后向前删都行
		if (str[i] == str[i + 1] && str[i] == ' ')
			str.erase(str.begin()+i);
	}

	// 删除字符串前面的空格，注意要先判断字符串的长度是否大于 0
	if (str.size()>0 && str[0] == ' ')
		str.erase(str.begin());

	// 删除字符串后面的空格，也要判断长度是否大于 0
	if (str.size() > 0 && str[str.size() - 1] == ' ')
		str.erase(str.begin()+str.size() - 1);
}

// 使用双指针移除空格，最后再 resize 字符串的大小，时间复杂度为 O(n)
// 就类似使用双指针移除数组中的元素，不使用额外空间。
void removeExtraSpace1(string& str)
{
	int slow = 0;
	int fast = 0;

	// 去掉字符串前面的空格。也就是移动快指针到第一个非空字符的位置
	while (str.size()>0 && fast<str.size() && str[fast] == ' ')
		++fast;

	// 去掉字符串中间的多余空格，只保留一个空格
	for (; fast < str.size(); ++fast)
	{
		// 注意成立的条件
		if (fast - 1 > 0 && str[fast] == str[fast - 1] && str[fast] == ' ')
			continue;
		else
			str[slow++] = str[fast]; // slow++ ，不是 ++slow ，因为要先使用 slow 的值，再加一
	}

	// 去掉字符串末尾的空格
	if (slow - 1 > 0 && str[slow - 1] == ' ')
		str.resize(slow - 1); // 重新设置字符串的大小
	else
		str.resize(slow); // 重新设置字符串大小
}

// 上面是双指针也可以更加精简
void removeExtraSpaces2(string& str)
{
	int slow = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
		{
			if (slow != 0)str[slow++] = ' ';
			while (i < str.size() && str[i] != ' ')
				str[slow++] = str[i++];
		}
	}
	str.resize(slow);
}


// 4、