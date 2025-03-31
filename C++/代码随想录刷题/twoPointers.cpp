#include"head.h"

// 1���Ƴ�Ԫ��
// ���� nums ��ֵ val ��ԭ�� �Ƴ�������ֵ���� val ��Ԫ�أ��������Ƴ���������³��ȡ�
// ��Ҫʹ�ö��������ռ䣬������ʹ�� O(1) ����ռ䲢ԭ���޸��������顣
// Ԫ�ص�˳����Ըı䡣�㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�

// ʾ�� 1: 
// ���� nums = [3, 2, 2, 3], val = 3, 
// ����Ӧ�÷����µĳ��� 2, ���� nums �е�ǰ����Ԫ�ؾ�Ϊ 2�� 
// �㲻��Ҫ���������г����³��Ⱥ����Ԫ�ء�

// ʾ�� 2 : 
// ���� nums = [0, 1, 2, 2, 3, 0, 4, 2], val = 2, 
// ����Ӧ�÷����µĳ��� 5, ���� nums �е�ǰ���Ԫ��Ϊ 0, 1, 3, 0, 4��

// ����˼·��
// ֱ��ɾ�������е�Ԫ�غ��鷳����Ϊ����Ĵ洢�ռ��������ģ�ɾ��һ��Ԫ�ؾ�Ҫ�ƶ�����Ԫ�ء�
// һ��ԭ�ز������������������ʹ��˫ָ����н���������ö���Ŀռ䡣

// �ⷨ 1������ for ѭ��ֱ�ӱ�����������Ƽ���

// �ⷨ 2��˫ָ��
int removeTargetNum(vector<int>& nums, int target)
{
	int slow = 0;
	int fast = 0;
	while (fast < nums.size())
	{
		if (nums[fast] != target)
		{
			// ��� fast ��λ����Ҫ�����������ͽ� fast λ�õ������� slow λ��
			// Ȼ������ָ��ͬʱ����һ��λ��
			nums[slow++] = nums[fast++]; // ע�� ++ ���Ǻ���
		}
		else
			++fast; // fast ��λ����Ҫɾ����ֵ����ֻ�� fast ����һ��λ��
	}
	return slow; // ���� slow ����ɾ�����ݺ�����ĳ��ȡ�
}

// 2����ת�ַ���
// �����ַ������ַ����� char[] ����ʽ������
// ����ԭ���޸��������顢ʹ�� O(1) �Ķ���ռ�����һ���⡣
// ����Լ��������е������ַ����� ASCII ����еĿɴ�ӡ�ַ���

void reverStr(vector<char>& str)
{
	int left = 0;
	int right = str.size() - 1;

	// �ַ�������Ϊ�����Ļ����м�λ�õ��ַ����ô�����Ϊ��ת�������м�
	while (left < right) 
	{
		// ʹ����ʱ���� temp ���� str[left] �� str[right]
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;

		// left ���ƣ�right ����
		++left;
		--right;
	}
}

// 3����ת����
// ʾ��: ����: 1->2->3->4->5->NULL ��� : 5->4->3->2->1->NULL

// ����˼·��
// ����һ�� nullptr ��Ȼ��ԭ�����ͷ��β���ȡ����ȡ���ĵ�һ��������ӵ���� nullptr
// �ڶ���������ӵ���һ����㣬���������ӵ��ڶ�������������
// ������ӵ��Ǹ���㣬���Ƿ�ת������ĵ�һ����㡣
ListNode* reverList(ListNode* head)
{
	ListNode* temp; // ��ʱָ��
	ListNode* cur = head; // ָ��ԭ����ĵ�һ�����
	ListNode* pre = nullptr; // �������
	while (cur) // ����ԭ����
	{
		// Ҫ�Ȼ�ȡ��ԭ����ǰ���ݽ�����һ����㣬��Ȼ����ı䵱ǰ���ݽ���ָ���ͻ��Ҳ���ԭ����
		temp = cur->next; 

		// �ı�ԭ����ǰ���ݽ���ָ��ԭ����ĵ�һ����㷭ת��������һ����㣬ָ�� nullptr
		cur->next = pre;

		// �ı丨����㣬pre �� nullptr ��Ϊԭ����ĵ�һ�����ڶ����������һ�����
		pre = cur;

		// �ı���ݽ�㣬��Ϊ��ǰ���ݽ�����һ�����
		cur = temp;
	}
	return pre;
}

// 4��ɾ�������� n �����
// �ⷨ 1 ��˫ָ�롣
// ����ָ�����ָ������ n+1 ��λ�ã���ָ��ÿ���ƶ�һ��������ָ���ƶ����������һ��λ��ʱ��
// ��ָ��ָ���λ�þ��ǵ����� n ������ǰ�̽�㣬����ָ������ n-1 ����㼴��
// ע�������Ҫ�ͷ�ʹ�� new �����ĸ������
ListNode* removeNth(ListNode* head, int n)
{
	// ��Ϊ��һ�������ܱ�ɾ����������ô���������㣬���̽���Ǵ��������ĵ�һ�����
	ListNode* aux_head = new ListNode(-1, head);
	
	// ��ָ������һ��λ��
	ListNode* slow = aux_head;
	ListNode* fast = head;

	// ��ָ�����ƶ� n ��λ�ã���ʱ��ָ������� n+1 ��λ����
	for (int i = 0; i < n; ++i)
		fast = fast->next;

	// ��ָ��ÿ��ͬʱ�ƶ�һ����ֱ����ָ�뵽���һ�����
	while (fast)
	{
		fast = fast->next;
		slow = slow->next;
	}

	// ��ʱ slow ��ָ����ǵ����� n+1 ����㣬����ָ������ n-1 �����
	slow->next = slow->next->next;

	// ��ȡɾ�����֮������ĵ�һ����㡣
	ListNode* ans = aux_head;
	delete aux_head; // �ͷŴ����ĸ������
	aux_head = nullptr; // ָ���ÿգ�����Ұָ��
	return ans;
}

// �ⷨ 2������ջ��
// ����������㣬���������ͬʱ�������ջ��Ȼ�󵯳�ջ�е�ǰ n ��Ԫ��
// ��ʱջ����Ԫ�ؾ��ǵ����� n ������ǰ�̽�㣬����ָ������ n-1 ����㼴��
// ע�������Ҫ�ͷ�ʹ�� new �����ĸ������
ListNode* removeNth1(ListNode* head, int n)
{
	// ��Ϊ��һ�������ܱ�ɾ�������Դ���������㣬�����ȡɾ�����֮������ĵ�һ�����
	// ���̽���Ǵ�������ĵ�һ�����
	ListNode* aux_head = new ListNode(-1, head);

	// ָ��ָ�������
	ListNode* cur = aux_head;
	stack<ListNode*>stk; // ��Ž��ָ���ջ

	while (cur) // ȫ�������ջ
	{
		stk.push(cur);
		cur = cur->next;
	}

	for (int i = 0; i < n; ++i) // ����ջ�е�ǰ n ��Ԫ��
		stk.pop();

	// ��ʱջ��Ԫ�ؾ��ǵ����� n ������ǰ�̽�㣬�������� n+1 �����
	ListNode* pre = stk.top();

	// �������� n+1 �����ָ������ n-1 ����㼴��ɾ�������� n �����
	pre->next = pre->next->next;

	// ��ȡɾ����������ĵ�һ�����
	ListNode* ans = aux_head->next;
	delete aux_head; // �ͷŸ������
	aux_head = nullptr; // ָ���ÿգ�����Ұָ��
	return ans;
}

// 5�������㡣û��ʲô��ָ����ȡ�
// ���������������ͷ�ڵ� headA �� headB �������ҳ������������������ཻ����ʼ�ڵ㡣
// �����������û�н��㣬���� null ��

// ����˵������������������ڵ��ָ�롣 
// �ر�ע�⣬���㲻����ֵ��ȣ�����ָ����ȡ�
// ���� [4,2,1,3,5] �� [3,3,2,1,3,5] �Ľ����� 1�������� 2

// ����˼·�������������ĳ��ȲȻ����������ĩβ���룬
// ����ľ���������������� A ����Ϊ 5������ B ����Ϊ 3��
// �������� headA��headB ����ָ��ֱ�ָ�� A��B ����ĵ�һ����㣬
// ��Ϊ���ߵĳ��Ȳ��� 2 �����Խ��ϳ����� A �� headA �ƶ� 2 ��λ�ã����ﵹ��������λ�ã�
// ��ʱ�����������ĩβ���롣
// ĩβ��������αȽ�ָ���Ƿ���ȣ�������ҵ����㣬���������ָ��ͬʱ�ƶ�һ��λ�á�
// �Ƚ���֮��û�н����򷵻� nullptr
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
{
	// ָ�����������һ������ָ��
	ListNode* curA = headA;
	ListNode* curB = headB;

	// �洢����������
	int lenA = 0;
	int lenB = 0;

	// ������������
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
	// lenA ����ϳ�����ĳ��ȣ�lenB ���ǽ϶�����
	// curA ָ��ϳ�����ĵ�һ����㣬curB ָ��϶�����
	if (lenA < lenB)
	{
		swap(lenA, lenB);
		swap(headA, headB);
	}

	// ���㳤�Ȳ���ƶ�ָ��ϳ������һ������ָ�� gap ��λ�ã���ĩβ����
	int gap = lenA - lenB;
	while (gap--)
		curA = curA->next;

	while (curA)
	{
		// ����ǲ��ǽ��㡣����ǽ��㣬���Ӧ��ָ����ȣ���ô������ָ��Ҳ�����
		if (curA == curB)
			return curA;

		// ��ָ��ͬʱ�ƶ�һ��
		curA = curA->next;
		curB = curB->next;
	}
	return nullptr; // û�н���
}

// 6���ж������Ƿ��л���������򷵻ؿ�ʼ�뻷�ĵ�һ�����
// ���⣺ ����һ�������л��򷵻�����ʼ�뻷�ĵ�һ���ڵ㡣 ��������޻����򷵻� null��
// Ϊ�˱�ʾ���������еĻ���ʹ������ pos ����ʾ����β���ӵ������е�λ�ã������� 0 ��ʼ����
// ��� pos �� - 1�����ڸ�������û�л���
// ˵�����������޸ĸ���������

// �ⷨ 1��˫ָ��(�졢��ָ��)
// ���� slow �� fast ����ָ�룬��������ĵ�һ����㿪ʼ�ƶ���
// ֻ�� slow ÿ���ƶ�һ���� fast ÿ���ƶ���������� fast ׷�� slow ����˵���л���
// ���������ҵ�������ڣ���Ҫһ����ѧ����

ListNode* cycleLinkListEntrance(ListNode* head)
{
	ListNode* slow = head;
	ListNode* fast = head;

	// ��Ϊ��ָ��һ�������������������һ�����ܵ���ֱ�ӵ������һ������ nullptr
	// ���û�е���������λ�ã�˵���л�
	while (fast != nullptr || fast->next != nullptr)
	{
		slow = slow->next; // ��ָ���ƶ�һ��
		fast = fast->next->next; // ��ָ���ƶ�����

		// ����ָ����������ʱ�� head �� �����㣬ͬʱ����ֱ������
		if (slow == fast)
		{
			// ����������˼�� index1 �ӻ�����ڿ�ʼ�ƶ���index2 �ӵ�һ����㿪ʼ�ƶ�
			// �� index1 ���Ż�һȦ�ص�������ڣ�index2 Ҳ�պ��ߵ��������
			// index1 �� n Ȧ�������һȦ���ƣ�ֻ���Ƶ�Ȧ������
			ListNode* index1 = fast;
			ListNode* index2 = head;
			while (index1 != index2)
			{
				index1 = index1->next;
				index2 = index2->next;
			}
			return index2; // ������ڽ��
		}
	}
	return nullptr;
}

// 7������֮�ͣ�ȥ�ز���û̫��
// ����һ������ n ������������ nums���ж� nums ���Ƿ��������Ԫ�� a��b��c ��
// ʹ�� a + b + c = 0 �������ҳ��������������Ҳ��ظ�����Ԫ�顣
// ע�⣺ ���в����԰����ظ�����Ԫ�顣��˼��ÿ��������������ϲ�����ͬ

vector<vector<int>>thrSum(vector<int>& nums)
{
	vector<vector<int>>result;
	sort(nums.begin(), nums.end());

	for (int i = 0; i < nums.size(); ++i)
	{
		if (nums[i] > 0)
			return result;

		// �� nums[i] ȥ�ء���Ϊ����������������ȵ�Ԫ�ر�Ȼ����
		// ��ʱ������ǰѭ����������һ��ѭ�������ⲻͬ������еĵ�һ��Ԫ�� nums[i] ��ͬ
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
				
				// �� nums[left] �� nums[right] ȥ��
				while (left < right && nums[left] == nums[left + 1])
					++left;
				while (left < right && nums[right] == nums[right - 1])
					--right;

				// ����з�����������ϣ�ͬʱ���� left �� right
				++left;
				--right;
			}
		}
	}
	return result;
}

// 8������֮�ͣ�����ȥ��û̫��
//���⣺����һ������ n ������������ nums ��һ��Ŀ��ֵ target��
//�ж� nums ���Ƿ�����ĸ�Ԫ�� a��b��c �� d ��
//ʹ�� a + b + c + d ��ֵ�� target ��ȣ��ҳ��������������Ҳ��ظ�����Ԫ�顣
//ע�⣺���в����԰����ظ�����Ԫ�顣

// ���˼·��������֮�����ƣ�ֻ���������Ƕ��һ��ѭ��
vector<vector<int>>fourNSum(vector<int>& nums,int target)
{
	vector<vector<int>>result; // �洢���ܵ����
	sort(nums.begin(), nums.end()); // ����
	
	for (int i = 0; i < nums.size(); ++i) // ��һ��ѭ��
	{
		// ��֦�������ĵ�һ�����ʹ��� target���Һ���������ڵ��� 0�������з������������
		if (nums[i] > target && nums[i + 1] >= 0) 
			break;
		
		// �� nums[i] ȥ�ء���Ϊ����������������ȵ�Ԫ�ر�Ȼ����
		// ��ʱ������ǰѭ����������һ��ѭ�������ⲻͬ������еĵ�һ��Ԫ�� nums[i] ��ͬ
		if (i > 0 && nums[i] == nums[i - 1])
			continue;
		for (int j = i + 1; j < nums.size(); ++j) // �ڶ���ѭ��
		{
			// ��֦
			if (nums[i] + nums[j] > target && nums[j + 1] >= 0)
				break;

			// �� nums[j] ȥ�ء���Ϊ����������������ȵ�Ԫ�ر�Ȼ����
			// ��ʱ������ǰѭ����������һ��ѭ�������ⲻͬ������еĵڶ���Ԫ�� nums[j] ��ͬ
			if (j > i + 1 && nums[j] == nums[j - 1]) 
				continue;

			// ��������ָ��
			int left = j + 1;
			int right = nums.size() - 1;
			while (left < right)
			{
				// �����������С�� target��������Ҫ�������� left ����
				if ((nums[i] + nums[j] + nums[left] + nums[right]) < target)
					++left;
				// ����������ʹ��� target��������Ҫ��С������ right ����
				else if ((nums[i] + nums[j] + nums[left] + nums[right]) > target)
					--right;
				else
				{
					// �ҵ��������������
					result.push_back(vector<int>{nums[i], nums[j], nums[left], nums[right]});
					// �� nums[left] ȥ��
					while (left < right && nums[left] == nums[left + 1])
						++left;
					// �� nums[right] ȥ��
					while (left < right && nums[right] == nums[right - 1])
						--right;
					// �ҵ�������������Ͼ�ͬʱ���� left �� right
					++left;
					--right;
				}
			}
		}
	}
	return result;
}
