#include"head.h"

// 1、给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
// 说明 : 你可以假设字符串只包含小写字母。
// 示例 1: 输入: s = "anagram", t = "nagaram" 输出 : true
// 示例 2 : 输入 : s = "rat", t = "car" 输出 : false

// 解法 1：两层暴力循环，时间复杂度是O(n^2)，不推荐。

// 解法 2：简单说就是统计一个字符串中所有字符出现的次数，并映射为哈希表，再统计另一个字符串的次数。
// 数组其实就是一个简单哈希表，而且规定字符串只有小写，那么就可以定义一个数组 record，来记录字符串 s 里字符出现的次数。  
// 因为字母有 26 个，且字符 a 到字符 z 的 ASCII 也是 26 个连续的数值。所以数组的长度定义为 26，并初始化为 0.

// 把字符映射到数组也就是哈希表的索引下标上，因为字符 a 到字符 z 的 ASCII 是 26 个连续的数值，
// 所以字符 a 映射为下标 0 ，相应的字符 z 映射为下标 25。

// 遍历字符串s的时候，只需要将 s[i] - 'a' 所在的元素做 + 1 操作即可，并不需要记住字符a的ASCII，只要求出一个相对数值就可以了。
// 这样就将字符串s中字符出现的次数，统计出来了。

// 检查字符串 t 中是否出现了这些字符，同样在遍历 t 的时候，对 t 中出现的字符映射哈希表索引上的数值再做 -1 的操作。
// 最后，如果 record 数组有的元素不为零 0，说明字符串 s 和 t 的字符出现次数不完全一致，return false。
// 最后如果 record 数组所有元素都为零 0，说明字符串 s 和 t 是字母异位词，return true。
// 时间复杂度为 O(n)，空间上因为定义是的一个常量大小的辅助数组，所以空间复杂度为 O(1)。

bool isAnagram(string s, string t)
{
	int record[26] = {0}; // 大小为 26 的数组
	for (int i = 0; i < s.size(); ++i) // 遍历字符串 s ，统计其中字符出现次数
	{
		// a-z 的 ASCII 码是连续的，且数组下标是从 0 开始，如果 s[i] 是 'a' ,那么代表 record[0] 加一，是 'b' 则 record[1] 加一
		++record[s[i] - 'a'];  // 将 s 中的字母对应位置加一
	}
	for (int i = 0; i < t.size(); ++i) // 遍历字符串 t
		--record[t[i] - 'a']; // 将 t 中的字母对应位置减一

	for (int i = 0; i < 26; ++i)
	{
        // 最后查找处理完的数组，如果两个字符串是字母异位词，那么最后数组全是初始值 0
		if (record[i] != 0)
			return false;
	}
	return true;
}

// 2、没完全清楚
// 字符串数组 words ，找出所有在 words 的每个字符串中都出现的共用字符（ 包括重复字符），
// 并以数组形式返回。你可以按 任意顺序 返回答案。

// 示例 1：
// 输入：words = ["bella", "label", "roller"] 输出：["e", "l", "l"]

// 示例 2：
// 输入：words = ["cool", "lock", "cook"] 输出：["c", "o"]

// 解法 1：哈希表
vector<string> commonChars(vector<string>& A) 
{
    vector<string> result;
    if (A.size() == 0) return result;
    int hash[26] = { 0 }; // 用来统计所有字符串里字符出现的最小频率
    for (int i = 0; i < A[0].size(); i++) 
    { // 用第一个字符串给 hash 初始化
        hash[A[0][i] - 'a']++;
    }

    int hashOtherStr[26] = { 0 }; // 统计除第一个字符串外字符的出现频率
    for (int i = 1; i < A.size(); i++) 
    {
        // 这一句重点理解
        // 每次循环都将 hashOtherStr 初始化为全 0
        memset(hashOtherStr, 0, 26 * sizeof(int)); 
        for (int j = 0; j < A[i].size(); j++) 
            hashOtherStr[A[i][j] - 'a']++;

        // 更新 hash，保证 hash 里统计 26 个字符在所有字符串里出现的最小次数
        for (int k = 0; k < 26; k++) 
            hash[k] = min(hash[k], hashOtherStr[k]);
    }
    // 将 hash 统计的字符次数，转成输出形式
    for (int i = 0; i < 26; i++) 
    {
        while (hash[i] != 0) 
        { // 注意这里是 while，多个重复的字符
            string s(1, i + 'a'); // char -> string
            result.push_back(s);
            hash[i]--;
        }
    }
    return result;
}

// 3、数组的交集（**）
vector<int> intersection(vector<int>& nums1, vector<int>& nums2) 
{
    // unordered_set 中的元素是不会重复的，如果要插入的元素已经在 unordered_set 中，
    // 则不会再插入之前要插入的元素。
    unordered_set<int> result_set; // 存放结果，之所以用 set 是为了给结果集去重

    // 将 nums1 的元素加入到 nums_set ，并自动去重，因为重复的元素在统计交集时没有使用。
    unordered_set<int> nums_set(nums1.begin(), nums1.end());
    for (int num : nums2) 
    {
        // 发现 nums2 的元素 在 nums_set 里又出现过
        if (nums_set.find(num) != nums_set.end()) 
        {
            result_set.insert(num);
        }
    }
    return vector<int>(result_set.begin(), result_set.end());
}

// 4、快乐数
// 快乐数定义为：对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和，
// 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。 
// 如果 可以变为  1，那么这个数就是快乐数。

// 解题思路：
// 会无限循环，也就是在求和的过程中，sum 会重复出现，
// 所以可以使用哈希法来判断这个数会不会重复出现，
// 判断 sum 是否重复出现就可以使用 unordered_set 。

// 先定义取一个数各个位平方和的函数
int getSum(int n)
{
    int sum = 0;
    while (n)
    {
        sum += (n % 10) * (n % 10); // 这里取的是个位
        n /= 10; // 将 n 缩小 10 倍，再取缩小后的个位
    }
    return sum;
}

bool isHappyNum(int n)
{
    unordered_set<int>set;
    while (1) // 无限循环，遇到条件才终止
    {
        int sum = getSum(n); // 取平方和
        if (sum == 1) // 平方和是 1 则是快乐数
            return true;

        // 如果这个 sum 曾经出现过，说明已经陷入了无限循环了，该数就不是快乐数
        if (set.find(sum) != set.end())
            return false;
        else
            set.insert(sum); // 插入到集合中
        n = sum; // n 更新为平方和
    }
}

// 5、两数之和
// 给定一个整数数组 nums 和一个目标值 target，请你在该数组中找出和为目标值的那 两个 整数，并返回他们的数组下标。
// 你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

// 解题思路
// 不仅要知道元素有没有遍历过，还要知道这个元素对应的下标，需要使用 key value 结构来存放，
// key 来存元素，value 来存下标，那么使用 map 正合适。
// 题目中并不需要 key 有序，选择 std::unordered_map 效率更高！

vector<int>twoSum(vector<int>& nums, int target)
{
    // 键存储的是数值，值存储的是数值的索引下标
    unordered_map<int,int>map;
    for (int i = 0; i < nums.size(); ++i)
    {
        // 遍历当前元素，并在 map 中寻找是否有匹配的 key， 这里 key 存储的是数值
        auto iter = map.find(target - nums[i]);
        if (iter != map.end())
        {
            // iter->first 表示键 key ，这里就是数值，
            // iter->second 表示值 val，这里就是数值对应的索引下标
            return { iter->second,i }; // 返回和为 target 的两个数值的下标
        }
        // 如果没找到匹配对，就把访问过的元素和下标加入到 map 中
        map.insert(pair<int, int>(nums[i], i));
    }
    return {};
}

// 6、四数之和
// 题目：
// 给定四个包含整数的数组列表 A, B, C, D, 计算有多少个元组(i, j, k, l) ，
// 使得 A[i] + B[j] + C[k] + D[l] = 0。
// 为了使问题简单化，所有的 A, B, C, D 具有相同的长度 N，且 0 ≤ N ≤ 500 。
// 所有整数的范围在 - 2 ^ 28 到 2 ^ 28 - 1 之间，最终结果不会超过 2 ^ 31 - 1 。

// 解题思路：
// 四个独立的数组，只要找到 A[i] + B[j] + C[k] + D[l] = 0 就可以，
// 不用考虑有重复的四个元素相加等于 0 的情况，

// 解题步骤：
// 1、首先定义 一个 unordered_map，key 放 a 和 b 两数之和，value 放a和b两数之和出现的次数。
// 2、遍历大 A 和大 B 数组，统计两个数组元素之和，和出现的次数，放到 map 中。
// 3、定义 int 变量 count，用来统计 a + b + c + d = 0 出现的次数。
// 4、再遍历大 C 和大 D 数组，找到如果 0 - (c + d) 在map中出现过的话，就用 count 把 map 中 key 对应的 value 也就是出现次数统计出来。
// 5、最后返回统计值 count 就可以了
int fourNumSum(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D)
{
    unordered_map<int,int>umap; // 键存放两数之和，值存放两数和出现的次数
    
    // 遍历大 A 和大 B 数组，统计两个数组元素之和，和出现的次数，放到 map 中
    for (int a : A)
        for (int b : B)
            ++umap[a + b]; // 两数和出现的次数加一

    int count = 0; // 统计 a+b+c+d = 0 出现的次数
    
    // 再遍历大 C 和大 D 数组，找到如果 0-(c+d) 在 map 中出现过的话，
    // 就把 map 中 key 对应的 value 也就是出现次数统计出来。
    for(int c:C)
        for (int d : D)
        {
            auto iter = umap.find(0 - (c + d));
            if (iter != umap.end())
                count += umap[0 - (c + d)]; 
        }
    return count;
}

// 7、赎金信
// 题目：
//给定一个赎金信(ransom) 字符串和一个杂志(magazine)字符串，
//判断第一个字符串 ransom 能不能由第二个字符串 magazines 里面的字符构成。

// 题目说明：
// 为了不暴露赎金信字迹，要从杂志上搜索各个需要的字母，组成单词来表达意思。
// 杂志字符串中的每个字符只能在赎金信字符串中使用一次。
// 注意，可以假设两个字符串均只含有小写字母。

// 也是创建一个数组，记录两个字符串中的字符出现次数。
// 遍历一个的时候增加次数，另一个则减少次数，
// 最后如果数组中出现小于 0 的情况，说明不能构成。
bool canConstruct(string ransomNote, string magazine)
{
    // 由于 magazine 中的每个字符只能使用一次，所以 magazine 的长度必须大于等于 ransom 才能构成
    if (ransomNote.size() > magazine.size())
        return false;
    // 创建数组记录字符出现次数，字母只有 26 个，
    int record[26] = { 0 };

    // 这里先遍历 magazine，记录其字符出现次数
    for (int i = 0; i < magazine.size(); ++i)
        ++record[magazine[i] - 'a']; // 'a'-'z' 的 ASCII 码是连续的
    for (int i = 0; i < ransomNote.size(); ++i)
        --record[ransomNote[i] - 'a'];
    
    // 因为是从 magazine 中选，且先记录 magazin 字符次数，
    // 所以最后记录次数的数组的所有元素必须大于等于 0 才能构成。
    // 当然，如果先记录 ransom ，最后所有元素必须小于等于 0 才能构成。
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
    // 先遍历 ransom
    for (int i = 0; i < ransom.size(); ++i)
        ++record[ransom[i] - 'a'];
    for (int i = 0; i < magazine.size(); ++i)
        --record[magazine[i] - 'a'];
    for (int i = 0; i < 26; ++i)
    {
        // 判断条件随之改变
        if (record[i] > 0)
            return false;
    }
    return true;
}

// 8、三数之和
// 给你一个整数数组 nums ，判断是否存在三元组[nums[i], nums[j], nums[k]] 
// 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
// 请你返回所有和为 0 且不重复的三元组。

// 解法 1：哈希法，不合适，因为去重操作细节很多，且时间复杂度较高。

// 解法 2: 双指针。
/*首先将数组排序，然后有一层 for 循环，i 从下标 0 的地方开始，
同时定一个下标 left 定义在 i + 1 的位置上，定义下标 right 在数组结尾的位置上。
依然还是在数组中找到 abc 使得 a + b + c = 0，我们这里相当于 a = nums[i]，b = nums[left]，c = nums[right]。

接下来如何移动 left 和 right 呢， 如果 nums[i] + nums[left] + nums[right] > 0 
就说明 此时三数之和大了，因为数组是排序后了，
所以 right 下标就应该向左移动，这样才能让三数之和小一些。

如果 nums[i] + nums[left] + nums[right] < 0 
说明此时 三数之和小了，left 就向右移动，才能让三数之和大一些，直到 left 与 right 相遇为止。*/

vector<vector<int>>threeNumSum(vector<int>& nums)
{
    vector<vector<int>>result; // 存放符合条件的组合
    sort(nums.begin(),nums.end()); // 排序，默认是从小到大
    
    // 找出 a + b + c = 0
    // a = nums[i], b = nums[left], c = nums[right]

    for (int i=0;i<nums.size();++i)
    {
        if (nums[i] > 0) // 排序后的第一个元素都大于 0 ，则不会有和为 0 的组合
            return result;

        // 错误去重 a 方法，将会漏掉 -1,-1,2 这种情况
            /*
            if (nums[i] == nums[i + 1]) {
                continue;
            }
            */
        // 正确去重 a 方法
        if (i > 0 && nums[i] == nums[i - 1])
            continue;

        int left = i + 1; // 左指针指向 i 的下一个位置
        int right = nums.size() - 1; // 右指针最开始指向最后一个数
        while (left < right)
        {
            if (nums[i] + nums[left] + nums[right] < 0)
                ++left;
            else if (nums[i] + nums[left] + nums[right] > 0)
                --right;
            else
            {
                // 将符合条件的组合放到 result 容器中
                result.push_back(vector<int>{nums[i], nums[left], nums[right]});

                // 去重逻辑应该放在找到一个三元组之后，对 b 和 c 去重
                while (left < right && nums[right] == nums[right - 1])
                    --right;
                while (left < right && nums[left] == nums[left + 1])
                    ++left;
                
                // 找到符合条件的结果时，左、右指针同时收缩
                ++left;
                --right;
            }
        }
    }
    return result;
}

// 9、四数之和
/*给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。
请你找出并返回满足下述全部条件且不重复的四元组[nums[a], nums[b], nums[c], nums[d]] 
（若两个四元组元素一一对应，则认为两个四元组重复）：

0 <= a, b, c, d < n
a、b、c 和 d 互不相同
nums[a] + nums[b] + nums[c] + nums[d] == target
你可以按 任意顺序 返回答案 。*/

// 解题思路：
// 和三数和问题类似，也是使用双指针，只是中间多加一层 for 循环
vector<vector<int>>fourSum(vector<int>& nums, int target)
{
    vector<vector<int>>result; // 存放符合条件的组合
    sort(nums.begin(), nums.end()); // 排序

    for (int k = 0; k < nums.size(); ++k) // 第一层循环
    {
        // 剪枝。即如果一定不满足条件就退出循环，减少不必要的操作，
        if (nums[k] > target && nums[k] >= 0) 
            break; // 使用 break ，统一通过最后的 return 返回
        
        // 对 nums[k] 去重
        if (k > 0 && nums[k] == nums[k - 1])
            continue;

        // 第二层循环，从第一层循环的下一个位置开始
        for (int i = k + 1; i < nums.size(); ++i)
        {
            // 剪枝。不符合条件直接退出
            if ((nums[k] + nums[i]) > target && (nums[k] + nums[i]) >= 0)
                break;

            // 对 nums[i] 去重
            if (i > k + 1 && nums[i] == nums[i - 1])
                continue;

            // 定义左、右指针
            int left = i + 1;
            int right = nums.size() - 1;
            while (left < right) // 循环条件
            {
                // 使用 long 避免溢出
                if ((long)nums[k] + nums[i] + nums[left] + nums[right] < target)
                    ++left; // 四个数的和小于 target 则左指针右移
                else if ((long)nums[k] + nums[i] + nums[left] + nums[right] > target)
                    --right; // 四个数的和大于 target 则右指针左移。
                else
                {
                    // 将符合条件的组合放入容器
                    result.push_back(vector<int>{nums[k], nums[i], nums[left], nums[right]});
                    
                    // 对 nums[left] 和 nums[right] 去重
                    while (left < right && nums[left] == nums[left + 1])
                        ++left;
                    while (left < right && nums[right] == nums[right - 1])
                        --right;

                    // 有符合条件的组合时，左、右指针同时收缩。
                    ++left;
                    --right;
                }
            }
        }
    }
    return result;
}
