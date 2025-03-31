#include"head.h"
#include"backTrack.cpp"
#include"greedy.cpp"
#include"dynamicProgramming.cpp"
#include"monotonicStack.cpp"

int main()
{
	//vector<int> nums1 = { 2,3,3,4,4,5 };
	//vector<int> nums2 = { 1,1,1,2,2,2,2 };
	//cout << removeElement(nums1, 3);
	//cout << removeDuplicates(nums1) << endl;
	//cout << duoshu(nums2) << endl;
	//string s = "dsc hello hihh  ";
	//cout << removeDuplicate1(nums2) << endl;

	//vector<int>prices = { 1,2,4,5 };
	//cout << maxProfit1(prices) << endl;
	//vector<string>strs = { "flow","flos","fly" };
	//cout << longestCommonPrefix(strs) << endl;

	//string str = "a1sd1s1a";
	//cout << isPalindrome1(str) << endl;

	//string sub = "dsc";
	//string large = "dasfc";
	//cout << isSubsequence(sub, large) << endl;

	/*vector<int>array = { -3,-2,-1,0,2,5,6 };
	vector<int>result = sortedSquare1(array);
	for (int val : result)
		cout << val << endl;*/

	/*vector<int>nums1 = { 1,2,2,1,3 };
	vector<int>nums2 = { 1,2,2,3 };
	vector<int> result = intersection(nums1, nums2);
	for (int val : result)
		cout << val << endl;*/

	/*vector<string>strs = { "flow","flos","fly" };
	vector<string>result = commonChars(strs);
	for (string ch : result)
		cout << ch << endl;*/

	/*vector<int>nums = { 2,3,4,5,6 };
	int target = 5;
	vector<int>tw = twoSum(nums, target);
	for (auto val : tw)
		cout << val << endl;*/

	/*vector<int>nums = { -1,1,1,-1,2,0,2,-4,9};
	auto result = fourSum(nums,0);
	if (!result.empty())
	{
		cout << result.size() << endl;
		for (auto val : result[2])
			cout << val << endl;
	}*/

	/*vector<char>str = { 'h','e','l','l','o' };
	reverseString(str);
	for (auto s : str)
		cout << s << endl;*/

	/*string str = "abcdefg";
	reverseStringII(str, 2);
	for (char c : str)
		cout << c ;*/
	/*string str = "ss  abcde  fg  cc";
	removeExtraSpaces(str);
	cout << str;*/

	/*vector<int>nums{ 2,2,3,3,3,4 };
	cout << removeTargetNum(nums, 3);*/

	/*string str1 = "abbaca";
	string result = removeNeiborDuplicates(str1);
	cout << result;*/

	/*vector<string>str = { "2","3","4","+","*"};
	cout << reverPolanExpression(str);*/
	/*solution2 ss;
	vector<vector<int>>res = ss.com(9, 3);
	cout << res.size() << endl;
	for (int val : res[0])
		cout << val << endl;*/

	/*string str = "23";
	solution3 ss;
	vector<string>res = ss.letterCombinations(str);
	cout << res.size();
	for (string s : res)
		cout << s << endl;*/

	/*vector<int>candidates = { 2,5,2,1,2 };
	solution5 ss5;
	vector<vector<int>>result = ss5.numCombination(candidates, 5);
	cout << result.size() << endl;
	for (auto val : result[0])
		cout << val << endl;*/

	/*string str = "aab";
	solution6 ss6;
	vector<vector<string>>res = ss6.hui(str);
	cout << res.size() << endl;
	for (auto val : res[1])
		cout << val << endl;*/

	/*string str = "0000";
	solution7 ss7;
	vector<string>result = ss7.getIpAddress(str);
	for (auto val : result)
		cout << val << endl;*/

	/*solution11 ss11;
	vector<int>nums = { 4,6,7,};
	vector<vector<int>>result = ss11.queue(nums);
	cout << result.size() << endl;
	for (auto val : result[5])
		cout << val << endl;*/
	/*greedy3 gd3;
	vector<int>nums = { -1,-1,-1,-1 };
	cout << gd3.maxSubArray(nums) << endl;*/

	/*greedy4 gd4;
	vector<int>prices = { 7,1,5,3,6,4 };
	int result = gd4.maxProfit(prices);
	cout << result;*/
	
	/*greedy9 gd9;
	vector<int>nums = { 1,2,2 };
	cout << gd9.minSugar(nums);*/

	/*greedy10 gd10;
	vector<int>mon = { 5,5 };
	cout << gd10.finMoney(mon);*/

	//vector<int>cost = { 1, 100, 1, 1, 1, 100, 1, 1, 100, 1 };
	//dynamic3 dm3;
	//cout << dm3.minCost2(cost);

	/*dynamic4 dy4;
	cout << dy4.allPaths1(3,7);*/

	monotonicStack1 mnStk; 
	vector<int>tem = { 73, 74, 75, 71, 69, 72, 76, 73 };
	vector<int>result=mnStk.dailyTemprature1(tem);
	for (auto val : result)
		cout << val << " ";
	return 0;
}

void selectSort(vector<int>& nums)
{
	int n = nums.size();
	for (int i = 0; i < n - 1; ++i)
	{
		int minIndex = i;
		for (int j = i + 1; j < n; ++j)
		{
			if (nums[j] < nums[minIndex])minIndex = j;
		}
		swap(nums[i], minIndex);
	}
}
void bubbleSort(vector<int>& nums)
{
	int n = nums.size();
	bool swap_flag;
	for (int i = 0; i < n - 1; ++i)
	{
		swap_flag = false;
		for (int j = 0; j < n - 1 - i; ++j)
		{
			if (nums[j] > nums[j + 1])
			{
				swap(nums[j], nums[j + 1]);
				swap_flag = true;
			}
		}
		if (swap_flag == false)break;
	}
}
void insertSort(vector<int>& nums)
{
	int n = nums.size();
	for (int i = 1; i < n; ++i)
	{
		int key = nums[i];
		int j = i - 1;
		while (j >= 0 && nums[j] > key)
		{
			nums[j + 1] = nums[j];
			--j;
		}
		nums[j + 1] = key;
	}
}

class solu
{
private:
	int partition(vector<int>& nums, int left, int high)
	{
		int pivot = nums[high];
		int i = left - 1;
		for (int j = left; j < high; ++j)
		{
			if (nums[j] <= pivot)
			{
				++i;
				swap(nums[i], nums[j]);
			}
		}
		swap(nums[i + 1], nums[high]);
		return i + 1;
	}
public:
	void quickSort(vector<int>& nums, int left, int right)
	{
		if (left < right)
		{
			int pivotIndex = partition(nums, left, right);
			quickSort(nums, left, pivotIndex - 1);
			quickSort(nums, pivotIndex + 1, right);
		}
	}
};

class solu22
{
private:
	vector<int>merge(vector<int>& nums, int left, int mid, int right)
	{
		int n1 = mid - left + 1;
		int n2 = right - mid;
		vector<int>L(n1), R(n2);
		for (int i = 0; i < n1; ++i)
		{
			L[i] = nums[left + 1];
		}
		for (int j = 0; j < n2; ++j)
		{
			R[j] = nums[mid + 1 + j];
		}
		int i = 0, j = 0, k = left;
		while (i < n1 && j < n2)
		{
			if (L[i] <= R[j])
			{
				nums[k] = L[i];
				++i;
			}
			else
			{
				nums[k] = R[j];
				++j;
			}
			++k;
		}
		while (i < n1)
		{
			nums[k] = L[i];
			++i;
			++k;
		}
		while (j < n2)
		{
			nums[k] = R[j];
			++j;
			++k;
		}
	}
public:
	void mergeSort(vector<int>& nums, int left, int right)
	{
		if (left < right)
		{
			int mid = left + (right - left) / 2;
			mergeSort(nums, left, mid - 1);
			mergeSort(nums, mid + 1, right);
			merge(nums, left, mid, right);
		}
	}
};

class nms11
{
private:
	struct bbox
	{
		int x1, y1;
		int x2, y2;
		float confidence;
		int class_id;
	};
	float calculate_iou(const bbox& box1, const bbox& box2)
	{
		int x1 = max(box1.x1, box2.x1);
		int y1 = max(box1.y1, box2.y1);
		int x2 = min(box1.x2, box2.x2);
		int y2 = min(box1.y2, box2.y2);
		int iou_area = max(0, x2 - x1) * max(0,y2 - y1);
		if (iou_area == 0.0f)return 0.0f;
		int box1_area = (box1.x2 - box1.x1) * (box1.y2 - box1.y1);
		int box2_area = (box2.x2 - box2.x1) * (box2.y2 - box2.y1);
		int union_area = box1_area + box2_area - iou_area;
		float iou = iou_area / union_area;
		return iou;
	}
public:
	vector<bbox>nms(vector<bbox>& boxes, float iou_threshold)
	{
		vector<bbox>keep_boxes;
		vector<bool>suppressed(boxes.size(), false);
		sort(boxes.begin(), boxes.end(),
			[](const bbox& box1, const bbox& box2) {
				return box1.confidence > box2.confidence;
			});
		for (int i = 0; i < boxes.size(); ++i)
		{
			if (suppressed[i])continue;
			keep_boxes.push_back(boxes[i]);
			for (int j = i + 1; j < boxes.size(); ++j)
			{
				if (suppressed[j])continue;
				float iou = calculate_iou(boxes[i], boxes[j]);
				if (iou > iou_threshold)suppressed[j] = true;
			}
		}
		return keep_boxes;
	}
};

vector<vector<float>>conv2D(
	vector<vector<int>>& input,
	vector<vector<int>>& kernel,
	int stride = 1,
	int padding = 0)
{
	// 要先验证输入是否合法

	// 输入的尺寸
	int in_height = input.size();
	int in_width = input[0].size();

	// 卷积核的尺寸
	int k_height = kernel.size();
	int k_width = kernel[0].size();

	// 计算输出尺寸
	int out_height = (in_height + 2 * padding - k_height) / stride + 1;
	int out_width = (in_width + 2 * padding - k_width) / stride + 1;

	// 创建填充后的输入矩阵
	vector<vector<int>>padded_input(in_height+2*padding, 
		vector<int>(in_width+2*padding, 0));
	
	for (int i = 0; i < in_height; ++i)
	{
		for (int j = 0; j < in_width; ++j)
		{
			padded_input[i + padding][j + padding] = input[i][j];
		}
	}

	//创建输出矩阵
	vector<vector<float>>output(out_height,vector<float>(out_width, 0));
	for (int i = 0; i<out_height; ++i)
	{
		for (int j = 0; j < out_width; ++j)
		{
			float sum = 0.0;
			for (int m = 0; m < k_height; ++m)
			{
				for (int n = 0; n < k_width; ++n)
				{
					int x = i * stride + m;
					int y = j * stride + n;
					sum += padded_input[x][y] * kernel[m][n];
				}
			}
			output[i][j] = sum;
		}
	}
	return output;
}

vector<vector<float>>nearestNeighbor11(
	vector<vector<int>>input,
	int scale_x,
	int scale_y)
{
	if (input.size() == 0 || input[0].size() == 0)
		throw invalid_argument("input is false");
	if (scale_x < 0 || scale_y < 0)
		throw invalid_argument("scale must greater equal 0");

	const int in_height = input.size();
	const int in_width = input[0].size();
	const int out_height = ceil(in_height * scale_y);
	const int out_width = ceil(in_width * scale_x);

	vector<vector<float>>output(out_height, vector<float>(out_width, 0));

	for (int y = 0; y < out_height; ++y)
	{
		for (int x = 0; x < out_width; ++x)
		{
			int src_y = y / scale_y;
			int src_x = x / scale_x;

			int nearest_y = floor(src_y);
			int nearest_x = floor(src_x);
			output[y][x] = input[nearest_y][nearest_x];
		}
	}
	return output;
}

int fib(int n)
{
	if (n <= 1)return n;
	int dp[2];
	dp[0] = 0;
	dp[1] = 1;
	for (int i = 2; i <= n; ++i)
	{
		int temp = dp[0] + dp[1];
		dp[0] = dp[1];
		dp[1] = temp;
	}
	return dp[1];
}

int climStair1(int n)
{
	if (n <= 2)return n;
	vector<int>dp(n + 1);
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; ++i)
	{
		dp[i] = dp[i - 1] + dp[i - 2];
	}
	return dp[n];
}
int climStair2(int n)
{
	if (n <= 2)return n;
	int dp[3];
	dp[1] = 1;
	dp[2] = 2;
	for (int i = 3; i <= n; ++i)
	{
		int temp = dp[1] + dp[2];
		dp[1] = dp[2];
		dp[2] = temp;
	}
	return dp[2];
}

int minClimStairsCost1(vector<int>& costs)
{
	vector<int>dp(costs.size() + 1);
	dp[0] = 0;
	dp[1] = 0;
	for (int i = 2; i <= costs.size(); ++i)
	{
		dp[i] = min(dp[i - 1] + costs[i - 1], dp[i - 2] + costs[i - 2]);
	}
	return dp[costs.size()];
}
int minClimStairsCost2(vector<int>& costs)
{
	int dp[2];
	dp[0] = 0;
	dp[1] = 0;
	for (int i = 2; i <= costs.size(); ++i)
	{
		int temp = min(dp[1] + costs[i - 1], dp[0] + costs[i - 2]);
		dp[0] = dp[1];
		dp[1] = temp;
	}
	return dp[1];
}

int allPaths(int m, int n)
{
	vector<vector<int>>dp(m, vector<int>(n, 0));
	for (int i = 0; i < n; ++i)dp[0][i] = 1;
	for (int j = 0; j < m; ++j)dp[j][0] = 1;

	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}
int allPathsWithObstacle(vector<vector<int>>& obstacleGrid)
{
	int m = obstacleGrid.size();
	int n = obstacleGrid[0].size();
	if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1] == 1)
		return 0;

	vector<vector<int>>dp(m, vector<int>(n, 0));
	for (int i = 0; i < n && obstacleGrid[0][i] == 0; ++i)
		dp[0][i] = 1;
	for (int j = 0; j < m && obstacleGrid[j][0] == 0; ++j)
		dp[j][0] = 1;

	for (int i = 1; i < m; ++i)
	{
		for (int j = 1; j < n; ++j)
		{
			if (obstacleGrid[i][j] == 1)continue;
			dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
		}
	}
	return dp[m - 1][n - 1];
}

