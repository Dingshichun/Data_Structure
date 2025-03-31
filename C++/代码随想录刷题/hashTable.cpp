#include"head.h"

// 1�����������ַ��� s �� t ����дһ���������ж� t �Ƿ��� s ����ĸ��λ�ʡ�
// ˵�� : ����Լ����ַ���ֻ����Сд��ĸ��
// ʾ�� 1: ����: s = "anagram", t = "nagaram" ��� : true
// ʾ�� 2 : ���� : s = "rat", t = "car" ��� : false

// �ⷨ 1�����㱩��ѭ����ʱ�临�Ӷ���O(n^2)�����Ƽ���

// �ⷨ 2����˵����ͳ��һ���ַ����������ַ����ֵĴ�������ӳ��Ϊ��ϣ����ͳ����һ���ַ����Ĵ�����
// ������ʵ����һ���򵥹�ϣ�����ҹ涨�ַ���ֻ��Сд����ô�Ϳ��Զ���һ������ record������¼�ַ��� s ���ַ����ֵĴ�����  
// ��Ϊ��ĸ�� 26 �������ַ� a ���ַ� z �� ASCII Ҳ�� 26 ����������ֵ����������ĳ��ȶ���Ϊ 26������ʼ��Ϊ 0.

// ���ַ�ӳ�䵽����Ҳ���ǹ�ϣ��������±��ϣ���Ϊ�ַ� a ���ַ� z �� ASCII �� 26 ����������ֵ��
// �����ַ� a ӳ��Ϊ�±� 0 ����Ӧ���ַ� z ӳ��Ϊ�±� 25��

// �����ַ���s��ʱ��ֻ��Ҫ�� s[i] - 'a' ���ڵ�Ԫ���� + 1 �������ɣ�������Ҫ��ס�ַ�a��ASCII��ֻҪ���һ�������ֵ�Ϳ����ˡ�
// �����ͽ��ַ���s���ַ����ֵĴ�����ͳ�Ƴ����ˡ�

// ����ַ��� t ���Ƿ��������Щ�ַ���ͬ���ڱ��� t ��ʱ�򣬶� t �г��ֵ��ַ�ӳ���ϣ�������ϵ���ֵ���� -1 �Ĳ�����
// ������ record �����е�Ԫ�ز�Ϊ�� 0��˵���ַ��� s �� t ���ַ����ִ�������ȫһ�£�return false��
// ������ record ��������Ԫ�ض�Ϊ�� 0��˵���ַ��� s �� t ����ĸ��λ�ʣ�return true��
// ʱ�临�Ӷ�Ϊ O(n)���ռ�����Ϊ�����ǵ�һ��������С�ĸ������飬���Կռ临�Ӷ�Ϊ O(1)��

bool isAnagram(string s, string t)
{
	int record[26] = {0}; // ��СΪ 26 ������
	for (int i = 0; i < s.size(); ++i) // �����ַ��� s ��ͳ�������ַ����ִ���
	{
		// a-z �� ASCII ���������ģ��������±��Ǵ� 0 ��ʼ����� s[i] �� 'a' ,��ô���� record[0] ��һ���� 'b' �� record[1] ��һ
		++record[s[i] - 'a'];  // �� s �е���ĸ��Ӧλ�ü�һ
	}
	for (int i = 0; i < t.size(); ++i) // �����ַ��� t
		--record[t[i] - 'a']; // �� t �е���ĸ��Ӧλ�ü�һ

	for (int i = 0; i < 26; ++i)
	{
        // �����Ҵ���������飬��������ַ�������ĸ��λ�ʣ���ô�������ȫ�ǳ�ʼֵ 0
		if (record[i] != 0)
			return false;
	}
	return true;
}

// 2��û��ȫ���
// �ַ������� words ���ҳ������� words ��ÿ���ַ����ж����ֵĹ����ַ��� �����ظ��ַ�����
// ����������ʽ���ء�����԰� ����˳�� ���ش𰸡�

// ʾ�� 1��
// ���룺words = ["bella", "label", "roller"] �����["e", "l", "l"]

// ʾ�� 2��
// ���룺words = ["cool", "lock", "cook"] �����["c", "o"]

// �ⷨ 1����ϣ��
vector<string> commonChars(vector<string>& A) 
{
    vector<string> result;
    if (A.size() == 0) return result;
    int hash[26] = { 0 }; // ����ͳ�������ַ������ַ����ֵ���СƵ��
    for (int i = 0; i < A[0].size(); i++) 
    { // �õ�һ���ַ����� hash ��ʼ��
        hash[A[0][i] - 'a']++;
    }

    int hashOtherStr[26] = { 0 }; // ͳ�Ƴ���һ���ַ������ַ��ĳ���Ƶ��
    for (int i = 1; i < A.size(); i++) 
    {
        // ��һ���ص����
        // ÿ��ѭ������ hashOtherStr ��ʼ��Ϊȫ 0
        memset(hashOtherStr, 0, 26 * sizeof(int)); 
        for (int j = 0; j < A[i].size(); j++) 
            hashOtherStr[A[i][j] - 'a']++;

        // ���� hash����֤ hash ��ͳ�� 26 ���ַ��������ַ�������ֵ���С����
        for (int k = 0; k < 26; k++) 
            hash[k] = min(hash[k], hashOtherStr[k]);
    }
    // �� hash ͳ�Ƶ��ַ�������ת�������ʽ
    for (int i = 0; i < 26; i++) 
    {
        while (hash[i] != 0) 
        { // ע�������� while������ظ����ַ�
            string s(1, i + 'a'); // char -> string
            result.push_back(s);
            hash[i]--;
        }
    }
    return result;
}

// 3������Ľ�����**��
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
{
    // unordered_set �е�Ԫ���ǲ����ظ��ģ����Ҫ�����Ԫ���Ѿ��� unordered_set �У�
    // �򲻻��ٲ���֮ǰҪ�����Ԫ�ء�
    unordered_set<int> result_set; // ��Ž����֮������ set ��Ϊ�˸������ȥ��

    // �� nums1 ��Ԫ�ؼ��뵽 nums_set �����Զ�ȥ�أ���Ϊ�ظ���Ԫ����ͳ�ƽ���ʱû��ʹ�á�
    unordered_set<int> nums_set(nums1.begin(), nums1.end());
    for (int num : nums2) 
    {
        // ���� nums2 ��Ԫ�� �� nums_set ���ֳ��ֹ�
        if (nums_set.find(num) != nums_set.end()) 
        {
            result_set.insert(num);
        }
    }
    return vector<int>(result_set.begin(), result_set.end());
}

// 4��������
// ����������Ϊ������һ����������ÿһ�ν������滻Ϊ��ÿ��λ���ϵ����ֵ�ƽ���ͣ�
// Ȼ���ظ��������ֱ���������Ϊ 1��Ҳ������ ����ѭ�� ��ʼ�ձ䲻�� 1�� 
// ��� ���Ա�Ϊ  1����ô��������ǿ�������

// ����˼·��
// ������ѭ����Ҳ��������͵Ĺ����У�sum ���ظ����֣�
// ���Կ���ʹ�ù�ϣ�����ж�������᲻���ظ����֣�
// �ж� sum �Ƿ��ظ����־Ϳ���ʹ�� unordered_set ��

// �ȶ���ȡһ��������λƽ���͵ĺ���
int getSum(int n)
{
    int sum = 0;
    while (n)
    {
        sum += (n % 10) * (n % 10); // ����ȡ���Ǹ�λ
        n /= 10; // �� n ��С 10 ������ȡ��С��ĸ�λ
    }
    return sum;
}

bool isHappyNum(int n)
{
    unordered_set<int>set;
    while (1) // ����ѭ����������������ֹ
    {
        int sum = getSum(n); // ȡƽ����
        if (sum == 1) // ƽ������ 1 ���ǿ�����
            return true;

        // ������ sum �������ֹ���˵���Ѿ�����������ѭ���ˣ������Ͳ��ǿ�����
        if (set.find(sum) != set.end())
            return false;
        else
            set.insert(sum); // ���뵽������
        n = sum; // n ����Ϊƽ����
    }
}

// 5������֮��
// ����һ���������� nums ��һ��Ŀ��ֵ target�������ڸ��������ҳ���ΪĿ��ֵ���� ���� ���������������ǵ������±ꡣ
// ����Լ���ÿ������ֻ���Ӧһ���𰸡����ǣ�������ͬһ��Ԫ�ز���ʹ�����顣

// ����˼·
// ����Ҫ֪��Ԫ����û�б���������Ҫ֪�����Ԫ�ض�Ӧ���±꣬��Ҫʹ�� key value �ṹ����ţ�
// key ����Ԫ�أ�value �����±꣬��ôʹ�� map �����ʡ�
// ��Ŀ�в�����Ҫ key ����ѡ�� std::unordered_map Ч�ʸ��ߣ�

vector<int>twoSum(vector<int>& nums, int target)
{
    // ���洢������ֵ��ֵ�洢������ֵ�������±�
    unordered_map<int,int>map;
    for (int i = 0; i < nums.size(); ++i)
    {
        // ������ǰԪ�أ����� map ��Ѱ���Ƿ���ƥ��� key�� ���� key �洢������ֵ
        auto iter = map.find(target - nums[i]);
        if (iter != map.end())
        {
            // iter->first ��ʾ�� key �����������ֵ��
            // iter->second ��ʾֵ val�����������ֵ��Ӧ�������±�
            return { iter->second,i }; // ���غ�Ϊ target ��������ֵ���±�
        }
        // ���û�ҵ�ƥ��ԣ��Ͱѷ��ʹ���Ԫ�غ��±���뵽 map ��
        map.insert(pair<int, int>(nums[i], i));
    }
    return {};
}

// 6������֮��
// ��Ŀ��
// �����ĸ����������������б� A, B, C, D, �����ж��ٸ�Ԫ��(i, j, k, l) ��
// ʹ�� A[i] + B[j] + C[k] + D[l] = 0��
// Ϊ��ʹ����򵥻������е� A, B, C, D ������ͬ�ĳ��� N���� 0 �� N �� 500 ��
// ���������ķ�Χ�� - 2 ^ 28 �� 2 ^ 28 - 1 ֮�䣬���ս�����ᳬ�� 2 ^ 31 - 1 ��

// ����˼·��
// �ĸ����������飬ֻҪ�ҵ� A[i] + B[j] + C[k] + D[l] = 0 �Ϳ��ԣ�
// ���ÿ������ظ����ĸ�Ԫ����ӵ��� 0 �������

// ���ⲽ�裺
// 1�����ȶ��� һ�� unordered_map��key �� a �� b ����֮�ͣ�value ��a��b����֮�ͳ��ֵĴ�����
// 2�������� A �ʹ� B ���飬ͳ����������Ԫ��֮�ͣ��ͳ��ֵĴ������ŵ� map �С�
// 3������ int ���� count������ͳ�� a + b + c + d = 0 ���ֵĴ�����
// 4���ٱ����� C �ʹ� D ���飬�ҵ���� 0 - (c + d) ��map�г��ֹ��Ļ������� count �� map �� key ��Ӧ�� value Ҳ���ǳ��ִ���ͳ�Ƴ�����
// 5����󷵻�ͳ��ֵ count �Ϳ�����
int fourNumSum(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
{
    unordered_map<int,int>umap; // ���������֮�ͣ�ֵ��������ͳ��ֵĴ���
    
    // ������ A �ʹ� B ���飬ͳ����������Ԫ��֮�ͣ��ͳ��ֵĴ������ŵ� map ��
    for (int a : A)
        for (int b : B)
            ++umap[a + b]; // �����ͳ��ֵĴ�����һ

    int count = 0; // ͳ�� a+b+c+d = 0 ���ֵĴ���
    
    // �ٱ����� C �ʹ� D ���飬�ҵ���� 0-(c+d) �� map �г��ֹ��Ļ���
    // �Ͱ� map �� key ��Ӧ�� value Ҳ���ǳ��ִ���ͳ�Ƴ�����
    for(int c:C)
        for (int d : D)
        {
            auto iter = umap.find(0 - (c + d));
            if (iter != umap.end())
                count += umap[0 - (c + d)]; 
        }
    return count;
}

// 7�������
// ��Ŀ��
//����һ�������(ransom) �ַ�����һ����־(magazine)�ַ�����
//�жϵ�һ���ַ��� ransom �ܲ����ɵڶ����ַ��� magazines ������ַ����ɡ�

// ��Ŀ˵����
// Ϊ�˲���¶������ּ���Ҫ����־������������Ҫ����ĸ����ɵ����������˼��
// ��־�ַ����е�ÿ���ַ�ֻ����������ַ�����ʹ��һ�Ρ�
// ע�⣬���Լ��������ַ�����ֻ����Сд��ĸ��

// Ҳ�Ǵ���һ�����飬��¼�����ַ����е��ַ����ִ�����
// ����һ����ʱ�����Ӵ�������һ������ٴ�����
// �����������г���С�� 0 �������˵�����ܹ��ɡ�
bool canConstruct(string ransomNote, string magazine)
{
    // ���� magazine �е�ÿ���ַ�ֻ��ʹ��һ�Σ����� magazine �ĳ��ȱ�����ڵ��� ransom ���ܹ���
    if (ransomNote.size() > magazine.size())
        return false;
    // ���������¼�ַ����ִ�������ĸֻ�� 26 ����
    int record[26] = { 0 };

    // �����ȱ��� magazine����¼���ַ����ִ���
    for (int i = 0; i < magazine.size(); ++i)
        ++record[magazine[i] - 'a']; // 'a'-'z' �� ASCII ����������
    for (int i = 0; i < ransomNote.size(); ++i)
        --record[ransomNote[i] - 'a'];
    
    // ��Ϊ�Ǵ� magazine ��ѡ�����ȼ�¼ magazin �ַ�������
    // ��������¼���������������Ԫ�ر�����ڵ��� 0 ���ܹ��ɡ�
    // ��Ȼ������ȼ�¼ ransom ���������Ԫ�ر���С�ڵ��� 0 ���ܹ��ɡ�
    for (int i = 0; i < 26; ++i)
    {
        if (record[i] < 0)
            return false;
    }
    return true;
}

bool canConstruct1(string ransom, string magazine)
{
    if (magazine.size() < ransom.size())
        return false;

    int record[26] = { 0 };
    // �ȱ��� ransom
    for (int i = 0; i < ransom.size(); ++i)
        ++record[ransom[i] - 'a'];
    for (int i = 0; i < magazine.size(); ++i)
        --record[magazine[i] - 'a'];
    for (int i = 0; i < 26; ++i)
    {
        // �ж�������֮�ı�
        if (record[i] > 0)
            return false;
    }
    return true;
}

// 8������֮��
// ����һ���������� nums ���ж��Ƿ������Ԫ��[nums[i], nums[j], nums[k]] 
// ���� i != j��i != k �� j != k ��ͬʱ������ nums[i] + nums[j] + nums[k] == 0 ��
// ���㷵�����к�Ϊ 0 �Ҳ��ظ�����Ԫ�顣

// �ⷨ 1����ϣ���������ʣ���Ϊȥ�ز���ϸ�ںܶ࣬��ʱ�临�ӶȽϸߡ�

// �ⷨ 2: ˫ָ�롣
/*���Ƚ���������Ȼ����һ�� for ѭ����i ���±� 0 �ĵط���ʼ��
ͬʱ��һ���±� left ������ i + 1 ��λ���ϣ������±� right �������β��λ���ϡ�
��Ȼ�������������ҵ� abc ʹ�� a + b + c = 0�����������൱�� a = nums[i]��b = nums[left]��c = nums[right]��

����������ƶ� left �� right �أ� ��� nums[i] + nums[left] + nums[right] > 0 
��˵�� ��ʱ����֮�ʹ��ˣ���Ϊ������������ˣ�
���� right �±��Ӧ�������ƶ�����������������֮��СһЩ��

��� nums[i] + nums[left] + nums[right] < 0 
˵����ʱ ����֮��С�ˣ�left �������ƶ�������������֮�ʹ�һЩ��ֱ�� left �� right ����Ϊֹ��*/

vector<vector<int>>threeNumSum(vector<int>& nums)
{
    vector<vector<int>>result; // ��ŷ������������
    sort(nums.begin(),nums.end()); // ����Ĭ���Ǵ�С����
    
    // �ҳ� a + b + c = 0
    // a = nums[i], b = nums[left], c = nums[right]

    for (int i=0;i<nums.size();++i)
    {
        if (nums[i] > 0) // �����ĵ�һ��Ԫ�ض����� 0 ���򲻻��к�Ϊ 0 �����
            return result;

        // ����ȥ�� a ����������©�� -1,-1,2 �������
            /*
            if (nums[i] == nums[i + 1]) {
                continue;
            }
            */
        // ��ȷȥ�� a ����
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1; // ��ָ��ָ�� i ����һ��λ��
        int right = nums.size() - 1; // ��ָ���ʼָ�����һ����
        while (left < right)
        {
            if (nums[i] + nums[left] + nums[right] < 0)
                ++left;
            else if (nums[i] + nums[left] + nums[right] > 0)
                --right;
            else
            {
                // ��������������Ϸŵ� result ������
                result.push_back(vector<int>{nums[i], nums[left], nums[right]});

                // ȥ���߼�Ӧ�÷����ҵ�һ����Ԫ��֮�󣬶� b �� c ȥ��
                while (left < right && nums[right] == nums[right - 1])
                    --right;
                while (left < right && nums[left] == nums[left + 1])
                    ++left;
                
                // �ҵ����������Ľ��ʱ������ָ��ͬʱ����
                ++left;
                --right;
            }
        }
    }
    return result;
}

// 9������֮��
/*����һ���� n ��������ɵ����� nums ����һ��Ŀ��ֵ target ��
�����ҳ���������������ȫ�������Ҳ��ظ�����Ԫ��[nums[a], nums[b], nums[c], nums[d]] 
����������Ԫ��Ԫ��һһ��Ӧ������Ϊ������Ԫ���ظ�����

0 <= a, b, c, d < n
a��b��c �� d ������ͬ
nums[a] + nums[b] + nums[c] + nums[d] == target
����԰� ����˳�� ���ش� ��*/

// ����˼·��
// ���������������ƣ�Ҳ��ʹ��˫ָ�룬ֻ���м���һ�� for ѭ��
vector<vector<int>>fourSum(vector<int>& nums, int target)
{
    vector<vector<int>>result; // ��ŷ������������
    sort(nums.begin(), nums.end()); // ����

    for (int k = 0; k < nums.size(); ++k) // ��һ��ѭ��
    {
        // ��֦�������һ���������������˳�ѭ�������ٲ���Ҫ�Ĳ�����
        if (nums[k] > target && nums[k] >= 0) 
            break; // ʹ�� break ��ͳһͨ������ return ����
        
        // �� nums[k] ȥ��
        if (k > 0 && nums[k] == nums[k - 1])
            continue;

        // �ڶ���ѭ�����ӵ�һ��ѭ������һ��λ�ÿ�ʼ
        for (int i = k + 1; i < nums.size(); ++i)
        {
            // ��֦������������ֱ���˳�
            if ((nums[k] + nums[i]) > target && (nums[k] + nums[i]) >= 0)
                break;

            // �� nums[i] ȥ��
            if (i > k + 1 && nums[i] == nums[i - 1])
                continue;

            // ��������ָ��
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) // ѭ������
            {
                // ʹ�� long �������
                if ((long)nums[k] + nums[i] + nums[left] + nums[right] < target)
                    ++left; // �ĸ����ĺ�С�� target ����ָ������
                else if ((long)nums[k] + nums[i] + nums[left] + nums[right] > target)
                    --right; // �ĸ����ĺʹ��� target ����ָ�����ơ�
                else
                {
                    // ��������������Ϸ�������
                    result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                    
                    // �� nums[left] �� nums[right] ȥ��
                    while (left < right && nums[left] == nums[left + 1])
                        ++left;
                    while (left < right && nums[right] == nums[right - 1])
                        --right;

                    // �з������������ʱ������ָ��ͬʱ������
                    ++left;
                    --right;
                }
            }
        }
    }
    return result;
}
