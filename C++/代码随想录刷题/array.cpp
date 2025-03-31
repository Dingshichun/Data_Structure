#include"head.h"

// 1、二分查找，只针对有序数组,且无重复元素，有重复元素返回的下标可能不唯一
// 总结：如果定义的查找区间不同{[left,right] 和 [left,right)}，那么 while 循环终止条件不同，中间位置 mid 的更新也不同
// 如果 target 定义在 [left,right] ，使用 while(left <= right) ，因为左右都是闭，可以取到 left = right
// 如果 target 定义在 [left,right) ，使用 while(left < right) ，因为左闭右开，不可以取到 left = right

// 解法 1：习惯使用该解法
// 假如 target 定义在左闭右闭的区间 [left, right] ，（这个很重要非常重要）。
// 区间的定义决定了代码的写法，因为定义 target 在 [left, right] 区间，所以有如下两点：
// while (left <= right) 要使用 <= ，因为 left == right 是有意义的，所以使用 <=
// if (nums[middle] > target) right 要赋值为 middle - 1，因为当前这个 nums[middle] 一定不是 target，那么接下来要查找的左区间结束下标位置就是 middle - 1
int binarySearch(vector<int>& array,int target)
{
	int left = 0, right = array.size() - 1; // 定义在 [left,right] ，注意查找下标的定义
	while (left <= right) // 注意循环终止条件
	{
		int mid = (left + right) / 2; // 取中间值一般都是如此
		if (array[mid] > target) // target 在区间左侧
			right = mid - 1;
		else if (array[mid] < target) // target 在区间右侧
			left = mid + 1;
		else
			return mid;
	}
	return -1; // 没有找到 target
}

// 解法 2：
// 假如 target 定义在左闭右开的区间 [left, right) 里 ，那么二分法的边界处理方式则截然不同。
// 有如下两点：
// while (left < right)，这里使用 < , 因为 left == right 在区间 [left, right) 是没有意义的
// if (nums[middle] > target)， right 更新为 middle，因为当前 nums[middle] 不等于target，
// 去左区间继续寻找，而寻找区间是左闭右开区间，所以 right 更新为 middle ，即：下一个查询区间不会去比较 nums[middle]

int binarySearch1(vector<int>& array, int target)
{
	int left = 0, right = array.size(); // 注意下标
	while (left < right) // 循环终止条件取不到 =
	{
		int mid = (left + right) / 2;
		if (array[mid] > target)
			right = mid; // 注意 target 在区间左侧时，即在 [left,mid) 中，所以取 right = mid
		else if (array[mid] < target)
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}

// 2、移除指定元素。
// 题目：给你一个数组 nums 和一个值 val，你需要 原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

// 解法 1：暴力循环求解，不推荐。

// 解法 2：双指针
vector<int>removeValue(vector<int>& array, int val)
{
	int slow = 0, fast = 0; // 定义快、慢指针初始位置
	int len = array.size(); 
	while (fast < len) // fast 只会比 slow 移动得快，所以会先到达末尾
	{
		if (array[fast] != val) // 快指针位置的值不等于 val
		{
			array[slow] = array[fast]; // 将快指针位置的值赋给慢指针
			++slow; // 快、慢指针都加 1 
			++fast;
		}
		else // 快指针位置的值等于 val
			++fast; // 则只移动快指针
	}
	// 执行完上面的操作之后，slow 的值就是删除指定 val 后 array 的长度。
	// array 的 0~slow 保存的就是删除 val 后的数，将其取出即可
	vector<int>result(slow , 0); // 新容器存放 array 的 0~slow 位置的元素
	for (int i = 0; i < slow; ++i)
		result[i] = array[i];
	return result;
}

// 3、有序数组的平方,注意是有序数组。
// 解法 1： 平方后排序
vector<int>sortedSquare(vector<int>& array)
{
	for (int& arr : array) // 使用引用就可以直接改变原值
		arr *= arr;
	sort(array.begin(), array.end()); // 利用迭代器进行排序
	return array; // 由于使用引用更改，所以可以直接返回传入的 array
}

// 解法 2 ：双指针。主要就是注意负数，平方之后可能变为最大值。
// 数组平方的最大值不是在数组的最左边就是最右边，不可能是中间。
// 此时可以考虑双指针法了，i 指向起始位置，j 指向终止位置。
// 定义一个新数组 result，和 A 数组一样的大小， k 最开始指向 result 数组末尾。
// 如果 A[i] * A[i] < A[j] * A[j] 那么 result[k--] = A[j] * A[j]; 。
// 如果 A[i] * A[i] >= A[j] * A[j] 那么 result[k--] = A[i] * A[i]; 。
vector<int>sortedSquare1(vector<int>& array)
{
	vector<int> result(array.size(), 0); // 新建数组全部初始化为 0 
	int left = 0, right = array.size() - 1; // left、right 指针最开始指向 array 头、尾
	int k = array.size() - 1; // k 指向数组末尾
	for (left, right; left <= right;) // 注意循环终止条件是 <=
	{
		if (array[left] * array[left] > array[right] * array[right])
		{
			// 注意，是 k-- ，不是 --k ，因为要先使用 k 的值，再进行减 1 。
			result[k--] = array[left] * array[left];
			++left;
		}
		else
		{
			result[k--] = array[right] * array[right];
			--right;
		}
	}
	return result;
}

// 4、长度最短的子数组
// 题目：
// 给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，
// 并返回其长度。如果不存在符合条件的子数组，返回 0。

// 解法 1：暴力 for 循环，会超时，不推荐。
int minSubArrayLen(vector<int>& array, int s)
{
	// INT32_MAX 宏，是整型变量能够存储的最大整数，定义在 limits.h 头文件中
	int result = INT32_MAX; // 保存要返回的子序列长度
	int sum = 0; // sum 保存子序列的和
	int subLength = 0; // subLength 保存子序列的长度
	for (int i = 0; i < array.size(); ++i) // 外层循环
	{
		for (int j = i; j < array.size(); ++j) // 内存循环，即找子序列
		{
			sum += array[j]; // 子序列的和
			if(sum >= s) // 如果子序列的和满足条件
			{
				subLength = j - i + 1; // 求出子序列的长度
				result = (result < subLength) ? result : subLength; // 更新满足条件的子序列的长度
				break; // 如果找到一个符合条件的子序列，就退出内层循环
			}
		}
	}
	return result == INT32_MAX ? 0 : result; // 没有符合的子序列返回 0 ，否则返回最短子序列的长度
}

// 解法 2：滑动窗口
int minSubArrayLen1(vector<int>& array, int s)
{
	// INT32_MAX 宏，是整型变量能够存储的最大整数，定义在 limits.h 头文件中
	int result = INT32_MAX; // 保存要返回的子序列长度
	int sum = 0; // 保存子序列的和
	int subLength = 0; // 保存子序列的长度
	int i = 0; // 子序列的起始位置

	for (int j = 0; j < array.size(); ++j)
	{
		sum += array[j]; // 子序列的和
		while (sum >= s) // 当检测到有符合的子序列时
		{
			subLength = j - i + 1; // 求符合条件的子序列长度
			result = (result < subLength) ? result : subLength;
			sum -= array[i++]; // 动态地变更子序列的起始位置
		}
	}
	return result == INT32_MAX ? 0 : result; // 不存在符合条件的子序列就返回 0 ，否则返回最短子序列。
}

// 5、数组区间和
// 题目：
// 给定一个整数数组 Array，请计算该数组在每个指定区间内元素的总和。
// 比如数组 [1,2,3,4,5] ，计算下标 0~2 的和就是 1+2+3=6 ，下标 1~3 的和就是 2+3+4=9

// 解法 1：直接累加对应区间的和。不推荐，时间复杂度较大
int gapSum()
{
	int n, a, b; // n 是数组长度，区间是 a~b
	cout << "please input length of array :" << endl;
	cin >> n; // 输入数组的长度
	vector<int>vector(n);
	cout << "请输入数组的元素" << endl;
	for (int i = 0; i < n; ++i)
		cin >> vector[i];
	cout << "输入区间" << endl;
	cin >> a >> b;
	int sum = 0;
	for (int i = a; i <= b; ++i)
		sum += vector[i];
	return sum;
}

// 解法 2:前缀和。其思想是重复利用计算过的子数组之和，从而降低区间查询需要累加计算的次数。
// 前缀和具体解法：有数组 vec[i] ，p[i] 表示 vec[0]~vec[i] 的累加和
// 比如 p[1] = vec[0] + vec[1] , p[3] = vec[0] + vec[1] + vec[2] + vec[3]
// 那么要计算下标 2~3 的和，使用 p[3] - p[1] = vec[2] + vec[3]
// 需要注意的是这里是减 p[1] ,不是减 p[2] ，
// 即要求区间 a~b 的和，如果 a=0,直接返回 p[b],否则返回 p[b]-p[a-1]

int gapSum1()
{
	int n, a, b; // n 是数组长度，区间是 a~b
	cout << "please input length of array :" << endl;
	cin >> n; // 输入数组的长度
	vector<int>vec(n); // 存放数组元素
	vector<int>p(n); // 存放数组前缀和
	int pre_sum = 0; // 初始化前缀和
	cout << "请输入数组的元素" << endl;
	for (int i = 0; i < n; ++i)
	{
		cin >> vec[i]; // 输入数组元素
		pre_sum += vec[i]; // 计算前缀和
		p[i] = pre_sum; // 前缀和添加到容器中
	}
	cout << "输入区间" << endl;
	cin >> a >> b;
	int sum = 0; // 存放最后要返回的前缀和
	if (a == 0)sum = p[b]; // 如果下标从 0 开始
	else
		sum = p[b] - p[a - 1]; 
	return sum;
}

// 6、螺旋矩阵
// 解法 1：
class Solution {
private:
	static constexpr int directions[4][2] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };
public:
	vector<int> spiralOrder(vector<vector<int>>& matrix) {
		if (matrix.size() == 0 || matrix[0].size() == 0) {
			return {};
		}

		int rows = matrix.size(), columns = matrix[0].size();
		vector<vector<bool>> visited(rows, vector<bool>(columns));
		int total = rows * columns;
		vector<int> order(total);

		int row = 0, column = 0;
		int directionIndex = 0;
		for (int i = 0; i < total; i++) {
			order[i] = matrix[row][column];
			visited[row][column] = true;
			int nextRow = row + directions[directionIndex][0], nextColumn = column + directions[directionIndex][1];
			if (nextRow < 0 || nextRow >= rows || nextColumn < 0 || nextColumn >= columns || visited[nextRow][nextColumn]) {
				directionIndex = (directionIndex + 1) % 4;
			}
			row += directions[directionIndex][0];
			column += directions[directionIndex][1];
		}
		return order;
	}
};
		
// 解法 2：按层模拟
// 可以将矩阵看成若干层，首先输出最外层的元素，其次输出次外层的元素，直到输出最内层的元素。
vector<int> spiralOrder(vector<vector<int>>& matrix)
{
	if (matrix.size() == 0 || matrix[0].size() == 0)
		return {};

	int rows = matrix.size(), columns = matrix[0].size();
	vector<int> order;
	int left = 0, right = columns - 1, top = 0, bottom = rows - 1;
	while (left <= right && top <= bottom) {
		for (int column = left; column <= right; column++)
			order.push_back(matrix[top][column]);
		for (int row = top + 1; row <= bottom; row++)
			order.push_back(matrix[row][right]);
		if (left < right&& top < bottom)
		{
			for (int column = right - 1; column > left; column--)
				order.push_back(matrix[bottom][column]);
			for (int row = bottom; row > top; row--)
				order.push_back(matrix[row][left]);
		}
		left++;
		right--;
		top++;
		bottom--;
	}
	return order;
}

