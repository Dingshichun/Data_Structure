#include"head.h"

// 1、移除
// 使用双指针原地修改
int removeElement(vector<int>& nums, int val) 
{
    int n = nums.size();
    int left = 0;
    for (int right = 0; right < n; ++right) {
        if (nums[right] != val) {
            nums[left] = nums[right];
            ++left;
        }
    }
    return left;
}


// 2、使非严格递增数组中的重复元素只保留一个
int removeDuplicates(vector<int>& nums)
{
    int n = nums.size();
    if (n == 0)
        return 0;
    int slow = 1;
    int fast = 1;
    while (fast < n)
    {
        if (nums[fast] != nums[fast - 1])
        {
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}

// 3、使有序数组中出现两次以上的元素只出现两次，需要原地删除元素。注意数组有序
//一样的题目是：使有序数组中出现 n 次以上的元素只出现 n 次，需要原地删除元素。注意数组有序
int removeDuplicate1(vector<int>& nums)
{
    int n = nums.size();
    if (n <= 2)return n;
    int slow = 2, fast = 2;
    while (fast < n)
    {
        if (nums[fast - 2] != nums[fast])
        {
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}


// 4、假设一个整数数组中总是存在多数元素，请找出多数元素，
// 解题思想是：存在多数元素，那么将数组排序后，位于 n/2 位置的就是多数元素。
int duoshu(vector<int>& nums)
{
    int n = nums.size();
    sort(nums.begin(),nums.end());
    return nums[n / 2];
}

// 5、最后一个单词的长度，字符串中只有单词和空格
// 思想是反向遍历，先排除最后的空格，再得到最后一个单词的长度。
int word_len(string s)
{
    int index = s.size() - 1;
    while (s[index] == ' ')
    {
        --index;
    }

    int word_count = 0;
    while (index>=0 && s[index] != ' ')
    {
        ++word_count;
        --index;
    }
    return word_count;
}

// 6、买卖股票的最佳时机。给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
// 只能选择某天买入，并在未来的某天卖出，求能获得的最大利润。
// 解决思想是在最低谷买入，在最高处抛出
int maxProfit(vector<int>& prices)
{
    int min_price = 1E9; // 初始最低价
    int max_profit = 0; // 初始最大利润
    for (int price : prices)
    {
        max_profit = max((price - min_price), max_profit); // 更新最大利润
        min_price = min(price, min_price); // 更新最低价
    }
    return max_profit;
}

// 买卖股票变形题。
// 在每一天，你可以决定是否购买和/或出售股票。  
// 你在任何时候 最多 只能持有 一股 股票。你也可以先购买，然后在 同一天 出售。
// 也就是说可以不断地进行买卖，直到最后遍历完数组。

// 解决思想是收集所有上升阶段，即可获得利润的阶段，那么最后肯定就可实现利益最大化。
int maxProfit1(vector<int>& prices)
{
    int n = prices.size();
    if (n <= 1)return 0;
    int max_profit = 0;
    for (int i = 1; i < n; ++i)
    {
        if (prices[i] > prices[i - 1])
            max_profit += (prices[i] - prices[i - 1]);
    }
    return max_profit;
}


// 7、最长公共前缀。采用纵向比较
string longestCommonPrefix(vector<string>& strs)
{
    if (!strs.size())return "";
    int length = strs[0].size();
    int count = strs.size();

    for (int i = 0; i < length; ++i)
    {
        char c = strs[0][i];
        for (int j = 1; j < count; ++j)
        {
            if (i == strs[j].size() || strs[j][i] != c)
                return strs[0].substr(0,i);
        }
    }
    return strs[0];
}

// 8、验证回文串。
// 方法 1 ：解决思想是仅保留字符串中的字母，将字母字符串分为对称的两部分，比较对称位置是否相等。
bool isPalindrome(string str)
{
    string alpha;
    for (char ch : str)
    {
        if (isalpha(ch))
            alpha += tolower(ch); // 注意转换为一样的格式进行比较，比如都是小写或大写。
    }
    int n = alpha.size();
    int left = 0, right = n - 1;
    while (left < right)
    {
        if (alpha[left] != alpha[right])
            return false;
        ++left;
        --right;
    }
    return true;
}
// 方法 2 ：直接在原字符串上比较，
// 分为左、右两半，左半部分从左往右遇到的第一个字母，和右半部分从右往左遇到的第一个字母比较，
// 然后比较第二个、第三个，直到比完左、右两部分。
bool isPalindrome1(string str)
{
    int n = str.size();
    int left = 0, right = n - 1;
    while (left < right)
    {
        while (left < right && !isalpha(str[left])) // 注意循环终止条件。
            ++left;
        while (left < right && !isalpha(str[right]))
            --right;
        if (tolower(str[left]) != tolower(str[right])) // 注意要转换为同样的大写或小写进行比较
            return false;
        ++left;
        --right;
    }
    return true;
}

// 9、判断是不是子序列
//字符串的一个子序列是原始字符串删除一些（也可以不删除）字符而不改变剩余字符相对位置形成的新字符串。
//（例如，"ace"是"abcde"的一个子序列，而"aec"不是）。

// 方法 1：双指针。
// 初始化两个指针 i 和 j，分别指向 s 和 t 的初始位置。
// 每次贪心地匹配，匹配成功则 i 和 j 同时右移，匹配 s 的下一个位置，匹配失败则 j 右移，i 不变，尝试用 t 的下一个字符匹配 s。
//最终如果 i 移动到 s 的末尾，就说明 s 是 t 的子序列。
bool isSubsequence(string small_str, string large_str) 
{
    int s_len = small_str.size(), l_len = large_str.size();
    int i = 0, j = 0;
    while (i < s_len && j < l_len)
    {
        if (small_str[i] == large_str[j])
            ++i;
        ++j;
    }
    return i == s_len;
}

// 10、判断链表中是否有环。
// 方法 1：哈希表。依次遍历链表中的结点，存入哈希表，如果后面遍历的结点在哈希表中出现，则有环
// 定义链表结点结构体 ListNode
//struct ListNode {
//    int val; // 数据域
//    ListNode* next; // 指针域，存放的是下一个结点的地址
//    ListNode() : val(0), next(nullptr) {} // 默认构造
//    ListNode(int x) : val(x), next(nullptr) {} // 仅初始化数据域，指针域为空
//    ListNode(int x, ListNode* next) : val(x), next(next) {} // 初始化数据域和指针域
//};
bool hasCycle(ListNode* head)
{
    // 判断是否有环的问题就不用设置虚拟头结点，因为不用返回结点，
    // 直接从原链表的第一个数据结点开始即可
    unordered_set<ListNode*>seen; // 该集合保存遍历过的结点
    while (head != nullptr) // 可直接写为 while(head)
    {
        if (seen.count(head)) // 如果结点在集合 seen 中，则有环
            return true;
        seen.insert(head);
        head = head->next; // 更新头结点
    }
    return false;
}

// 方法 2：快慢指针。快指针追上慢指针则说明有环。
bool hasCycle1(ListNode* head)
{
    // 这里要分为链表有、无头结点进行讨论，官方解答应该是没有考虑头结点。
    // 没有头结点，头指针直接指向第一个存放元素的结点。那么下面的 if 判断条件就表示链表为空或只有一个存放元素的结点
    // 空链表和只有一个结点的链表都不会有环，起码两个结点才会有环。
    if (head == nullptr || head->next == nullptr)
        return false;
    // 定义快、慢指针，两指针相邻
    ListNode* slow = head; // 慢指针指向第一个存放元素的结点
    ListNode* fast = head->next; // 快指针指向第二个
    while (fast != slow) // 如果快指针能追上慢指针则有环
    {
        // 如果没有环，那么快指针会先到达最后一个结点或成为 nullptr
        // 由于快指针每次走两步，所以快指针走最后一步时可能直接到达最后一个结点的位置或成为 nullptr
        if (fast == nullptr || fast->next == nullptr)
            return false;
        slow = slow->next; // 慢指针移动一步
        fast = fast->next->next; // 快指针移动两步
    }
    return true;
}

// 11、合并两个有序链表
ListNode* mergeTwoLists(ListNode* list1, ListNode* list2)
{
    ListNode* aux_head = new ListNode(-1);//创建新结点用于保存合并的链表
    ListNode* prev = aux_head;//指向新结点的一个指针
    while (list1 != nullptr && list2 != nullptr) // 依次比较两个链表中的值
    {
        // 哪个链表结点中的值小就添加到新结点后面
        if (list1->val < list2->val) 
        {
            prev->next = list1;// 链表 1 的结点中的值小，添加到新结点后
            list1 = list1->next; // 链表 1 的下一个结点
        }
        else
        {
            prev->next = list2;
            list2 = list2->next; // 链表 2 的下一个结点
        }
        prev = prev->next; // 更新合并链表的最后一个结点
    }
    // 如果遍历到最后哪个链表先被遍历完，说明该链表中的值较小，先到达 nullptr，
    // 那么只需将没有遍历完的链表的剩余结点添加到新链表后面即可。
    // 这里的写法意思是如果链表 1 先遍历完，那么将链表 2 剩余结点添加到新链表末尾，否则就将链表 1 剩余结点添加到新链表末尾。
    // 也可以写成：prev->next = (list2 == nullptr) ? list1 : list2; 作用一样
    prev->next = (list1 == nullptr) ? list2 : list1;
    ListNode* ans = aux_head->next; // 获取合并后的第一个结点
    delete aux_head; // 释放辅助结点
    aux_head = nullptr; // 置空，避免野指针
    return ans;
}

// 12、给你一个链表，删除链表的倒数第 n 个结点，并且返回删除结点后链表的头结点。
// 方法 1：使用栈。遍历的同时入栈，然后出栈，弹出的第 n 个元素就是要删除的结点。
// 此时栈顶的元素就是要删除的结点的前继结点的指针，将其指向倒数第 n-1 个元素即可删除第 n 个结点
ListNode* removeNthFromEnd(ListNode* head, int n) 
{
    // 创建结点 dummy ，其后继结点是所传入链表的头结点，
    ListNode* aux_head = new ListNode(0, head);  
    stack<ListNode*> stk; // 存放结点指针的栈 stk
    ListNode* cur = aux_head; // cur 和 dummy 一样
    while (cur) {
        stk.push(cur);// 遍历链表，并将每个结点的指针入栈
        cur = cur->next;
    }
    for (int i = 0; i < n; ++i) 
    {
        stk.pop(); // 弹出最后入栈的 n 个指针，那么栈顶就是倒数第 n+1 个结点的指针
    }
    ListNode* prev = stk.top(); // prev 是倒数第 n 个结点的前继结点的指针，即倒数第 n+1 个结点的指针
    ListNode* temp = prev->next; // 获取要删除结点的地址
    prev->next = prev->next->next; // 删除倒数第 n 个结点，只需要将倒数第 n+1 个结点指向倒数第 n-1 个结点
    delete temp; // 释放要删除结点的内存空间
    temp = nullptr; // 置空，避免成为野指针

    ListNode* ans = aux_head->next; // 要返回的是原链表的头结点，即新建结点 dummy 的下一个结点，要取得该结点的指针
    delete aux_head; // 删除新建的辅助结点。因为该结点要删除，所以前面就要先取出它的下一个结点。
    aux_head = nullptr; // 置空，避免野指针
    return ans; // 返回删除链表元素后的头结点。因为有可能删除原来的头结点，所以不能直接返回原链表的头结点。
}

// 方法 2：双指针。指针 front 和 behind
// front 指针比 behind 指针超前 n 个结点，当 front 遍历到链表的末尾时，
// behind 恰好处于倒数第 n 个结点。
// 
// 但是由于删除倒数第 n 个结点需要找到它的前驱结点，即倒数第 n+1 个结点，
// 所以直接设置 front 比 behind 超前 n+1 个结点，那么当 front 遍历到链表的末尾时，
// behind 就处于倒数第 n 个结点的前驱结点，即倒数第 n+1 个结点。
// 直接将 behind 指向倒数第 n-1 个结点就可删除第 n 个结点。
ListNode* removeNthFromEnd1(ListNode* head, int n)
{
    ListNode* aux_head = new ListNode(0, head);// 辅助结点，指向原链表的 head
    ListNode* behind = aux_head;
    ListNode* front = head;
    for (int i = 0; i < n; ++i) // 将 front 指针前移 n 位
        front = front->next;
    while (front != nullptr) // 可直接写为 while(front)
    {
        // front 指针指向链表最后一个结点时，behind 指向要删除结点的前继结点
        front = front->next;
        behind = behind->next;
    }
    ListNode* temp = behind->next;
    behind->next = behind->next->next; // 删除倒数第 n 个结点
    delete temp;
    temp = nullptr; // 置空，避免野指针

    ListNode* ans = aux_head->next; // 获取删除元素后的头结点
    delete aux_head; // 删除创建的辅助结点。
    aux_head = nullptr; // 置空，避免野指针
    return ans;
}

// 13、删除有序链表中的重复元素，返回头结点，比如 1,2,2,3,3,4 ，删除之后只有 1,4 
bool removeLinkDuplicates(ListNode* head)
{
    if (!head) // 头结点为空直接返回
        return head;
    ListNode* aux_head = new ListNode(0, head); // 创建辅助结点，是 head 结点的前继结点
    ListNode* cur = aux_head; // cur 指针指向创建的辅助结点
    
    while (cur->next && cur->next->next) // 循环条件是这两个结点不为空
    {
        if (cur->next->val == cur->next->next->val) // 连续两个结点的数据域相同
        {
            int same_val = cur->next->val; // 取出相同的数据域
            while (cur->next && cur->next->val == same_val) // 删除数据域相同的结点
                cur->next = cur->next->next;
        }
        else // 如果连续两个结点的数据域不相同，直接更新 cur
            cur = cur->next;
    }
    ListNode* ans = aux_head->next; // 获取辅助结点的下一个结点，即要返回的头结点
    delete aux_head; // 删除辅助结点
    aux_head = nullptr; // 置空，避免野指针
    return ans;
}
