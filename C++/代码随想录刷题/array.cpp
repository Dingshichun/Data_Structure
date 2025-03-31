#include"head.h"

// 1�����ֲ��ң�ֻ�����������,�����ظ�Ԫ�أ����ظ�Ԫ�ط��ص��±���ܲ�Ψһ
// �ܽ᣺�������Ĳ������䲻ͬ{[left,right] �� [left,right)}����ô while ѭ����ֹ������ͬ���м�λ�� mid �ĸ���Ҳ��ͬ
// ��� target ������ [left,right] ��ʹ�� while(left <= right) ����Ϊ���Ҷ��Ǳգ�����ȡ�� left = right
// ��� target ������ [left,right) ��ʹ�� while(left < right) ����Ϊ����ҿ���������ȡ�� left = right

// �ⷨ 1��ϰ��ʹ�øýⷨ
// ���� target ����������ұյ����� [left, right] �����������Ҫ�ǳ���Ҫ����
// ����Ķ�������˴����д������Ϊ���� target �� [left, right] ���䣬�������������㣺
// while (left <= right) Ҫʹ�� <= ����Ϊ left == right ��������ģ�����ʹ�� <=
// if (nums[middle] > target) right Ҫ��ֵΪ middle - 1����Ϊ��ǰ��� nums[middle] һ������ target����ô������Ҫ���ҵ�����������±�λ�þ��� middle - 1
int binarySearch(vector<int>& array,int target)
{
	int left = 0, right = array.size() - 1; // ������ [left,right] ��ע������±�Ķ���
	while (left <= right) // ע��ѭ����ֹ����
	{
		int mid = (left + right) / 2; // ȡ�м�ֵһ�㶼�����
		if (array[mid] > target) // target ���������
			right = mid - 1;
		else if (array[mid] < target) // target �������Ҳ�
			left = mid + 1;
		else
			return mid;
	}
	return -1; // û���ҵ� target
}

// �ⷨ 2��
// ���� target ����������ҿ������� [left, right) �� ����ô���ַ��ı߽紦��ʽ���Ȼ��ͬ��
// ���������㣺
// while (left < right)������ʹ�� < , ��Ϊ left == right ������ [left, right) ��û�������
// if (nums[middle] > target)�� right ����Ϊ middle����Ϊ��ǰ nums[middle] ������target��
// ȥ���������Ѱ�ң���Ѱ������������ҿ����䣬���� right ����Ϊ middle ��������һ����ѯ���䲻��ȥ�Ƚ� nums[middle]

int binarySearch1(vector<int>& array, int target)
{
	int left = 0, right = array.size(); // ע���±�
	while (left < right) // ѭ����ֹ����ȡ���� =
	{
		int mid = (left + right) / 2;
		if (array[mid] > target)
			right = mid; // ע�� target ���������ʱ������ [left,mid) �У�����ȡ right = mid
		else if (array[mid] < target)
			left = mid + 1;
		else
			return mid;
	}
	return -1;
}

// 2���Ƴ�ָ��Ԫ�ء�
// ��Ŀ������һ������ nums ��һ��ֵ val������Ҫ ԭ�� �Ƴ�������ֵ���� val ��Ԫ�أ��������Ƴ���������³��ȡ�

// �ⷨ 1������ѭ����⣬���Ƽ���

// �ⷨ 2��˫ָ��
vector<int>removeValue(vector<int>& array, int val)
{
	int slow = 0, fast = 0; // ����졢��ָ���ʼλ��
	int len = array.size(); 
	while (fast < len) // fast ֻ��� slow �ƶ��ÿ죬���Ի��ȵ���ĩβ
	{
		if (array[fast] != val) // ��ָ��λ�õ�ֵ������ val
		{
			array[slow] = array[fast]; // ����ָ��λ�õ�ֵ������ָ��
			++slow; // �졢��ָ�붼�� 1 
			++fast;
		}
		else // ��ָ��λ�õ�ֵ���� val
			++fast; // ��ֻ�ƶ���ָ��
	}
	// ִ��������Ĳ���֮��slow ��ֵ����ɾ��ָ�� val �� array �ĳ��ȡ�
	// array �� 0~slow ����ľ���ɾ�� val �����������ȡ������
	vector<int>result(slow , 0); // ��������� array �� 0~slow λ�õ�Ԫ��
	for (int i = 0; i < slow; ++i)
		result[i] = array[i];
	return result;
}

// 3�����������ƽ��,ע�����������顣
// �ⷨ 1�� ƽ��������
vector<int>sortedSquare(vector<int>& array)
{
	for (int& arr : array) // ʹ�����þͿ���ֱ�Ӹı�ԭֵ
		arr *= arr;
	sort(array.begin(), array.end()); // ���õ�������������
	return array; // ����ʹ�����ø��ģ����Կ���ֱ�ӷ��ش���� array
}

// �ⷨ 2 ��˫ָ�롣��Ҫ����ע�⸺����ƽ��֮����ܱ�Ϊ���ֵ��
// ����ƽ�������ֵ���������������߾������ұߣ����������м䡣
// ��ʱ���Կ���˫ָ�뷨�ˣ�i ָ����ʼλ�ã�j ָ����ֹλ�á�
// ����һ�������� result���� A ����һ���Ĵ�С�� k �ʼָ�� result ����ĩβ��
// ��� A[i] * A[i] < A[j] * A[j] ��ô result[k--] = A[j] * A[j]; ��
// ��� A[i] * A[i] >= A[j] * A[j] ��ô result[k--] = A[i] * A[i]; ��
vector<int>sortedSquare1(vector<int>& array)
{
	vector<int> result(array.size(), 0); // �½�����ȫ����ʼ��Ϊ 0 
	int left = 0, right = array.size() - 1; // left��right ָ���ʼָ�� array ͷ��β
	int k = array.size() - 1; // k ָ������ĩβ
	for (left, right; left <= right;) // ע��ѭ����ֹ������ <=
	{
		if (array[left] * array[left] > array[right] * array[right])
		{
			// ע�⣬�� k-- ������ --k ����ΪҪ��ʹ�� k ��ֵ���ٽ��м� 1 ��
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

// 4��������̵�������
// ��Ŀ��
// ����һ������ n ���������������һ�������� s ���ҳ���������������� �� s �ĳ�����С�� ���� �����飬
// �������䳤�ȡ���������ڷ��������������飬���� 0��

// �ⷨ 1������ for ѭ�����ᳬʱ�����Ƽ���
int minSubArrayLen(vector<int>& array, int s)
{
	// INT32_MAX �꣬�����ͱ����ܹ��洢����������������� limits.h ͷ�ļ���
	int result = INT32_MAX; // ����Ҫ���ص������г���
	int sum = 0; // sum ���������еĺ�
	int subLength = 0; // subLength ���������еĳ���
	for (int i = 0; i < array.size(); ++i) // ���ѭ��
	{
		for (int j = i; j < array.size(); ++j) // �ڴ�ѭ��������������
		{
			sum += array[j]; // �����еĺ�
			if(sum >= s) // ��������еĺ���������
			{
				subLength = j - i + 1; // ��������еĳ���
				result = (result < subLength) ? result : subLength; // �������������������еĳ���
				break; // ����ҵ�һ�����������������У����˳��ڲ�ѭ��
			}
		}
	}
	return result == INT32_MAX ? 0 : result; // û�з��ϵ������з��� 0 �����򷵻���������еĳ���
}

// �ⷨ 2����������
int minSubArrayLen1(vector<int>& array, int s)
{
	// INT32_MAX �꣬�����ͱ����ܹ��洢����������������� limits.h ͷ�ļ���
	int result = INT32_MAX; // ����Ҫ���ص������г���
	int sum = 0; // ���������еĺ�
	int subLength = 0; // ���������еĳ���
	int i = 0; // �����е���ʼλ��

	for (int j = 0; j < array.size(); ++j)
	{
		sum += array[j]; // �����еĺ�
		while (sum >= s) // ����⵽�з��ϵ�������ʱ
		{
			subLength = j - i + 1; // ����������������г���
			result = (result < subLength) ? result : subLength;
			sum -= array[i++]; // ��̬�ر�������е���ʼλ��
		}
	}
	return result == INT32_MAX ? 0 : result; // �����ڷ��������������оͷ��� 0 �����򷵻���������С�
}

// 5�����������
// ��Ŀ��
// ����һ���������� Array��������������ÿ��ָ��������Ԫ�ص��ܺ͡�
// �������� [1,2,3,4,5] �������±� 0~2 �ĺ;��� 1+2+3=6 ���±� 1~3 �ĺ;��� 2+3+4=9

// �ⷨ 1��ֱ���ۼӶ�Ӧ����ĺ͡����Ƽ���ʱ�临�ӶȽϴ�
int gapSum()
{
	int n, a, b; // n �����鳤�ȣ������� a~b
	cout << "please input length of array :" << endl;
	cin >> n; // ��������ĳ���
	vector<int>vector(n);
	cout << "�����������Ԫ��" << endl;
	for (int i = 0; i < n; ++i)
		cin >> vector[i];
	cout << "��������" << endl;
	cin >> a >> b;
	int sum = 0;
	for (int i = a; i <= b; ++i)
		sum += vector[i];
	return sum;
}

// �ⷨ 2:ǰ׺�͡���˼�����ظ����ü������������֮�ͣ��Ӷ����������ѯ��Ҫ�ۼӼ���Ĵ�����
// ǰ׺�;���ⷨ�������� vec[i] ��p[i] ��ʾ vec[0]~vec[i] ���ۼӺ�
// ���� p[1] = vec[0] + vec[1] , p[3] = vec[0] + vec[1] + vec[2] + vec[3]
// ��ôҪ�����±� 2~3 �ĺͣ�ʹ�� p[3] - p[1] = vec[2] + vec[3]
// ��Ҫע����������Ǽ� p[1] ,���Ǽ� p[2] ��
// ��Ҫ������ a~b �ĺͣ���� a=0,ֱ�ӷ��� p[b],���򷵻� p[b]-p[a-1]

int gapSum1()
{
	int n, a, b; // n �����鳤�ȣ������� a~b
	cout << "please input length of array :" << endl;
	cin >> n; // ��������ĳ���
	vector<int>vec(n); // �������Ԫ��
	vector<int>p(n); // �������ǰ׺��
	int pre_sum = 0; // ��ʼ��ǰ׺��
	cout << "�����������Ԫ��" << endl;
	for (int i = 0; i < n; ++i)
	{
		cin >> vec[i]; // ��������Ԫ��
		pre_sum += vec[i]; // ����ǰ׺��
		p[i] = pre_sum; // ǰ׺����ӵ�������
	}
	cout << "��������" << endl;
	cin >> a >> b;
	int sum = 0; // ������Ҫ���ص�ǰ׺��
	if (a == 0)sum = p[b]; // ����±�� 0 ��ʼ
	else
		sum = p[b] - p[a - 1]; 
	return sum;
}

// 6����������
// �ⷨ 1��
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
		
// �ⷨ 2������ģ��
// ���Խ����󿴳����ɲ㣬�������������Ԫ�أ�������������Ԫ�أ�ֱ��������ڲ��Ԫ�ء�
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

