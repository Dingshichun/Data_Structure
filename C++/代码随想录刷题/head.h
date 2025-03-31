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
#include<execution>

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
using std::to_string;

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

// ����������
struct ListNode {
    int val; // ������
    ListNode* next; // ָ���򣬴�ŵ�����һ�����ĵ�ַ
    ListNode() : val(0), next(nullptr) {} // Ĭ�Ϲ���
    ListNode(int x) : val(x), next(nullptr) {} // ����ʼ��������ָ����Ϊ��
    ListNode(int x, ListNode* next) : val(x), next(next) {} // ��ʼ���������ָ����
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

// ��ϣ��
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

// �ַ���
void reverseString(vector<char>& str);
void reverseStr(string& str, int start, int end);
void reverseStringII(string& str, int k);
void removeExtraSpaces(string& str);

// ˫ָ��
int removeTargetNum(vector<int>& nums, int target);

// ջ�Ͷ���
string removeNeiborDuplicates(string str);
long long reverPolanExpression(vector<string>& tokens);

// ������
// ���������Ķ���
struct treeNode
{
    int val;
    treeNode* left;
    treeNode* right;
    treeNode() :val(0), left(nullptr), right(nullptr) {}
    treeNode(int x) :val(x), left(nullptr), right(nullptr) {}
};

// ����
void selectionSort(int arr[],int n);
void selectionSort2(vector<int>&);

