#pragma once

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<unordered_set>
#include<stack>
#include<limits.h>
#include<unordered_map>
#include<queue>
#include<deque>
#include <stdexcept>
#include <cmath>

using std::cout;
using std::endl;
using std::cin;
using std::vector;
using std::sort;

using std::string;
using std::max;
using std::min;
using std::unordered_set;
using std::count;
using std::stack;
using std::unordered_map;
using std::pair;
using std::swap;
using std::deque;
using std::queue;
using std::stoll;
using std::abs;
using std::invalid_argument;
using std::cerr;
using std::exception;

// 二维卷积
vector<vector<float>>convolu2D(
    const vector<vector<float>>&,
    const vector<vector<float>>&,
    int stride,
    int padding);

// 三维卷积
vector<vector<vector<float>>>convolu3D(
    const vector<vector<vector<float>>>& input,
    const vector<vector<vector<float>>>& kernel,
    const vector<int>& stride,
    const vector<int>& padding);

//最近邻插值
vector<vector<float>> nearestNeighbor(
    const vector<vector<float>>& input,
    float scale_x,
    float scale_y);

struct BBox
{
    int x1, y1;       // 左上角坐标(x1,y1)
    int x2, y2;       // 右下角坐标(x2,y2)
    float confidence; // 置信度
    int class_id;     // 类别标识（可选）
};
float calculateIoU(const BBox& box1, const BBox& box2);
vector<BBox> nms(vector<BBox>& boxes, float iou_threshold);
/*
int removeElement(vector<int>& nums, int val);
int removeDuplicates(vector<int>& nums);
int removeDuplicate1(vector<int>& nums);
int duoshu(vector<int>& nums);
int word_len(string s);
int maxProfit(vector<int>& prices);
int maxProfit1(vector<int>& prices);
string longestCommonPrefix(vector<string>& strs);
bool isPalindrome(string str);
bool isPalindrome1(string str);
bool isSubsequence(string small_str, string large_str);

// 定义链表结点
struct ListNode {
    int val; // 数据域
    ListNode* next; // 指针域，存放的是下一个结点的地址
    ListNode() : val(0), next(nullptr) {} // 默认构造
    ListNode(int x) : val(x), next(nullptr) {} // 仅初始化数据域，指针域为空
    ListNode(int x, ListNode* next) : val(x), next(next) {} // 初始化数据域和指针域
};
bool hasCycle(ListNode* head);
bool hasCycle1(ListNode* head);
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2);
ListNode* removeNthFromEnd(ListNode* head, int n);
ListNode* removeNthFromEnd1(ListNode* head, int n);
ListNode* removeLinkElement(ListNode* head, int val);

vector<int>sortedSquare(vector<int>& array);
vector<int>sortedSquare1(vector<int>& array);
int binarySearch(vector<int>& array, int target);
int binarySearch1(vector<int>& array, int target);
vector<int>removeValue(vector<int>& array, int val);
int minSubArrayLen(vector<int>& array, int s);
int minSubArrayLen1(vector<int>& array, int s);
int gapSum();
int gapSum1();

// 哈希表
bool isAnagram(string s, string t);
vector<string> commonChars(vector<string>& A);
vector<int> intersection(vector<int>& nums1, vector<int>& nums2);
int getSum(int n);
bool isHappyNum(int n);
vector<int>twoSum(vector<int>& nums, int target);
int fourNumSum(vector<int>& A, vector<int>& B, vector<int>& C, vector<int>& D);
bool canConstruct(string ransomNote, string magazine);
bool canConstruct1(string ransomNote, string magazine);
vector<vector<int>>threeNumSum(vector<int>& nums);
vector<vector<int>>fourSum(vector<int>& nums, int target);

// 字符串
void reverseString(vector<char>& str);
void reverseStr(string& str, int start, int end);
void reverseStringII(string& str, int k);
void removeExtraSpaces(string& str);

// 双指针
int removeTargetNum(vector<int>& nums, int target);

// 栈和队列
string removeNeiborDuplicates(string str);
long long reverPolanExpression(vector<string>& tokens);

// 二叉树
// 二叉树结点的定义
struct treeNode
{
    int val;
    treeNode* left;
    treeNode* right;
    treeNode() :val(0), left(nullptr), right(nullptr) {}
    treeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};
*/