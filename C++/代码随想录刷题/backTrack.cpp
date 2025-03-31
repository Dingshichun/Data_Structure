#include"head.h"

// 回溯算法
// 回溯法也叫回溯搜索法，是一种搜索的方式。
// 回溯是递归的副产品，只要有递归，就有回溯。
// 回溯法的本质是穷举，并不高效，甚至是低效。最多做一些剪枝操作，使效率高一点点。
// 使用回溯法的原因是有些问题能暴力搜出来就不错了，撑死了再剪枝一下，还没有更高效的解法。

// 回溯法，一般可以解决如下几种问题：
// • 组合问题：N 个数里面按一定规则找出 k 个数的集合
// • 切割问题：一个字符串按一定规则有几种切割方式
// • 子集问题：一个 N 个数的集合里有多少符合条件的子集
// • 排列问题：N 个数按一定规则全排列，有几种排列方式
// • 棋盘问题：N 皇后，解数独等等


// 回溯三部曲：

// (1) 回溯函数模板返回值和参数
// 返回值一般是 void ，但是参数不容易确定，一般是先写逻辑，然后需要什么参数就填什么参数。
// 回溯函数伪代码：void backTracking(参数)

// (2) 回溯函数的终止条件
// 回溯法解决的问题都可以抽象为树形结构（N 叉树）
// 什么时候达到了终止条件，树中就可以看出，一般来说搜到叶子节点了，
// 也就找到了满足条件的一条答案，把这个答案存放起来，并结束本层递归。

// (3) 回溯搜索的遍历过程
// 回溯法一般是在集合中递归搜索，集合的大小构成了树的宽度，递归的深度构成的树的深度。
// 伪代码如下：
/*
for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) 
{
    处理节点;
    backtracking(路径，选择列表); // 递归
    回溯，撤销处理结果
}
*/

// 回溯算法的完整模板框架如下：
/*
void backtracking(参数) 
{
    if (终止条件) 
    {
        存放结果;
        return;
    }

    for (选择：本层集合中元素（树中节点孩子的数量就是集合的大小）) 
    {
        处理节点;
        backtracking(路径，选择列表); // 递归
        回溯，撤销处理结果
    }
}
*/

// 1、组合
// 给定两个整数 n 和 k，返回 1 ... n 中所有可能的 k 个数的组合。

// 示例 : 
// 输入: n = 4, k = 2 
// 输出 : [[2, 4], [3, 4], [2, 3], [1, 2], [1, 3], [1, 4], ]

// 解法 1：使用两个 for 循环，不推荐，因为随着 k 的增大，时间复杂度是指数级增长

// 解法 2 ：回溯
// 用递归来解决嵌套层数的问题。
// 递归来做层叠嵌套（可以理解是开 k 层 for 循环），每一次的递归中嵌套一个 for 循环，
// 那么递归就可以用于解决多层嵌套循环的问题了。
// 图中可以发现 n 相当于树的宽度，k 相当于树的深度。
// 每次搜索到了叶子节点，我们就找到了一个结果。

// 确定三部曲：
// (1) 回溯函数的返回值和参数
// 首先定义两个全局变量，一个存放符合条件的单一结果，一个存放符合条件结果的集合
// 比如：vector<int>path 和 vector<vector<int>> result
// 这两个变量也可以不定义，直接将这两个变量放进递归函数的参数中，但是参数太多影响可读性。
// 除了 n 、k 两个参数外，还需要一个变量 startIndex 记录集合从哪里开始遍历,防止出现重复组合

// (2) 回溯终止条件
// path 这个数组的大小如果达到 k，说明我们找到了一个子集大小为 k 的组合了，
// path 存的就是根节点到叶子节点的路径。
// 此时用 result 二维数组，把 path 保存起来，并终止本层递归。
// 伪代码如下：
/*
if (path.size() == k) {
    result.push_back(path);
    return;
}
*/

// 回溯搜索的遍历过程
// 回溯法的搜索过程就是一个树型结构的遍历过程，for 循环用来横向遍历，递归的过程是纵向遍历。
// for 循环每次从 startIndex 开始遍历，然后用 path 保存取到的节点 i 。
// 代码如下：
/*
for (int i = startIndex; i <= n; i++) { // 控制树的横向遍历
    path.push_back(i); // 处理节点
    backtracking(n, k, i + 1); // 递归：控制树的纵向遍历，注意下一层搜索要从 i+1 开始
    path.pop_back(); // 回溯，撤销处理的节点
}
*/

class solution1
{
private:
    vector<int>path; // 保存一次纵向遍历的结果
    vector<vector<int>>result; // 保存所有 path

    // 定义回溯函数，注意传入参数 startIndex
    void backTracking(int n, int k, int startIndex) 
    {
        // 回溯终止条件
        if (path.size() == k)
        {
            result.push_back(path);
            return;
        }

        // 回溯搜索的遍历过程，for 实现横向遍历，回溯则实现纵向遍历，最终搜索到所有组合
        // 这里进行了剪枝优化，避免不必要的遍历，比如 n=4，k=4 ，那么就只有一种取法，
        // 这种取法在第一次 for 循环时就能够确定，就不用再遍历了。
        for (int i = startIndex; i <= n - (k - path.size()) + 1; ++i)
        {
            path.push_back(i);
            backTracking(n, k, i+1);
            path.pop_back(); // 这里有疑问？
        }
    }
public:
    vector<vector<int>>combine(int n, int k)
    {
        result.clear();
        path.clear();
        backTracking(n, k, 1); // 
        return result;
    }
};

// 2、组合总和III
// 找出所有相加之和为 n 的 k 个数的组合。组合中只允许含有 1 - 9 的正整数，
// 并且每种组合中不存在重复的数字。

// 说明：
// • 所有数字都是正整数。
// • 解集不能包含重复的组合。
// 示例 1: 输入: k = 3, n = 7 输出 : [[1, 2, 4]]
// 示例 2 : 输入 : k = 3, n = 9 输出 : [[1, 2, 6], [1, 3, 5], [2, 3, 4]]

class solution2
{
private:
    vector<int>path; // 存储一条路径的结果
    vector<vector<int>>result; // 存储所有满足条件组合的结果
    void backTracking(int targetNum, int k, int sum, int startIndex)
    {
        if (sum > targetNum)return; // 剪枝
        // 回溯终止条件。路径的长度达到 k 则终止，如果和为 n ，则将 path 加入 result
        if (path.size() == k)
        {
            if (sum == targetNum)result.push_back(path);
            return;
        }

        // 回溯搜索的遍历过程
        for (int i = startIndex; i <= 9 - (k - path.size()) + 1; ++i) // 剪枝
        {
            sum += i;
            path.push_back(i);
            backTracking(targetNum, k, sum, i + 1);
            sum -= i; // 注意撤销 sum
            path.pop_back(); // 撤销 path
        }
    }
public:
    vector<vector<int>>com(int targetNum, int k)
    {
        path.clear();
        result.clear();
        backTracking(targetNum, k, 0, 1);
        return result;
    }
};

// 3、给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。
// 给出数字到字母的映射与电话按键相同。注意 1 不对应任何字母。

// 示例:
// 输入："23"
// 输出：["ad", "ae", "af", "bd", "be", "bf", "cd", "ce", "cf"]

class solution3
{
private:
    const string letterMap[10] = {
        "", // 0
        "", // 1
        "abc", // 2
        "def", // 3
        "ghi", // 4
        "jkl", // 5
        "mno", // 6
        "pqrs", // 7
        "tuv", // 8
        "wxyz", // 9
    };
public:
    vector<string>result; // 存储所有字符串
    string s; // 存储每一条路径上的字符

    // 回溯函数，index 记录遍历到所给数字字符串的哪一个位置
    void backTracking(const string& digits, int index)
    {
        // 终止条件，index 到达所给数字字符串的最后一个位置时
        if (index == digits.size())
        {
            result.push_back(s);
            return;
        }
        int digit = digits[index] - '0'; // 字符串中的字符转换为整型数字
        string letters = letterMap[digit]; // letters 是数字对应的字母
        
        // 回溯
        for (int i = 0; i < letters.size(); ++i)
        {
            s.push_back(letters[i]);
            backTracking(digits, index + 1);
            s.pop_back(); // 撤销操作
        }
    }

    vector<string>letterCombinations(string digits)
    {
        s.clear();
        result.clear();
        if (digits.size() == 0)return result;
        backTracking(digits, 0);
        return result;
    }
};

// 4、
/*
给定一个无重复元素的数组 candidates 和一个目标数 target ，
找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的数字可以无限制重复被选取。

说明：
所给数组中没有重复元素。
所有数字（包括 target）都是正整数。
解集不能包含重复的组合。

示例 1：
输入：candidates = [2, 3, 6, 7], target = 7,
所求解集为： [[7], [2, 2, 3]]

示例 2：
输入：candidates = [2, 3, 5], target = 8,
所求解集为： [[2, 2, 2, 2], [2, 3, 3], [3, 5]]
*/

class solution4
{
private:
    vector<int>path; // 存储一条路径上的数
    vector<vector<int>>result; // 存储全部的结果

    // 回溯函数， sum 记录求和结果，startIndex 记录开始回溯的位置
    void backTracking(vector<int>& candidates, int target,int sum, int startIndex)
    {
        // 终止条件
        if (sum > target)return;
        if (sum == target)
        {
            result.push_back(path);
            return;
        }

        // 回溯
        for (int i = startIndex; i < candidates.size(); ++i)
        {
            sum += candidates[i]; // 记录每条路径逐渐变长时的和
            path.push_back(candidates[i]); // 记录遍历到的数
            backTracking(candidates, target, sum, i); // 主要区别在这里，选过的还可以选
            
            // 撤销处理。注意，sum 也要进行撤销处理
            sum -= candidates[i];
            path.pop_back();
        }
    }
public:
    vector<vector<int>>numCombination(vector<int>& candidates, int target)
    {
        path.clear();
        result.clear();
        backTracking(candidates, target, 0, 0);
        return result;
    }
};

// 5、
/*给定一个数组 candidates 和一个目标数 target ，找出 candidates 中所有可以使数字和为 target 的组合。
candidates 中的每个数字在每个组合中只能使用一次。
说明： 所有数字（包括目标数）都是正整数。解集不能包含重复的组合。*/

// 解题思路：
// 最重要的点是去重，和三数之和、四数之和的去重方法一样，首先进行排序，
// 然后在选择的时候去掉重复选择的数
class solution5
{
private:
    vector<int>path;
    vector<vector<int>>result;
    void backTracking(vector<int>& candidates, int target, int sum, int startIndex)
    {
        if (sum > target)return; // 剪枝，可以省略，因为下面 sum + candidates[i] <= target 是一个意思
        if (sum == target)
        {
            result.push_back(path);
            return;
        }

        for (int i = startIndex; i < candidates.size() && sum + candidates[i] <= target; i++)
        {
            // 这里进行去重操作
            if (i > startIndex && candidates[i] == candidates[i - 1])
                continue;
            sum += candidates[i];
            path.push_back(candidates[i]);
            backTracking(candidates, target, sum, i + 1);
            sum -= candidates[i]; // 注意撤销操作的对象包括 sum 和 path
            path.pop_back();
        }
    }
public:
    vector<vector<int>>numCombination(vector<int>& candidates, int target)
    {
        path.clear();
        result.clear();
        sort(candidates.begin(), candidates.end()); // 排序，便于去重
        backTracking(candidates, target, 0, 0);
        return result;
    }
};

// 6、
// 给定一个字符串 s，将 s 分割成一些子串，使每个子串都是回文串。
// 返回 s 所有可能的分割方案。
// 示例 : 输入: "aab" 输出 : [["aa", "b"], ["a", "a", "b"]]

// 解题思路：
// 这里的分割和前面的组合问题是类似的，只是多了判断回文串的步骤
class solution6
{
private:
    vector<string> path; // 存储单条路径上的结果
    vector<vector<string>>result; // 存储所有满足条件的结果

    // 回溯函数，参数为传入的字符串 str ，开始分割的位置 startIndex
    void backTracking(const string& str, int startIndex)
    {
        // 终止条件，切割线 startIndex 大于等于字符串的长度
        if (startIndex >= str.size())
        {
            result.push_back(path);
            return;
        }

        // 回溯
        for (int i = startIndex; i < str.size(); ++i)
        {
            // 如果是回文串。即字符串 str 的 startIndex 到 i 这部分字符是回文串
            if (isPalindrome(str, startIndex, i))
            {
                // 如果分割出的是回文串，将其提取出来添加到 path 中
                string s = str.substr(startIndex, i - startIndex + 1);
                path.push_back(s);
            }
            else continue; // 如果不是回文串，则开始下一轮循环
            backTracking(str, i + 1); // 回溯操作
            path.pop_back(); // 撤销操作
        }
    }

    // 判断字符串是不是回文串
    bool isPalindrome(const string str,int start,int end)
    {
        
        for (int i = start, j = end; i < j; ++i, --j)
        {
            if (str[i] != str[j])return false;
        }
        return true;
    }
public:
    vector<vector<string>>hui(string str)
    {
        path.clear();
        result.clear();
        backTracking(str, 0);
        return result;
    }
};


// 7、
//给定一个只包含数字的字符串，复原它并返回所有可能的 IP 地址格式。
//有效的 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，且不能含有前导 0），整数之间用 '.' 分隔。
//例如："0.1.2.201" 和 "192.168.1.1" 是 有效的 IP 地址，
//但是 "0.011.255.245"、"192.168.1.312" 和 "192.168@1.1" 是 无效的 IP 地址。

//示例 1：
//输入：s = "25525511135"
//输出：["255.255.11.135", "255.255.111.35"]
//
//示例 2：
//输入：s = "0000"
//输出：["0.0.0.0"]
//
//示例 3：
//输入：s = "1111"
//输出：["1.1.1.1"]
//
//示例 4：
//输入：s = "010010"
//输出：["0.10.0.10", "0.100.1.0"]

class solution7
{
private:
    vector<string>result; // 记录结果
    // startIndex: 搜索的起始位置，pointNum:添加句点的数量
    void backTracking(string& str, int startIndex, int pointNum)
    {
        // 添加的点 pointNum 为 3 时，分隔结束
        if (pointNum == 3)
        {
            // 判断第四段子字符串是否合法，如果合法就放进 result 中
            if (isValid(str, startIndex, str.size() - 1))         
                result.push_back(str);
            return;
        }

        for (int i = startIndex; i < str.size(); ++i)
        {
            // 判断 [startIndex,i] 这个区间的子串是否合法
            if (isValid(str, startIndex, i))
            {
                str.insert(str.begin() + i + 1, '.'); // 在 i 的后面插入一个 '.'
                ++pointNum;// 
                backTracking(str, i + 2, pointNum); // 插入逗点之后下一个子串的起始位置为i+2
                
                --pointNum; // 回溯
                str.erase(str.begin() + i + 1); // 回溯删掉 '.'
            }
            else continue; // 不合法，直接结束本层循环，开始下一层循环
        }
    }

    bool isValid(const string& s, int start, int end) {
        if (start > end) return false; // 开始和结尾的顺序错误，不合法
        
        if (s[start] == '0' && start != end) { // 0 开头的多位数字不合法，只是 0 则合法
            return false;
        }
        int num = 0;
        for (int i = start; i <= end; i++) {
            if (s[i] > '9' || s[i] < '0') { // 遇到非数字字符不合法
                return false;
            }
            num = num * 10 + (s[i] - '0');
            if (num > 255) { // 如果大于255了不合法
                return false;
            }
        }
        return true;
    }

public:
    vector<string>getIpAddress(string& str)
    {
        result.clear();
        // 相当于剪枝，符合条件的字符串长度范围是 4~12
        if (str.size() < 4 || str.size() > 12)return result;
        backTracking(str, 0, 0);
        return result;
    }
};


// 8、子集
//给定一组不含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
//说明：解集不能包含重复的子集。
//
//示例 : 
//输入: nums = [1, 2, 3] 
//输出 : [[3], [1], [2], [1, 2, 3], [1, 3], [2, 3], [1, 2], []]

// 解题思路：很多回溯的题都是求树的叶子结点，而子集问题则是求所有结点
// 为了避免重复，也要使用一个参数 startIndex 记录开始遍历的位置，依次增加。

// 疑问：空集是什么时候加的？
// 应该是 path 最开始的时候是空的，所以下面要先收集子集，再写终止条件，不然就漏掉空集。
class solution8
{
private:
    vector<int>path; // 存放一个子集
    vector<vector<int>>result; // 存放所有子集
    void backTracking(vector<int>& nums, int startIndex)
    {
        // 收集子集，要放在终止添加的上面，否则会漏掉空集
        result.push_back(path);
        if (startIndex >= nums.size())return; // 终止条件可以不写，下面的循环会自己退出

        for (int i = startIndex; i < nums.size(); ++i)
        {
            path.push_back(nums[i]);
            backTracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>>subSets(vector<int>& nums)
    {
        path.clear();
        result.clear();
        backTracking(nums, 0);
        return result;
    }
};

// 9、
// 给定一个可能包含重复元素的整数数组 nums，返回该数组所有可能的子集（幂集）。
// 说明：解集不能包含重复的子集。

//示例 :
//输入: [1, 2, 2]
//输出 : [[2], [1], [1, 2, 2], [2, 2], [1, 2], []]

// 解题思路：
// 和求子集类似，只是多了去重。去重操作一般排序后方便去重。

class solution9
{
private:
    vector<int>path;
    vector<vector<int>>result;
    void backTracking(vector<int>& nums, int startIndex)
    {
        result.push_back(path);
        if (startIndex >= nums.size())return;

        for (int i = startIndex; i < nums.size(); ++i)
        {
            if (i > startIndex && nums[i] == nums[i - 1])
                continue;
            path.push_back(nums[i]);
            backTracking(nums, i + 1);
            path.pop_back();
        }
    }
public:
    vector<vector<int>>subSets(vector<int>& nums)
    {
        path.clear();
        result.clear();
        sort(nums.begin(), nums.end());
        backTracking(nums, 0);
        return result;
    }
};


// 10、
//给定一个整型数组, 你的任务是找到所有该数组的递增子序列，递增子序列的长度至少是2。

//示例 :
//输入: [4, 6, 7, 7]
//输出 : [[4, 6], [4, 7], [4, 6, 7], [4, 6, 7, 7], [6, 7], [6, 7, 7], [7, 7], [4, 7, 7]]

//说明 :
//给定数组的长度不会超过15。
//数组中的整数范围是[-100, 100]。
//给定数组中可能包含重复数字，相等的数字应该被视为递增的一种情况。

// 注意，
// 原数组是无序的，只是示例是有序的，具有误导性。
// 本题求自增子序列，是不能对原数组进行排序的，因为排完序的数组都是自增子序列了。
// 所以不能使用之前的去重逻辑

class solution10
{
private:
    vector<int>path; // 记录一条路径的结果
    vector<vector<int>>result; // 记录所有满足条件的结果

    void backTracking(vector<int>& nums, int startIndex)
    {
        // 终止条件，只要 path 的长度大于 1 就可以终止
        if (path.size() > 1)result.push_back(path);
        // 注意这里不要加 return，要取树上的节点

        unordered_set<int>uset; // 无序容器，用于去重
        for (int i = startIndex; i < nums.size(); ++i)
        {
            // 不符合条件的直接退出本次循环。包括元素不递增和元素在同一层使用过了
            if ((!path.empty() && nums[i] < path.back()) || uset.find(nums[i]) != uset.end())
                continue;
            uset.insert(nums[i]); // 记录元素在本层使用过了，本层后面不能再使用
            path.push_back(nums[i]);
            backTracking(nums, i + 1); // 回溯

            // 看到递归函数上面的uset.insert(nums[i]); ，
            // 下面却没有对应的 pop 之类的操作，应该很不习惯吧
            // 这也是需要注意的点，unordered_set<int> uset; 是记录本层元素是否重复使用，
            // 新的一层 uset 都会重新定义（清空），所以要知道 uset 只负责本层！
            path.pop_back(); // 撤销处理
        }
    }
public:
    vector<vector<int>> findSubsequences(vector<int>& nums) {
        result.clear();
        path.clear();
        backTracking(nums, 0);
        return result;
    }
};


// 11、
// 给定一个 没有重复 数字的序列，返回其所有可能的全排列。

// 示例 :
// 输入: [1, 2, 3]
// 输出 : [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]

// 解题思路：
// 首先排列是有序的，也就是说[1, 2] 和[2, 1] 是两个集合，这和之前分析的子集以及组合所不同的地方。
// 可以看出元素 1 在[1, 2]中已经使用过了，但是在[2, 1]中还要在使用一次1，
// 所以处理排列问题就不用使用 startIndex 了。
// 但排列问题需要一个 used 数组，标记已经选择的元素。

// 叶子节点就是结果。那么什么时候，算是到达叶子节点呢？
// 当收集元素的数组 path 的大小达到和 nums 数组一样大的时候，
// 说明找到了一个全排列，也表示到达了叶子节点。
// used 数组，其实就是记录此时 path 里都有哪些元素使用了，一个排列里一个元素只能使用一次。

class solution11
{
private:
    vector<int>path;
    vector<vector<int>>result;
    void backTracking(vector<int>& nums, vector<bool>& used)
    {
        // 此时说明找到了全排列组合中的一组
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            // path 里已经收录的元素，直接跳过
            if (used[i])
                continue;
            used[i] = true; // 表示该元素已经收录
            path.push_back(nums[i]); 
            backTracking(nums, used); // 回溯
            
            // 撤销处理
            used[i] = false; // used[i] 撤销为 false
            path.pop_back(); // 弹出加入到 path 中的元素
        }
    }
public:
    vector<vector<int>>queue(vector<int>nums)
    {
        path.clear();
        result.clear();
        // used 容器大小为 nums.size()，全部初始化为 false
        vector<bool>used(nums.size(), false); 
        backTracking(nums, used);
        return result;
    }
};


// 12、
//给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。

//示例 1：
//输入：nums = [1, 1, 2]
//输出： [[1, 1, 2], [1, 2, 1], [2, 1, 1]]

//示例 2：
//输入：nums = [1, 2, 3]
//输出： [[1, 2, 3], [1, 3, 2], [2, 1, 3], [2, 3, 1], [3, 1, 2], [3, 2, 1]]

// 解题思路：
// 不重复的全排列，涉及到去重。
// 去重一定要对元素进行排序，这样才方便通过相邻的节点来判断是否重复使用了。
// 对同一树层，前一位（也就是nums[i-1]）如果使用过，那么就进行去重。

class solution12
{
private:
    vector<int>path;
    vector<vector<int>>result;
    void backTracking(vector<int>& nums, vector<bool>&used)
    {
        if (path.size() == nums.size())
        {
            result.push_back(path);
            return;
        }

        for (int i = 0; i < nums.size(); ++i)
        {
            // used[i - 1] == true，说明同一树枝 nums[i - 1] 使用过
            // used[i - 1] == false，说明同一树层 nums[i - 1] 使用过
            // 如果同一树层 nums[i - 1] 使用过则直接跳过
            if (i > 0 && nums[i] == nums[i - 1] && used[i - 1] == false)
                continue;

            if (used[i] == false)
            {
                used[i] = true;
                path.push_back(nums[i]);
                backTracking(nums, used);
                path.pop_back();
                used[i] = false;
            }
        }
    }
public:
    vector<vector<int>>permuteUnique(vector<int>& nums)
    {
        path.clear();
        result.clear();
        vector<bool>used(nums.size(), false);
        sort(nums.begin(), nums.end());
        backTracking(nums, used);
        return result;
    }
};


// 13、N 皇后
// n 皇后问题 研究的是如何将 n 个皇后放置在 n×n 的棋盘上，并且使皇后彼此之间不能相互攻击。
// 给你一个整数 n ，返回所有不同的 n 皇后问题 的解决方案。
// 每一种解法包含一个不同的 n 皇后问题 的棋子放置方案，
// 该方案中 'Q' 和 '.' 分别代表了皇后和空位。

// 要求:皇后不能同行、不能同列、不能同斜线

// 解题思路：
// 用回溯解决多了组合、切割、子集、排列问题之后，遇到这种二维矩阵还会有点不知所措。
// 可以将搜索过程抽象为一棵树，二维矩阵的每一行就是树的每一层，
// 然后在每一行中再依次选出每一列，判断位置是否满足皇后放置的要求。
// 用皇后们的约束条件，来回溯搜索这棵树，只要搜索到了树的叶子节点，说明就找到了皇后们的合理位置了。

// (1) 确定递归函数的参数
// 依然定义全局变量二维数组 result 来记录最终结果。
// 参数 n 是棋盘的大小，然后用 row 来记录当前遍历到棋盘的第几层了。

// (2)确定递归终止条件
// 当递归到棋盘最底层，也就是叶子结点的位置时，就可以收集结果并返回

// (3)单层搜索的逻辑
// 递归深度就是 row 控制棋盘的行，每一层里 for 循环的 col 控制棋盘的列，
// 一行一列，确定了放置皇后的位置。
// 每次都是要从新的一行的起始位置开始搜，所以都是从 0 开始。

class solution13
{
private:
    vector<vector<string>>result;
    void backTracking(int n, int row, vector<string>& chessboard)
    {
        if (row = n)
        {
            result.push_back(chessboard);
            return;
        }
        for (int col = 0; col < n; ++col)
        {
            if (isValid(row, col, chessboard, n))
            {
                chessboard[row][col] = 'Q';
                backTracking(n, row + 1, chessboard);
                chessboard[row][col] = '.';
            }
        }
    }

    bool isValid(int row, int col, vector<string>& chessboard, int n)
    {
        // 这里只需要判断列和斜线方向是否合法，不用判断行
        // 因为是按行遍历，每行只要找到一个正确的位置就会对下一行进行回溯，无需判断。
        // 检查列
        for (int i = 0; i < row; i++) 
        { // 这是一个剪枝
            if (chessboard[i][col] == 'Q') 
                return false;
        }

        // 检查 135 度角是否有皇后
        for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) 
        {
            if (chessboard[i][j] == 'Q') 
                return false;
        }
        // 检查 45 度角是否有皇后
        for (int i = row - 1, j = col + 1; i >= 0 && j < n; i--, j++) 
        {
            if (chessboard[i][j] == 'Q') 
                return false;
        }
        return true;
    }
public:
    vector<vector<string>> solveNQueens(int n) 
    {
        result.clear();
        vector<string> chessboard(n, string(n, '.'));
        backTracking(n, 0, chessboard);
        return result;
    }
};


// 14、解数独。没理解清楚
// 编写一个程序，通过填充空格来解决数独问题。

// 一个数独的解法需遵循如下规则： 
// 数字 1 - 9 在每一行只能出现一次。 数字 1 - 9 在每一列只能出现一次。 
// 数字 1 - 9 在每一个以粗实线分隔的 3x3 宫内只能出现一次。 空白格用 '.' 表示。

class solution14
{
private:
    // 这里回溯函数的返回值是 bool 类型。
    // 因为解数独找到一个符合的条件（就在树的叶子节点上）立刻就返回，
    // 相当于找从根节点到叶子节点一条唯一路径，所以需要使用 bool 返回值。
    bool backTrack(vector<vector<char>>& board)
    {
        for (int i = 0; i < board.size(); ++i) // 遍历行
        {
            for (int j = 0; j < board[0].size(); ++j) // 遍历列
            {
                if (board[i][j] == '.') // 遇到空的位置就尝试填数进去
                {
                    for (char k = '1'; k < '9'; ++k) // 1 到 9 依次尝试填入
                    {
                        if(isValid(i,j,k,board)) // k 满足条件
                            board[i][j]=k;
                        if (backTrack(board))return true; // 找到一组合适的就立刻返回
                        board[i][j] = '.'; // 回溯，撤销 k
                    }
                    return false; // 9 个数都试完了，都不满足条件，就返回 false
                }
            }
        }
        return true; // 遍历完之后没有返回 false，说明找到了合适的棋盘位置
    }

    // 判断 val 填在 board[row][col] 的位置是否合适
    bool isValid(int row, int col, int val, vector<vector<char>>board)
    {
        for (int i = 0; i < 9; ++i) // 判断行是否有重复
        {
            if (board[row][i] == val)return false;         
        }
        for (int i = 0; i < 9; ++i) //判断列是否有重复
        {
            if (board[i][col] == val)return false;
        }

        // 判断在划分的 9 个小方格里面是否合适
        int startRow = (row / 3) * 3;
        int startCol = (col / 3) * 3;
        for (int i = startRow; i < startRow + 3; ++i)
        {
            for (int j = startCol; j < startCol + 3; ++j)
            {
                if (board[i][j] == val)return false;
            }
        }
        return true;
    }
public:
    void solveShuDu(vector<vector<char>>& board)
    {
        backTrack(board);
    }
};