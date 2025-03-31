#include"head.h"

// 1、删除链表中的指定元素，链表数据是随机的，未排序。
ListNode* removeLinkElement(ListNode* head, int val)
{
	// 辅助头结点 aux_head ，其后继结点是 head
	ListNode* aux_head = new ListNode(-1, head);
	ListNode* cur = aux_head;
	while (cur->next != nullptr) // 可直接写为 while(cur->next)
	{
		if (cur->next->val == val)
		{
			ListNode* temp = cur->next; // 获取要删除结点的地址，
			cur->next = cur->next->next;
			delete temp; // 释放要删除结点所指向的空间

			// 被 delete 之后的指针 temp 并不是 nullptr，而是随机值
			// 如果不将其设为 nullptr，就会成为指向随意的野指针，
			// 后续如果不小心使用了 temp，会指向难以预想的内存空间
			temp = nullptr; 
		}
		else
			cur = cur->next;
	}
	ListNode* ans = aux_head->next;
	delete aux_head;
	aux_head = nullptr; // 置空，避免野指针
	return ans;
}
ListNode* removeLinkElement2(ListNode* head, int targetVal)
{
	ListNode* aux_head = new ListNode(-1, head);
	ListNode* cur = aux_head;
	while (cur->next != nullptr)
	{
		if (cur->next->val == targetVal)
		{
			ListNode* temp = cur->next;
			cur->next = cur->next->next;
			delete temp;
			temp = nullptr;
		}
		else cur = cur->next;
	}
	ListNode* ans = aux_head->next;
	delete aux_head;
	aux_head = nullptr;
	return ans;
}

// 2、删除有序链表中的重复元素。比如 [1,2,2,3,3,4]，删除后变为 [1,4]
ListNode* removeSortLinkDuplicate(ListNode* head)
{
	if (!head) // 传入的链表头结点为空
		return head;
	ListNode* aux_head = new ListNode(-1, head); // 创建辅助结点
	ListNode* cur = aux_head; 
	while (cur->next && cur->next->next) // 循环的条件是这两个结点不为空
	{
		if (cur->next->val == cur->next->next->val) // 连续两个结点的值相等
		{
			int same_val = cur->next->val; // 得到相等的值
			while (cur->next && cur->next->val == same_val) // 删除值相等的结点
			{
				ListNode* temp = cur->next; // 获取要删除结点的地址
				cur->next = cur->next->next; // 执行删除结点操作
				delete temp; // 释放被删除结点指向的内存空间
				temp = nullptr; // 指针置空，避免成为野指针
			}
		}
		else 
			cur = cur->next; // 两个结点的值不相等，更新 cur
	}
	ListNode* ans = aux_head->next; // 得到删除重复元素之后的链表头结点
	delete aux_head; // 删除创建的辅助结点
	aux_head = nullptr; // 置空，避免野指针
	return ans;
}

// 3、设计链表。实现一些列表的函数。
// get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回 - 1。
// addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。
// addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。
// addAtIndex(index, val)：在链表中的第 index 个节点之前添加值为 val  的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。
// deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。

// 可以使用原链表直接操作，也可以设置虚拟头结点，后者较方便。
class myLinkList {
public:
	// 定义链表结点结构体，由于在 head.h 头文件中已经定义，这里注释。
	/*
	struct ListNode
	{
	public: // 结构体中如果不声明则默认是 public ，而类则是 private
		int val;
		ListNode* next;
		ListNode() :val(0), next(nullptr){}
		ListNode(int x):val(x),next(nullptr){}
		ListNode(int x,ListNode*next):val(x),next(next){}
	};
	*/
	
	myLinkList() // 构造函数
	{
		_size = 0;
		aux_head = new ListNode(0); // 辅助结点(虚拟结点)
	}

	// 获取第 index 结点的数据，注意 index 从 0 开始。index 非法则返回 -1
	int get(int index)
	{
		if (index<0 || index>(_size - 1))
			return -1;
		ListNode* cur = aux_head->next; // 因为 index 从 0 开始，所以 cur 从 aux_head->next 开始
		while (index--) // index-- 不是 --index
			cur = cur->next;
		return cur->val;
	}

	// 在链表的最前面插入一个结点
	void addAtHead(int insertVal)
	{
		ListNode* newNode = new ListNode(insertVal); // 创建要插入的结点
		
		// 这里必须先确定后继结点的原因是，如果先将要插入结点的前继结点指向要插入的结点
		// 那么该前继结点就会和它原本的后继结点断开，再将要插入的结点指向原本的后继结点时，
		// 就会找不到那个断开的后继结点。
		newNode->next = aux_head->next; // 必须先确认要插入的结点的后继结点，不然可能会找不到
		aux_head->next = newNode; // 然后再确认要插入结点的前继结点
		++_size;
	}

	// 在链表末尾添加一个结点
	void addAtTail(int val)
	{
		ListNode* cur = aux_head;
		while (cur->next) // 找到尾结点
			cur = cur->next;

		// 注意尾结点的后继结点是 nullptr，必须写上指向 nullptr
		ListNode* newNode = new ListNode(val,nullptr); 
		cur->next = newNode; // 将之前的尾结点指向要插入的尾结点
		++_size; // 链表长度加一
	}

	// 在第 index 个节点之前插入一个新节点，例如 index 为 0 ，那么新插入的节点为链表的新头节点。
	// 如果 index 等于链表的长度，则说明是新插入的节点为链表的尾结点
	// 如果 index 大于链表的长度，则返回空
	// 如果 index 小于 0 ，则在头部插入节点
	void addAtIndex(int index, int val)
	{
		if (index > _size)return;
		if (index < 0)index = 0;
		ListNode* newNode = new ListNode(val);  // 创建要插入的结点
		ListNode* cur = aux_head; // 指向辅助结点的指针
		while (index--)
			cur = cur->next; // 找到要插入位置的前一个结点
		
		// 插入新结点
		newNode->next = cur->next; 
		cur->next = newNode;
		_size++; // 链表长度加一
	}


	// 删除第 index 个节点，如果 index 大于等于链表的长度，直接 return ，注意 index 是从 0 开始的
	void deleteAtIndex(int index)
	{
		if (index >= _size || index < 0)return;
		ListNode* cur = aux_head;
		while (index--)
			cur = cur->next;
		ListNode* temp = cur->next; // 获取要删除结点的地址
		cur->next = cur->next->next; // 删除结点
		delete temp; // 释放被删除结点指向的空间
		temp = nullptr; // 指针置空，避免成为野指针
		--_size; // 链表长度减一
	}

	// 打印链表
	void printList()
	{
		ListNode* cur = aux_head; // 获取辅助结点的地址
		while (cur->next != nullptr) // 可直接写为 while(cur->next)
		{
			cout << cur->next->val << endl; // 打印值
			cur = cur->next; // 更新 cur
		}
	}
private:
	int _size; // 链表长度
	ListNode* aux_head; // 辅助结点，即头结点，其后继结点是链表存储元素的第一个结点。
};

// 4、翻转单链表
// 示例: 输入: 1->2->3->4->5->nullptr 输出 : 5->4->3->2->1->nullptr

// 解法 1：双指针法。从前往后原地翻转，不借助额外的链表
ListNode* reveseList(ListNode* head)
{
	ListNode* temp; // 用于保存 cur 的下一个结点
	ListNode* cur = head;
	ListNode* prev = nullptr;
	while (cur)
	{
		temp = cur->next; // 保存 cur 的下一个结点，因为接下来要改变 cur->next
		cur->next = prev; // 翻转操作。就是将原来链表中的后一个结点指向前一个结点
		// 更新 prev 和 cur
		prev = cur;
		cur = temp;
	}
	return prev;
}

// 5、两两交换链表中的结点，不只是交换数据，要交换整个结点
// 比如 [1,2,3,4,5,6],交换后变为 [2,1,4,3,6,5]。即交换相邻的结点
ListNode* swapPairs(ListNode* head)
{
	ListNode* aux_head = new ListNode(0, head); // 创建辅助头结点
	ListNode* cur = aux_head; // 指向辅助头结点的指针

	while (cur->next && cur->next->next) // 当这两个结点不为空
	{
		// 记录两个临时结点
		ListNode* temp = cur->next;
		ListNode* temp1 = cur->next->next;

		// 交换结点
		cur->next = cur->next->next;
		cur->next->next = temp;
		cur->next->next->next = temp1;

		// cur 移动两位，准备下一轮交换
		cur = cur->next->next;
	}
	ListNode* ans = aux_head->next;
	delete aux_head;
	aux_head = nullptr; // 置空，避免野指针
	return ans;
}

// 6、删除链表的倒数第 n 个结点，倒数肯定是从 1 开始数，不是从 0 开始数
// 
// 解法 1：利用栈。
// 遍历链表的同时将结点入栈，然后弹出栈的前 n 个数据，
// 此时栈顶的元素即为要删除的结点的前继结点，将其指向倒数第 n-1 个结点即可。
ListNode* deleteNthFromEnd(ListNode* head, int n)
{
	stack<ListNode*>stk; // 存放结点地址的栈
	ListNode* aux_head = new ListNode(-1, head); // 创建辅助结点
	ListNode* cur = aux_head; 
	while (cur) // 注意，创建的辅助结点也要入栈，因为第一个结点可能被删除
	{
		stk.push(cur); // 指针入栈
		cur = cur->next; // 更新 cur
	}

	for (int i = 0; i < n; ++i) // 弹出栈的前 n 个元素
		stk.pop();

	ListNode* prev = stk.top(); // 此时栈顶的元素就是要删除结点的前继结点
	ListNode* temp = prev->next; // 获取要删除结点的地址
	prev->next = prev->next->next; // 删除倒数第 n 个结点
	delete temp; // 释放被删除结点的内存
	temp = nullptr; // 置空，避免野指针

	ListNode* ans = aux_head->next; // 获取删除结点后链表的第一个结点
	delete aux_head; // 删除创建的辅助结点
	aux_head = nullptr; // 置空，避免野指针
	return ans;
}

// 解法 2：快慢指针。
// 定义快、慢两个指针，快指针超前慢指针 n 个位置，当快指针移动到链表末尾时，
// 慢指针指向的就是倒数第 n 个结点，此时再找到慢指针的前继结点(即倒数第 n+1 个结点),
// 将其指向倒数第 n-1 个结点，即可删除倒数第 n 个结点。

// 但是上面方法完全可以再简化，即将快指针超前慢指针 n+1 个位置，此时快指针移动到链表末尾时，
// 慢指针指向的就是倒数第 n 个结点的前继结点，将其直接指向倒数第 n-1 个结点即可。
ListNode* deleteNthFromEnd1(ListNode* head, int n)
{
	// 创建辅助结点，即虚拟头结点，其后继为结点 head
	ListNode* aux_head = new ListNode(-1, head); 
	
	// 创建前、后指针，front 指针落后 behind 指针一个位置
	ListNode* front = head;
	ListNode* behind = aux_head;
	for (int i = 0; i < n; ++i) // 将 front 指针向前移动 n 个位置
		front = front->next;
	
	// 此时 behind 落后 front n+1 个位置
	while (front) // 两个指针一起移动，front 指针到达链表末尾时停止
	{
		front = front->next;
		behind = behind->next;
	}
	ListNode* temp = behind->next; // 获取要删除结点的地址
	behind->next = behind->next->next; // 删除倒数第 n 个结点
	delete temp; // 释放要删除结点的空间
	temp = nullptr; // 置空，避免野指针

	ListNode* ans = aux_head->next; // 获取删除结点后的第一个数据结点
	delete aux_head; // 删除辅助结点
	aux_head = nullptr; // 置空，避免野指针
	return ans;
}

// 7、判断链表中是否有环
// 解法 1：
// 遍历链表结点的同时将结点放入容器中，在遍历的同时也检测结点是否在容器中
// 如果在，即有环。遍历完所有结点都不在容器中，则无环。
bool hasCircle(ListNode* head)
{
	unordered_set<ListNode*>seen; // 该集合存放遍历过的结点
	while (head)
	{
		if(seen.count(head)) // 结点在集合中则有环
			return true;
		else
		{
			seen.insert(head); // 结点插入集合中
			head = head->next; // 更新 head
		}
	}
	return false; // 遍历完所有结点都没有环
}

// 解法 2：快 、慢指针，直接原地操作。
// 定义快、慢指针，快指针在慢指针前一个位置，移动时慢指针移动 1 步，快指针移动 2 步
// 如果快指针追上了慢指针，说明有环，否则无环。
// 这种方法需要先判断链表的的长度是否满足，结点数小于 2 不会有环

bool hasCircle1(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) // 结点小于 2 则无环
		return false;
	ListNode* slow = head; // 慢指针最开始指向第一个结点
	ListNode* fast = head->next; // 快指针最开始指向第 2 个结点
	while (fast != slow) // 快指针没有追上慢指针
	{
		// 这一句是重点。如果链表没有环，则快指针会先到达链表末尾结点或成为 nullptr
		// 因为快指针每次是移动两步，所以最后一次移动可能到达两个位置
		if (fast == nullptr || fast->next == nullptr)
			return false;
		slow = slow->next; // 慢指针一次移动一步
		fast = fast->next->next; // 快指针一次移动两步
	}
	return true;
}
