#include"head.h"

// 1、移除元素
// 数组 nums 和值 val ，原地 移除所有数值等于 val 的元素，并返回移除后数组的新长度。
// 不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
// 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

// 示例 1: 
// 给定 nums = [3, 2, 2, 3], val = 3, 
// 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。 
// 你不需要考虑数组中超出新长度后面的元素。

// 示例 2 : 
// 给定 nums = [0, 1, 2, 2, 3, 0, 4, 2], val = 2, 
// 函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。

// 解题思路：
// 直接删除数组中的元素很麻烦，因为数组的存储空间是连续的，删掉一个元素就要移动其它元素。
// 一般原地操作的问题基本都可以使用双指针进行解决，不适用额外的空间。

// 解法 1：两个 for 循环直接暴力解决，不推荐。

// 解法 2：双指针
int removeTargetNum(vector<int>& nums, int target)
{
	int slow = 0;
	int fast = 0;
	while (fast < nums.size())
	{
		if (nums[fast] != target)
		{
			// 如果 fast 的位置是要保留的数，就将 fast 位置的数赋给 slow 位置
			// 然后两个指针同时右移一个位置
			nums[slow++] = nums[fast++]; // 注意 ++ 都是后置
		}
		else
			++fast; // fast 的位置是要删除的值，则只将 fast 右移一个位置
	}
	return slow; // 最后的 slow 就是删除数据后数组的长度。
}

// 2、反转字符串
// 输入字符串以字符数组 char[] 的形式给出。
// 必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。
// 你可以假设数组中的所有字符都是 ASCII 码表中的可打印字符。

void reverStr(vector<char>& str)
{
	int left = 0;
	int right = str.size() - 1;

	// 字符串长度为奇数的话，中间位置的字符不用处理，因为反转后仍在中间
	while (left < right) 
	{
		// 使用临时变量 temp 交换 str[left] 和 str[right]
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;

		// left 右移，right 左移
		++left;
		--right;
	}
}

// 3、反转链表
// 示例: 输入: 1->2->3->4->5->NULL 输出 : 5->4->3->2->1->NULL

// 解题思路：
// 生成一个 nullptr ，然后将原链表从头到尾逐个取出，取出的第一个结点链接到这个 nullptr
// 第二个结点链接到第一个结点，第三个链接到第二个，依次链接
// 最后链接的那个结点，就是翻转后链表的第一个结点。
ListNode* reverList(ListNode* head)
{
	ListNode* temp; // 临时指针
	ListNode* cur = head; // 指向原链表的第一个结点
	ListNode* pre = nullptr; // 辅助结点
	while (cur) // 遍历原链表
	{
		// 要先获取到原链表当前操纵结点的下一个结点，不然后面改变当前操纵结点的指向后就会找不到原链表
		temp = cur->next; 

		// 改变原链表当前操纵结点的指向，原链表的第一个结点翻转后就是最后一个结点，指向 nullptr
		cur->next = pre;

		// 改变辅助结点，pre 从 nullptr 变为原链表的第一个、第二个、到最后一个结点
		pre = cur;

		// 改变操纵结点，变为当前操纵结点的下一个结点
		cur = temp;
	}
	return pre;
}

// 4、删除倒数第 n 个结点
// 解法 1 ：双指针。
// 即快指针比慢指针领先 n+1 个位置，两指针每次移动一步，当快指针移动到链表最后一个位置时，
// 慢指针指向的位置就是倒数第 n 个结点的前继结点，将其指向倒数第 n-1 个结点即可
// 注意最后需要释放使用 new 创建的辅助结点
ListNode* removeNth(ListNode* head, int n)
{
	// 因为第一个结点可能被删除，所以最好创建辅助结点，其后继结点是传入的链表的第一个结点
	ListNode* aux_head = new ListNode(-1, head);
	
	// 快指针领先一个位置
	ListNode* slow = aux_head;
	ListNode* fast = head;

	// 快指针再移动 n 个位置，此时快指针就领先 n+1 个位置了
	for (int i = 0; i < n; ++i)
		fast = fast->next;

	// 两指针每次同时移动一步，直到快指针到最后一个结点
	while (fast)
	{
		fast = fast->next;
		slow = slow->next;
	}

	// 此时 slow 的指向就是倒数第 n+1 个结点，将其指向倒数第 n-1 个结点
	slow->next = slow->next->next;

	// 获取删除结点之后链表的第一个结点。
	ListNode* ans = aux_head;
	delete aux_head; // 释放创建的辅助结点
	aux_head = nullptr; // 指针置空，避免野指针
	return ans;
}

// 解法 2：利用栈。
// 创建辅助结点，遍历链表的同时将结点入栈，然后弹出栈中的前 n 个元素
// 此时栈顶的元素就是倒数第 n 个结点的前继结点，将其指向倒数第 n-1 个结点即可
// 注意最后需要释放使用 new 创建的辅助结点
ListNode* removeNth1(ListNode* head, int n)
{
	// 因为第一个结点可能被删除，所以创建辅助结点，方便获取删除结点之后链表的第一个结点
	// 其后继结点是传入链表的第一个结点
	ListNode* aux_head = new ListNode(-1, head);

	// 指针指向辅助结点
	ListNode* cur = aux_head;
	stack<ListNode*>stk; // 存放结点指针的栈

	while (cur) // 全部结点入栈
	{
		stk.push(cur);
		cur = cur->next;
	}

	for (int i = 0; i < n; ++i) // 弹出栈中的前 n 个元素
		stk.pop();

	// 此时栈顶元素就是倒数第 n 个结点的前继结点，即倒数第 n+1 个结点
	ListNode* pre = stk.top();

	// 将倒数第 n+1 个结点指向倒数第 n-1 个结点即可删除倒数第 n 个结点
	pre->next = pre->next->next;

	// 获取删除结点后链表的第一个结点
	ListNode* ans = aux_head->next;
	delete aux_head; // 释放辅助结点
	aux_head = nullptr; // 指针置空，避免野指针
	return ans;
}

// 5、链表交点。没懂什么叫指针相等。
// 给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
// 如果两个链表没有交点，返回 null 。

// 简单来说，就是求两个链表交点节点的指针。 
// 特别注意，交点不是数值相等，而是指针相等。
// 比如 [4,2,1,3,5] 和 [3,3,2,1,3,5] 的交点是 1，而不是 2

// 解题思路：求出两个链表的长度差，然后将两个链表末尾对齐，
// 对齐的具体操作：比如链表 A 长度为 5，链表 B 长度为 3，
// 创建两个 headA、headB 两个指针分别指向 A、B 链表的第一个结点，
// 因为两者的长度差是 2 ，所以将较长链表 A 的 headA 移动 2 个位置，到达倒数第三个位置，
// 此时就完成了链表末尾对齐。
// 末尾对齐后依次比较指针是否相等，相等则找到交点，不相等则两指针同时移动一个位置。
// 比较完之后没有交点则返回 nullptr
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
	// 指向两个链表第一个结点的指针
	ListNode* curA = headA;
	ListNode* curB = headB;

	// 存储两个链表长度
	int lenA = 0;
	int lenB = 0;

	// 计算两链表长度
	while (curA)
	{
		++lenA;
		curA = curA->next;
	}
	while (curB)
	{
		++lenB;
		curB = curB->next;
	}

	
	curA = headA;
	curB = headB;
	// lenA 代表较长链表的长度，lenB 则是较短链表
	// curA 指向较长链表的第一个结点，curB 指向较短链表
	if (lenA < lenB)
	{
		swap(lenA, lenB);
		swap(headA, headB);
	}

	// 计算长度差，并移动指向较长链表第一个结点的指针 gap 个位置，即末尾对齐
	int gap = lenA - lenB;
	while (gap--)
		curA = curA->next;

	while (curA)
	{
		// 检查是不是交点。如果是交点，则对应的指针相等，那么后续的指针也就相等
		if (curA == curB)
			return curA;

		// 两指针同时移动一步
		curA = curA->next;
		curB = curB->next;
	}
	return nullptr; // 没有交点
}

// 6、判断链表是否有环，如果有则返回开始入环的第一个结点
// 题意： 给定一个链表，有环则返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
// 为了表示给定链表中的环，使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
// 如果 pos 是 - 1，则在该链表中没有环。
// 说明：不允许修改给定的链表。

// 解法 1：双指针(快、慢指针)
// 定义 slow 和 fast 两个指针，都从链表的第一个结点开始移动，
// 只是 slow 每次移动一步， fast 每次移动两步，如果 fast 追上 slow ，则说明有环。
// 至于怎样找到环的入口，需要一点数学推理

ListNode* cycleLinkListEntrance(ListNode* head)
{
	ListNode* slow = head;
	ListNode* fast = head;

	// 因为快指针一次走两步，所以其最后一步可能到达直接到达最后一个结点或 nullptr
	// 如果没有到达这两个位置，说明有环
	while (fast != nullptr || fast->next != nullptr)
	{
		slow = slow->next; // 慢指针移动一步
		fast = fast->next->next; // 快指针移动两步

		// 快慢指针相遇，此时从 head 和 相遇点，同时查找直至相遇
		if (slow == fast)
		{
			// 这里代码的意思是 index1 从环的入口开始移动，index2 从第一个结点开始移动
			// 当 index1 绕着环一圈回到环的入口，index2 也刚好走到环的入口
			// index1 绕 n 圈的情况和一圈类似，只是绕的圈数更多
			ListNode* index1 = fast;
			ListNode* index2 = head;
			while (index1 != index2)
			{
				index1 = index1->next;
				index2 = index2->next;
			}
			return index2; // 环的入口结点
		}
	}
	return nullptr;
}

// 7、三数之和，去重操作没太懂
// 给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，
// 使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。
// 注意： 答案中不可以包含重复的三元组。意思是每个符合条件的组合不能相同

vector<vector<int>>thrSum(vector<int>& nums)
{
	vector<vector<int>>result;
	sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size(); ++i)
	{
		if (nums[i] > 0)
			return result;

		// 对 nums[i] 去重。因为经过了排序，所以相等的元素必然相邻
		// 此时跳出当前循环，进入下一次循环，避免不同的组合中的第一个元素 nums[i] 相同
		if (i > 0 && nums[i] == nums[i - 1])
			continue;

		int left = i + 1;
		int right = nums.size() - 1;
		while (left < right)
		{
			if ((nums[i] + nums[left] + nums[right]) < 0)
				++left;
			else if ((nums[i] + nums[left] + nums[right]) > 0)
				--right;
			else
			{
				result.push_back(vector<int>{nums[i], nums[left], nums[right]});
				
				// 对 nums[left] 和 nums[right] 去重
				while (left < right && nums[left] == nums[left + 1])
					++left;
				while (left < right && nums[right] == nums[right - 1])
					--right;

				// 如果有符合条件的组合，同时收缩 left 和 right
				++left;
				--right;
			}
		}
	}
	return result;
}

// 8、四数之和，还是去重没太懂
//题意：给定一个包含 n 个整数的数组 nums 和一个目标值 target，
//判断 nums 中是否存在四个元素 a，b，c 和 d ，
//使得 a + b + c + d 的值与 target 相等？找出所有满足条件且不重复的四元组。
//注意：答案中不可以包含重复的四元组。

// 解决思路：和三数之和类似，只是最外层再嵌套一层循环
vector<vector<int>>fourNSum(vector<int>& nums,int target)
{
	vector<vector<int>>result; // 存储可能的组合
	sort(nums.begin(), nums.end()); // 排序
	
	for (int i = 0; i < nums.size(); ++i) // 第一层循环
	{
		// 剪枝，排序后的第一个数就大于 target，且后面的数大于等于 0，不会有符合条件的组合
		if (nums[i] > target && nums[i + 1] >= 0) 
			break;
		
		// 对 nums[i] 去重。因为经过了排序，所以相等的元素必然相邻
		// 此时跳出当前循环，进入下一次循环，避免不同的组合中的第一个元素 nums[i] 相同
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		for (int j = i + 1; j < nums.size(); ++j) // 第二层循环
		{
			// 剪枝
			if (nums[i] + nums[j] > target && nums[j + 1] >= 0)
				break;

			// 对 nums[j] 去重。因为经过了排序，所以相等的元素必然相邻
			// 此时跳出当前循环，进入下一次循环，避免不同的组合中的第二个元素 nums[j] 相同
			if (j > i + 1 && nums[j] == nums[j - 1]) 
				continue;

			// 定义左、右指针
			int left = j + 1;
			int right = nums.size() - 1;
			while (left < right)
			{
				// 排序后，四数和小于 target，表明需要增大，所以 left 右移
				if ((nums[i] + nums[j] + nums[left] + nums[right]) < target)
					++left;
				// 排序后，四数和大于 target，表明需要减小，所以 right 左移
				else if ((nums[i] + nums[j] + nums[left] + nums[right]) > target)
					--right;
				else
				{
					// 找到符合条件的组合
					result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
					// 对 nums[left] 去重
					while (left < right && nums[left] == nums[left + 1])
						++left;
					// 对 nums[right] 去重
					while (left < right && nums[right] == nums[right - 1])
						--right;
					// 找到符合条件的组合就同时收缩 left 和 right
					++left;
					--right;
				}
			}
		}
	}
	return result;
}
