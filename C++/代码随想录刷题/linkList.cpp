#include"head.h"

// 1��ɾ�������е�ָ��Ԫ�أ���������������ģ�δ����
ListNode* removeLinkElement(ListNode* head, int val)
{
	// ����ͷ��� aux_head �����̽���� head
	ListNode* aux_head = new ListNode(-1, head);
	ListNode* cur = aux_head;
	while (cur->next != nullptr) // ��ֱ��дΪ while(cur->next)
	{
		if (cur->next->val == val)
		{
			ListNode* temp = cur->next; // ��ȡҪɾ�����ĵ�ַ��
			cur->next = cur->next->next;
			delete temp; // �ͷ�Ҫɾ�������ָ��Ŀռ�

			// �� delete ֮���ָ�� temp ������ nullptr���������ֵ
			// �����������Ϊ nullptr���ͻ��Ϊָ�������Ұָ�룬
			// ���������С��ʹ���� temp����ָ������Ԥ����ڴ�ռ�
			temp = nullptr; 
		}
		else
			cur = cur->next;
	}
	ListNode* ans = aux_head->next;
	delete aux_head;
	aux_head = nullptr; // �ÿգ�����Ұָ��
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

// 2��ɾ�����������е��ظ�Ԫ�ء����� [1,2,2,3,3,4]��ɾ�����Ϊ [1,4]
ListNode* removeSortLinkDuplicate(ListNode* head)
{
	if (!head) // ���������ͷ���Ϊ��
		return head;
	ListNode* aux_head = new ListNode(-1, head); // �����������
	ListNode* cur = aux_head; 
	while (cur->next && cur->next->next) // ѭ������������������㲻Ϊ��
	{
		if (cur->next->val == cur->next->next->val) // ������������ֵ���
		{
			int same_val = cur->next->val; // �õ���ȵ�ֵ
			while (cur->next && cur->next->val == same_val) // ɾ��ֵ��ȵĽ��
			{
				ListNode* temp = cur->next; // ��ȡҪɾ�����ĵ�ַ
				cur->next = cur->next->next; // ִ��ɾ��������
				delete temp; // �ͷű�ɾ�����ָ����ڴ�ռ�
				temp = nullptr; // ָ���ÿգ������ΪҰָ��
			}
		}
		else 
			cur = cur->next; // ��������ֵ����ȣ����� cur
	}
	ListNode* ans = aux_head->next; // �õ�ɾ���ظ�Ԫ��֮�������ͷ���
	delete aux_head; // ɾ�������ĸ������
	aux_head = nullptr; // �ÿգ�����Ұָ��
	return ans;
}

// 3���������ʵ��һЩ�б�ĺ�����
// get(index)����ȡ�����е� index ���ڵ��ֵ�����������Ч���򷵻� - 1��
// addAtHead(val)��������ĵ�һ��Ԫ��֮ǰ���һ��ֵΪ val �Ľڵ㡣������½ڵ㽫��Ϊ����ĵ�һ���ڵ㡣
// addAtTail(val)����ֵΪ val �Ľڵ�׷�ӵ���������һ��Ԫ�ء�
// addAtIndex(index, val)���������еĵ� index ���ڵ�֮ǰ���ֵΪ val  �Ľڵ㡣��� index ��������ĳ��ȣ���ýڵ㽫���ӵ������ĩβ����� index ���������ȣ��򲻻����ڵ㡣���indexС��0������ͷ������ڵ㡣
// deleteAtIndex(index)��������� index ��Ч����ɾ�������еĵ� index ���ڵ㡣

// ����ʹ��ԭ����ֱ�Ӳ�����Ҳ������������ͷ��㣬���߽Ϸ��㡣
class myLinkList {
public:
	// ����������ṹ�壬������ head.h ͷ�ļ����Ѿ����壬����ע�͡�
	/*
	struct ListNode
	{
	public: // �ṹ���������������Ĭ���� public ���������� private
		int val;
		ListNode* next;
		ListNode() :val(0), next(nullptr){}
		ListNode(int x):val(x),next(nullptr){}
		ListNode(int x,ListNode*next):val(x),next(next){}
	};
	*/
	
	myLinkList() // ���캯��
	{
		_size = 0;
		aux_head = new ListNode(0); // �������(������)
	}

	// ��ȡ�� index �������ݣ�ע�� index �� 0 ��ʼ��index �Ƿ��򷵻� -1
	int get(int index)
	{
		if (index<0 || index>(_size - 1))
			return -1;
		ListNode* cur = aux_head->next; // ��Ϊ index �� 0 ��ʼ������ cur �� aux_head->next ��ʼ
		while (index--) // index-- ���� --index
			cur = cur->next;
		return cur->val;
	}

	// ���������ǰ�����һ�����
	void addAtHead(int insertVal)
	{
		ListNode* newNode = new ListNode(insertVal); // ����Ҫ����Ľ��
		
		// ���������ȷ����̽���ԭ���ǣ�����Ƚ�Ҫ�������ǰ�̽��ָ��Ҫ����Ľ��
		// ��ô��ǰ�̽��ͻ����ԭ���ĺ�̽��Ͽ����ٽ�Ҫ����Ľ��ָ��ԭ���ĺ�̽��ʱ��
		// �ͻ��Ҳ����Ǹ��Ͽ��ĺ�̽�㡣
		newNode->next = aux_head->next; // ������ȷ��Ҫ����Ľ��ĺ�̽�㣬��Ȼ���ܻ��Ҳ���
		aux_head->next = newNode; // Ȼ����ȷ��Ҫ�������ǰ�̽��
		++_size;
	}

	// ������ĩβ���һ�����
	void addAtTail(int val)
	{
		ListNode* cur = aux_head;
		while (cur->next) // �ҵ�β���
			cur = cur->next;

		// ע��β���ĺ�̽���� nullptr������д��ָ�� nullptr
		ListNode* newNode = new ListNode(val,nullptr); 
		cur->next = newNode; // ��֮ǰ��β���ָ��Ҫ�����β���
		++_size; // �����ȼ�һ
	}

	// �ڵ� index ���ڵ�֮ǰ����һ���½ڵ㣬���� index Ϊ 0 ����ô�²���Ľڵ�Ϊ�������ͷ�ڵ㡣
	// ��� index ��������ĳ��ȣ���˵�����²���Ľڵ�Ϊ�����β���
	// ��� index ��������ĳ��ȣ��򷵻ؿ�
	// ��� index С�� 0 ������ͷ������ڵ�
	void addAtIndex(int index, int val)
	{
		if (index > _size)return;
		if (index < 0)index = 0;
		ListNode* newNode = new ListNode(val);  // ����Ҫ����Ľ��
		ListNode* cur = aux_head; // ָ��������ָ��
		while (index--)
			cur = cur->next; // �ҵ�Ҫ����λ�õ�ǰһ�����
		
		// �����½��
		newNode->next = cur->next; 
		cur->next = newNode;
		_size++; // �����ȼ�һ
	}


	// ɾ���� index ���ڵ㣬��� index ���ڵ�������ĳ��ȣ�ֱ�� return ��ע�� index �Ǵ� 0 ��ʼ��
	void deleteAtIndex(int index)
	{
		if (index >= _size || index < 0)return;
		ListNode* cur = aux_head;
		while (index--)
			cur = cur->next;
		ListNode* temp = cur->next; // ��ȡҪɾ�����ĵ�ַ
		cur->next = cur->next->next; // ɾ�����
		delete temp; // �ͷű�ɾ�����ָ��Ŀռ�
		temp = nullptr; // ָ���ÿգ������ΪҰָ��
		--_size; // �����ȼ�һ
	}

	// ��ӡ����
	void printList()
	{
		ListNode* cur = aux_head; // ��ȡ�������ĵ�ַ
		while (cur->next != nullptr) // ��ֱ��дΪ while(cur->next)
		{
			cout << cur->next->val << endl; // ��ӡֵ
			cur = cur->next; // ���� cur
		}
	}
private:
	int _size; // ������
	ListNode* aux_head; // ������㣬��ͷ��㣬���̽��������洢Ԫ�صĵ�һ����㡣
};

// 4����ת������
// ʾ��: ����: 1->2->3->4->5->nullptr ��� : 5->4->3->2->1->nullptr

// �ⷨ 1��˫ָ�뷨����ǰ����ԭ�ط�ת�����������������
ListNode* reveseList(ListNode* head)
{
	ListNode* temp; // ���ڱ��� cur ����һ�����
	ListNode* cur = head;
	ListNode* prev = nullptr;
	while (cur)
	{
		temp = cur->next; // ���� cur ����һ����㣬��Ϊ������Ҫ�ı� cur->next
		cur->next = prev; // ��ת���������ǽ�ԭ�������еĺ�һ�����ָ��ǰһ�����
		// ���� prev �� cur
		prev = cur;
		cur = temp;
	}
	return prev;
}

// 5���������������еĽ�㣬��ֻ�ǽ������ݣ�Ҫ�����������
// ���� [1,2,3,4,5,6],�������Ϊ [2,1,4,3,6,5]�����������ڵĽ��
ListNode* swapPairs(ListNode* head)
{
	ListNode* aux_head = new ListNode(0, head); // ��������ͷ���
	ListNode* cur = aux_head; // ָ����ͷ����ָ��

	while (cur->next && cur->next->next) // ����������㲻Ϊ��
	{
		// ��¼������ʱ���
		ListNode* temp = cur->next;
		ListNode* temp1 = cur->next->next;

		// �������
		cur->next = cur->next->next;
		cur->next->next = temp;
		cur->next->next->next = temp1;

		// cur �ƶ���λ��׼����һ�ֽ���
		cur = cur->next->next;
	}
	ListNode* ans = aux_head->next;
	delete aux_head;
	aux_head = nullptr; // �ÿգ�����Ұָ��
	return ans;
}

// 6��ɾ������ĵ����� n ����㣬�����϶��Ǵ� 1 ��ʼ�������Ǵ� 0 ��ʼ��
// 
// �ⷨ 1������ջ��
// ���������ͬʱ�������ջ��Ȼ�󵯳�ջ��ǰ n �����ݣ�
// ��ʱջ����Ԫ�ؼ�ΪҪɾ���Ľ���ǰ�̽�㣬����ָ������ n-1 ����㼴�ɡ�
ListNode* deleteNthFromEnd(ListNode* head, int n)
{
	stack<ListNode*>stk; // ��Ž���ַ��ջ
	ListNode* aux_head = new ListNode(-1, head); // �����������
	ListNode* cur = aux_head; 
	while (cur) // ע�⣬�����ĸ������ҲҪ��ջ����Ϊ��һ�������ܱ�ɾ��
	{
		stk.push(cur); // ָ����ջ
		cur = cur->next; // ���� cur
	}

	for (int i = 0; i < n; ++i) // ����ջ��ǰ n ��Ԫ��
		stk.pop();

	ListNode* prev = stk.top(); // ��ʱջ����Ԫ�ؾ���Ҫɾ������ǰ�̽��
	ListNode* temp = prev->next; // ��ȡҪɾ�����ĵ�ַ
	prev->next = prev->next->next; // ɾ�������� n �����
	delete temp; // �ͷű�ɾ�������ڴ�
	temp = nullptr; // �ÿգ�����Ұָ��

	ListNode* ans = aux_head->next; // ��ȡɾ����������ĵ�һ�����
	delete aux_head; // ɾ�������ĸ������
	aux_head = nullptr; // �ÿգ�����Ұָ��
	return ans;
}

// �ⷨ 2������ָ�롣
// ����졢������ָ�룬��ָ�볬ǰ��ָ�� n ��λ�ã�����ָ���ƶ�������ĩβʱ��
// ��ָ��ָ��ľ��ǵ����� n ����㣬��ʱ���ҵ���ָ���ǰ�̽��(�������� n+1 �����),
// ����ָ������ n-1 ����㣬����ɾ�������� n ����㡣

// �������淽����ȫ�����ټ򻯣�������ָ�볬ǰ��ָ�� n+1 ��λ�ã���ʱ��ָ���ƶ�������ĩβʱ��
// ��ָ��ָ��ľ��ǵ����� n ������ǰ�̽�㣬����ֱ��ָ������ n-1 ����㼴�ɡ�
ListNode* deleteNthFromEnd1(ListNode* head, int n)
{
	// ����������㣬������ͷ��㣬����Ϊ��� head
	ListNode* aux_head = new ListNode(-1, head); 
	
	// ����ǰ����ָ�룬front ָ����� behind ָ��һ��λ��
	ListNode* front = head;
	ListNode* behind = aux_head;
	for (int i = 0; i < n; ++i) // �� front ָ����ǰ�ƶ� n ��λ��
		front = front->next;
	
	// ��ʱ behind ��� front n+1 ��λ��
	while (front) // ����ָ��һ���ƶ���front ָ�뵽������ĩβʱֹͣ
	{
		front = front->next;
		behind = behind->next;
	}
	ListNode* temp = behind->next; // ��ȡҪɾ�����ĵ�ַ
	behind->next = behind->next->next; // ɾ�������� n �����
	delete temp; // �ͷ�Ҫɾ�����Ŀռ�
	temp = nullptr; // �ÿգ�����Ұָ��

	ListNode* ans = aux_head->next; // ��ȡɾ������ĵ�һ�����ݽ��
	delete aux_head; // ɾ���������
	aux_head = nullptr; // �ÿգ�����Ұָ��
	return ans;
}

// 7���ж��������Ƿ��л�
// �ⷨ 1��
// �����������ͬʱ�������������У��ڱ�����ͬʱҲ������Ƿ���������
// ����ڣ����л������������н�㶼���������У����޻���
bool hasCircle(ListNode* head)
{
	unordered_set<ListNode*>seen; // �ü��ϴ�ű������Ľ��
	while (head)
	{
		if(seen.count(head)) // ����ڼ��������л�
			return true;
		else
		{
			seen.insert(head); // �����뼯����
			head = head->next; // ���� head
		}
	}
	return false; // ���������н�㶼û�л�
}

// �ⷨ 2���� ����ָ�룬ֱ��ԭ�ز�����
// ����졢��ָ�룬��ָ������ָ��ǰһ��λ�ã��ƶ�ʱ��ָ���ƶ� 1 ������ָ���ƶ� 2 ��
// �����ָ��׷������ָ�룬˵���л��������޻���
// ���ַ�����Ҫ���ж�����ĵĳ����Ƿ����㣬�����С�� 2 �����л�

bool hasCircle1(ListNode* head)
{
	if (head == nullptr || head->next == nullptr) // ���С�� 2 ���޻�
		return false;
	ListNode* slow = head; // ��ָ���ʼָ���һ�����
	ListNode* fast = head->next; // ��ָ���ʼָ��� 2 �����
	while (fast != slow) // ��ָ��û��׷����ָ��
	{
		// ��һ�����ص㡣�������û�л������ָ����ȵ�������ĩβ�����Ϊ nullptr
		// ��Ϊ��ָ��ÿ�����ƶ��������������һ���ƶ����ܵ�������λ��
		if (fast == nullptr || fast->next == nullptr)
			return false;
		slow = slow->next; // ��ָ��һ���ƶ�һ��
		fast = fast->next->next; // ��ָ��һ���ƶ�����
	}
	return true;
}
