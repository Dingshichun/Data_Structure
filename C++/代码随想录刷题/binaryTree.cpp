#include"head.h"

// (һ) �������ı���

// 1���������ĵݹ����
// �ݹ���Ҫ�أ�
// (1)ȷ���ݹ麯���Ĳ����ͷ���ֵ�� 
// ȷ����Щ�����ǵݹ�Ĺ�������Ҫ����ģ���ô���ڵݹ麯���������������� ���һ�Ҫ��ȷÿ�εݹ�ķ���ֵ��ʲô����ȷ���ݹ麯���ķ������͡�

// (2)ȷ����ֹ������ д���˵ݹ��㷨, ���е�ʱ�򣬾���������ջ����Ĵ���
// ����ûд��ֹ����������ֹ����д�Ĳ��ԣ�����ϵͳҲ����һ��ջ�Ľṹ������ÿһ��ݹ����Ϣ��
// ����ݹ�û����ֹ������ϵͳ���ڴ�ջ��Ȼ�ͻ������

// (3)ȷ������ݹ���߼��� ȷ��ÿһ��ݹ���Ҫ�������Ϣ��
// ������Ҳ�ͻ��ظ������Լ���ʵ�ֵݹ�Ĺ��̡�


// ��ǰ�����Ϊ����
// (1)ȷ���ݹ麯���Ĳ����ͷ���ֵ
// ��ΪҪ��ӡ������ֵ�����Բ�����Ҫ���� vector ����Ž�����ֵ����������������
// Ҳ���÷���ֵ�����Է��� void��
// ���Ժ����������£�void traversal(treeNode*cur, vector<int>& result)

// (2)ȷ����ֹ����
// �����ǰ�����Ľ��Ϊ�գ���ô�ݹ�ͽ���
// ��: if(cur == nullptr) return;

// (3)ȷ������ݹ���߼�
// ǰ������Ǹ������ҵ�˳�����Եݹ�ʱҪ��ȡ������ֵ��
/*
	result.push_back(cur-val);
	traversal(cur->left,result);
	traversal(cur->right,result);
*/

// ǰ����������������£�
// ǰ������ĵ���ݹ麯�� 
void preTraversal(treeNode* cur, vector<int>&result)
{
	if (cur == nullptr)return;
	result.push_back(cur->val);
	preTraversal(cur->left, result);
	preTraversal(cur->right, result);
}

// ǰ�����һ�Ŷ������ĺ��� 
vector<int>preorderTraversal11(treeNode* root)
{
	vector<int>result;
	preTraversal(root, result);
	return result;
}

// ��������ĵ���ݹ麯�� 
void inorderTraversal(treeNode* cur, vector<int>result)
{
	if (cur == nullptr)return;
	inorderTraversal(cur->left, result);
	result.push_back(cur->val);
	inorderTraversal(cur->right, result);
}

// ��������ĵ���ݹ麯�� 
void posterderTraversal(treeNode* cur, vector<int>result)
{
	if (cur == nullptr)return;
	posterderTraversal(cur->left, result);
	posterderTraversal(cur->right, result);
	result.push_back(cur->val);
}

// 2����������ͳһ������������

// ʹ��ջ���������Ļ����޷�ͬʱ������ʽڵ㣨�����ڵ㣩�ʹ���ڵ㣨��Ԫ�طŽ����������һ�µ������
// �����Ǿͽ����ʵĽڵ����ջ�У���Ҫ����Ľڵ�Ҳ����ջ�е���Ҫ����ǡ�
// ��α���أ�����Ҫ����Ľڵ����ջ֮�󣬽����ŷ���һ����ָ����Ϊ��ǡ� 
// ���ַ���Ҳ���Խ�����Ƿ���

// �������������
vector<int>inorderTraversal(treeNode* root)
{
	vector<int>result;
	stack<treeNode*>stk;

	if (root)stk.push(root);
	while (!stk.empty())
	{
		treeNode* node = stk.top();
		if (node)
		{
			stk.pop(); // ���ý�㵯���������ظ��������ٽ��ҡ�����������ӵ�ջ��
			if (node->right)stk.push(node->right);//����ҽ�㣬�ս�㲻��ջ
			
			stk.push(node); //��Ӹ����
			stk.push(nullptr); // �������ʹ�������û�д�������ս����Ϊ���
			if (node->left)stk.push(node->left);//������㣬�ս�㲻��ջ
		}
		else // ֻ�������ս�㣬�Ž���һ������������
		{
			stk.pop(); //���ս�㵯��
			node = stk.top(); //����ȡ��ջ��Ԫ��
			stk.pop();
			result.push_back(node->val); //���뵽�����
		}
	}
	return result;
}

// ������ǰ�����
vector<int> preorderTraversal(treeNode* root) 
{
		vector<int> result;
		stack<treeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) 
		{
			treeNode* node = st.top();
			if (node != NULL) 
			{
				st.pop();
				if (node->right) st.push(node->right);  // ��
				if (node->left) st.push(node->left);    // ��
				st.push(node);                          // ��
				st.push(NULL);
			}
			else 
			{
				st.pop();
				node = st.top();
				st.pop();
				result.push_back(node->val);
			}
		}
		return result;
}

// �������������
vector<int> postorderTraversal(treeNode* root) 
{
		vector<int> result;
		stack<treeNode*> st;
		if (root != NULL) st.push(root);
		while (!st.empty()) 
		{
			treeNode* node = st.top();
			if (node != NULL) 
			{
				st.pop();
				st.push(node);                          // ��
				st.push(NULL);

				if (node->right) st.push(node->right);  // ��
				if (node->left) st.push(node->left);    // ��

			}
			else 
			{
				st.pop();
				node = st.top();
				st.pop();
				result.push_back(node->val);
			}
		}
		return result;
}

// 3���������Ĳ�����������������
// ��Ҫ����һ���������ݽṹ��������ʵ�֣������Ƚ��ȳ�������һ��һ��������߼���
// ����ջ�Ƚ�����ʺ�ģ��������ȱ���Ҳ���ǵݹ���߼���
// �����ֲ��������ʽ����ͼ���еĹ�����ȱ�����ֻ��������Ӧ���ڶ������ϡ�

vector<vector<int>>levelOrder(treeNode* root)
{
	queue<treeNode*>que; // ���������������ڱ����������Ľ��
	if (root)que.push(root); // �������ӵ�������
	vector<vector<int>>result; // ��������һ��һ��ش洢�� result
	while (!que.empty())
	{
		int size = que.size();
		vector<int>vec; // �洢������ÿһ�����
		// ����һ��Ҫʹ�ù̶���С size����Ҫʹ�� que.size()����Ϊ que.size() �ǲ��ϱ仯��
		for (int i = 0; i < size; ++i)
		{
			treeNode* node = que.front(); // ��ȡ���е�ͷԪ��
			que.pop(); // ����һ��Ԫ��
			vec.push_back(node->val); // ��ȡ����Ӧ��ֵ
			if (node->left)que.push(node->left); // ���������ӽ����ӵ�����
			if (node->right)que.push(node->right);
		}
		result.push_back(vec); // ��¼һ��Ľ��
	}
	return result; // ���ذ����ŵĽ����
}

// 3����ת�����������õݹ�

treeNode* invertTree(treeNode* root)
{
	if (root == nullptr)return root;
	swap(root->left, root->right); // �����������ҽ����н�����ʵ�����ǽ���������������
	invertTree(root->left); // �ݹ齻�����������������ҽ��
	invertTree(root->right); // �ݹ齻�����������������ҽ��
	return root; 
}

// 4���Գƶ��������ж�һ�Ŷ������Ƿ�Գơ�
// �ж϶������Ƿ�Գƣ�Ҫ����Աȵ�����������㣬
// ���ǶԱ����ҽ�㣬���ǶԱ������������ڲ������Ƿ���ȡ�

// �ݹ鷽��
class binaryTree4 
{
public:
	// Ҫ�Ƚϵ��Ǹ��ڵ�����������Ƿ����໥��ת�ģ������ж�������ǲ��ǶԳ�����
	// ����Ҫ�Ƚϵ�����������������ȻҲ���������ڵ���������ڵ㡣
	bool compare(treeNode* left, treeNode* right) 
	{
		// �����ų��սڵ�����
		if (left == nullptr && right != nullptr) return false;
		else if (left != nullptr && right == nullptr) return false;
		else if (left == nullptr && right == nullptr) return true;
		
		// �ų��˿սڵ㣬���ų���ֵ����ͬ�����
		else if (left->val != right->val) return false;

		// ��ʱ���ǣ����ҽڵ㶼��Ϊ�գ�����ֵ��ͬ�����
		// ��ʱ�����ݹ飬����һ����ж�
		bool outside = compare(left->left, right->right);   // ���������� ����������
		bool inside = compare(left->right, right->left);    // ���������ҡ� ����������
		bool isSame = outside && inside;                    // ���������С� ���������� ���߼�����
		return isSame;
	}

	// �ж��Ƿ�Գ�
	bool isSymmetric(treeNode* root) 
	{
		if (root == nullptr) return true; // �����Ϊ�գ������Գ�
		return compare(root->left, root->right);
	}


};

// 5���������������ȡ�
// �ݹ顣�õ����������������ȣ�Ȼ��ȡ���ߵ����ֵ +1 ���ɡ�
class binaryTree5_1
{
public:
	int getDepth(treeNode* node)
	{
		if (node == nullptr)return 0; // �ս�����Ϊ 0
		int leftDepth = getDepth(node->left); // ���������
		int rightDepth = getDepth(node->right); // ���������
		int depth = max(leftDepth, rightDepth) + 1; // ��ǰ������
		return depth;
	}
	int maxDepth(treeNode* root)
	{
		return getDepth(root);
	}

	// ����Ĵ�������
	int maxDepth1(treeNode* root)
	{
		if (root == nullptr)return 0;
		return 1 + max(maxDepth1(root->left), maxDepth1(root->right));
	}
};

// �������������ȣ����ò��������ÿ����һ�㣬��� +1��
class binaryTree5_2
{
public:
	int maxDepth(treeNode* root)
	{
		if (root == nullptr)return 0; // �ս�����Ϊ 0
		queue<treeNode*>que; // �ö��д�Ž��
		int depth = 0; // ��¼���
		if (root != nullptr)que.push(root); // ��������
		while (!que.empty()) // ���в�Ϊ�գ����������
		{
			int size = que.size(); // ��ǰ�������
			++depth; // ��� +1
			for (int i = 0; i < size; ++i) // ������ǰ������н��
			{
				treeNode* node = que.front(); // ȡ�����׽��
				que.pop(); // ����
				if (node->left)que.push(node->left); // �������
				if (node->right)que.push(node->right); // �ҽ�����
			}
		}
		return depth; 
	}
};

// n �����������ȡ�Ҳ�����ݹ鷨�͵�������
// ����û�ж��� n ���������Խ�����ע�ͷ������
/*
class binaryTree5_3
{
public:
	// �ݹ鷨
	int maxDepth(treeNode* root)
	{
		if (root == nullptr)return 0;
		int depth = 0;
		for (int i = 0; i < root->children.size(); ++i)
		{
			depth = max(depth, maxDepth(root->children[i]));
		}
		return depth + 1;
	}

	// ������
	int maxDepth1(treeNode* root)
	{
		if (root == nullptr)return 0;
		queue<treeNode*>que;
		int depth = 0;
		if (root != nullptr)que.push(root);
		while (!que.empty())
		{
			int size = que.size();
			++depth;
			for (int i = 0; i < size; ++i)
			{
				treeNode* node = que.front();
				que.pop();
				for (int i = 0; i < node->children.size(); ++i)
				{
					if (node->children[i])que.push(node->children[i]);
				}
			}
		}
		return depth;
	}
};
*/


// 6������������С��ȡ�
// ��С����ǴӸ��ڵ㵽���Ҷ�ӽڵ�����·���ϵĽڵ�������ע����Ҷ�ӽڵ㡣
// ʲô��Ҷ�ӽڵ㣬���Һ��Ӷ�Ϊ�յĽڵ����Ҷ�ӽڵ㣡
class binaryTree6
{
public:
	// �ⷨ 1���ݹ鷨
	int getDepth(treeNode* node)
	{
		if (node == nullptr)return 0; // �ս�����Ϊ 0
		int leftDepth = getDepth(node->left); // ���������
		int rightDepth = getDepth(node->right); // ���������

		// ���������Ϊ�գ���������Ϊ�գ��򷵻�����������С���
		if (node->left == nullptr && node->right != nullptr)return rightDepth + 1;

		// ���������Ϊ�գ���������Ϊ�գ��򷵻�����������С���
		if (node->left != nullptr && node->right == nullptr)return leftDepth + 1;

		// ���������������Ϊ�գ��򷵻�����������С��ȵ���Сֵ
		int depth = 1 + min(leftDepth, rightDepth);
		return depth;
	}

	int minDepth(treeNode* root)
	{
		return getDepth(root);
	}

	// �ݹ鷨�ľ����������
	int minDepth1(treeNode* root)
	{
		if (root == nullptr)return 0;

		// ���������Ϊ�գ���������Ϊ�գ��򷵻�����������С���
		if (root->left == nullptr && root->right != nullptr)return minDepth1(root->right) + 1;

		// ���������Ϊ�գ���������Ϊ�գ��򷵻�����������С���
		if (root->left != nullptr && root->right == nullptr)return minDepth1(root->left) + 1;

		// ���������������Ϊ�գ��򷵻�����������С��ȵ���Сֵ
		return 1 + min(minDepth1(root->left), minDepth(root->right));
	}
	
	// �ⷨ 2��������
	int minDepth2(treeNode* root)
	{
		if (root == nullptr)return 0; // �ս�����Ϊ 0
		queue<treeNode*>que; // ʹ�ö��н��в������
		int depth = 0; // ��¼��С���
		que.push(root); // �����ڵ����
		while (!que.empty()) // ���в�Ϊ��ʱ��ѭ������
		{
			int size = que.size(); // ��ǰ��Ľ�����
			++depth; // ��ȼ� 1
			for (int i = 0; i < size; ++i) // ������ǰ������н��
			{
				treeNode* node = que.front(); // ȡ�����׽��
				que.pop(); // �������׽��
				if (node->left)que.push(node->left); // �����������
				if (node->right)que.push(node->right); // ����������� 

				// �������������Ϊ�գ���˵���ҵ���Ҷ�ӽ�㣬���ص�ǰ���
				if (!node->left && !node->right)return depth;
			}
		}
		return depth; // ������С���
	}
};


// 7����ȫ�������Ľڵ������
class binaryTree7
{
public:
    // �ⷨ 1���ݹ鷨
	int getNum(treeNode* node)
	{
		if (node == nullptr)return 0; // �ս��,���� 0
		int leftNum = getNum(node->left); // ������������
		int rightNum = getNum(node->right); // ������������ 
		int num = leftNum + rightNum + 1; // ��ǰ������
		return num;
	}
	int numTrees(treeNode* root)
	{
		return getNum(root);
	}

	// �ݹ鷨�ľ���
	int numTrees1(treeNode* root)
	{
		if (root == nullptr)return 0; // �ս��,���� 0
		int leftNum = numTrees1(root->left); // ������������
		int rightNum = numTrees1(root->right); // ������������
		int num = leftNum + rightNum + 1; // ��ǰ������
		return num;
	}
	
	// �ⷨ 2��������,�������
	int numTrees2(treeNode* root)
	{
		if (root == nullptr)return 0; // �ս��,���� 0
		queue<treeNode*>que; // ʹ�ö��н��в������
		int count = 0; // ��¼������
		que.push(root); // �����ڵ����
		while (!que.empty()) // ���в�Ϊ��ʱ��ѭ������
		{
			int size = que.size();  // ��ǰ��Ľ�����
			for (int i = 0; i < size; ++i) // ������ǰ������н��
			{
				treeNode* node = que.front(); // ȡ�����׽��
				que.pop(); // �������׽��
				++count; // �������� 1
				if (node->left)que.push(node->left); // �����������
				if (node->right)que.push(node->right); // �����������
			}
		}
		return count;
	}
};

// 8���ж��ǲ���ƽ���������û̫��
// ���ĳ���������������������������������� 1����ô������һ��ƽ���������
class binaryTree8
{
public:
	// �����Ըýڵ�Ϊ���ڵ�Ķ������ĸ߶ȣ��������ƽ����������򷵻� -1
	int getHeight(treeNode* node) {
		if (node == nullptr) {
			return 0;
		}
		int leftHeight = getHeight(node->left);
		if (leftHeight == -1) return -1;
		int rightHeight = getHeight(node->right);
		if (rightHeight == -1) return -1;
		return abs(leftHeight - rightHeight) > 1 ? -1 : 1 + max(leftHeight, rightHeight);
	}
	bool isBalanced(treeNode* root) {
		return getHeight(root) == -1 ? false : true;
	}
};

// 9��������������·��������
class binaryTree9
{
private:

	// ���ݺ���,path ��¼·��,result ��¼���,cur ��¼��ǰ���
	void traversal(treeNode* cur, vector<int>& path, vector<string>& result)
	{
		// ����ǰ���ֵ����·����д�����λ������Ϊ���һ�����ҲҪ���� path
		path.push_back(cur->val); 

		// �����ǰ�����Ҷ�ӽ�㣬��·����������Ҷ�ӽ�����ҽ�㶼Ϊ��
		if (cur->left == nullptr && cur->right == nullptr)
		{
			string sPath; // ��·��תΪ�ַ����洢�� sPath
			for (int i = 0; i < path.size() - 1; ++i) // ���һ����㲻�Ӽ�ͷ
			{
				sPath += to_string(path[i]); // ��·��תΪ�ַ���
				sPath += "->"; // �Ӽ�ͷ
			}
			sPath += to_string(path[path.size() - 1]); // ���һ����㲻�Ӽ�ͷ
			result.push_back(sPath); // ��·�������� 
			return;
		}
		if (cur->left) 
		{
			traversal(cur->left, path, result); // ��
			path.pop_back(); // ����
		}
		if (cur->right)
		{
			traversal(cur->right, path, result); // ��
			path.pop_back(); // ����
		}
	}
public:
	vector<string> binaryTreePaths(treeNode* root)
	{
		vector<string>result;
		vector<int>path;
		if (root == nullptr)return result;
		traversal(root, path, result);
		return result;
	}
};

// 10����������������Ҷ�ӽ��ĺ͡��е�û����
// ���һ���������㲻Ϊ�գ�������û�����ҽ�㣬��ô�����������Ҷ�ӽ�㡣
class binaryTree10
{
public:
	int sumOfLeftLeaves(treeNode* root)
	{
		if (root == nullptr)return 0; // ��������Ϊ�գ��򷵻� 0
		
		// ��������û�����ҽ�㣬�򷵻� 0
		if (root->left == nullptr && root->right == nullptr)return 0; 
		
		int leftVal = sumOfLeftLeaves(root->left); // ��

		// ������㲻Ϊ�գ�������û�����ҽ�㣬�������ֵ������
		if (root->left && root->left->left == nullptr && root->left->right == nullptr)
			leftVal = root->left->val;
		int rightVal = sumOfLeftLeaves(root->right); // ��
		int sum= leftVal + rightVal; // ��
		return sum; 
	}

	// ����棬û̫��
	int sumOfLeftLeaves2(treeNode* root)
	{
		if (root == nullptr)return 0; // ��������Ϊ�գ��򷵻� 0
		int leftVal = 0; // ��

        // ������㲻Ϊ�գ�������û�����ҽ�㣬�������ֵ������
		if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr)
			leftVal = root->left->val;
		
		// �� + ��
		return leftVal + sumOfLeftLeaves2(root->left) + sumOfLeftLeaves2(root->right);
	}
};

// 11������һ�������������������һ���ҵ�����ߵ�ֵ��
// �����ԣ���������ܺ��ʣ���¼���һ�еĵ�һ����㼴�ɡ�
class binaryTree11
{
public:
	int findBottomLeftValue(treeNode* root)
	{
		queue<treeNode*>que;
		if (root != nullptr)que.push(root);
		int val = 0;
		while (!que.empty())
		{
			int size = que.size();
			for (int i = 0; i < size; ++i)
			{
				treeNode* node = que.front();
				que.pop();

				// ��¼���һ�еĵ�һ����㣬ÿһ�㶼����¸�ֵ��ֱ�����һ�㡣
				if (i == 0)val = node->val; 

				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);
			}
		}
		return val;
	}
};

// 12������һ����������һ��Ŀ��ͣ��жϸ������Ƿ���ڸ��ڵ㵽Ҷ�ӽڵ��·����
// ����·�������нڵ�ֵ��ӵ���Ŀ��͡�

// ˼·�������Կ������û��ݡ�
// �ݹ麯���Ĳ���Ϊ����ǰ��㣬Ŀ��͡�
// �ݹ麯���ķ���ֵ���Ƿ����������·����
// �ݹ麯������ֹ�����������ǰ���ΪҶ�ӽ�㣬��·���ܺͲ������������򷵻� false��
// ÿ�α���һ����㣬�ͽ�Ŀ��ͼ�ȥ��ǰ����ֵ��������� 0 �ҵ�ǰ���ΪҶ�ӽ�㣬�򷵻� true��
// ����ټ��ϵ�ǰ����ֵ�����ݡ�
class binaryTree12
{
private:

	// �ݹ麯��,����Ϊ����ǰ��㣬Ŀ��͡�
	bool backTrack(treeNode* cur, int count)
	{
		// �����ǰ���ΪҶ�ӽ�㣬��·���ܺ������������򷵻� true
		if (cur->left == nullptr && cur->right == nullptr && count == 0)return true;
		
		// �����ǰ���ΪҶ�ӽ�㣬��·���ܺͲ������������򷵻� false
		if (cur->left == nullptr && cur->right == nullptr)return false;

		// ������㲻Ϊ�գ���ݹ��������
		if (cur->left)
		{
			count -= cur->left->val; // ÿ�α���һ����㣬�ͽ�Ŀ��ͼ�ȥ��ǰ����ֵ

			// ����ݹ�������㷵�� true���򷵻� true
			if (backTrack(cur->left, count))return true; 
			count += cur->left->val; // ����ټ��ϵ�ǰ����ֵ������
		}
		if (cur->right)  // ����ҽ�㲻Ϊ�գ���ݹ�����ҽ��
		{
			count -= cur->right->val; // ÿ�α���һ����㣬�ͽ�Ŀ��ͼ�ȥ��ǰ����ֵ

            // ����ݹ�����ҽ�㷵�� true���򷵻� true
			if (backTrack(cur->right, count))return true;
			count += cur->right->val; // ����ټ��ϵ�ǰ����ֵ������
		}
		return false; // ������ҽ�㶼�������������򷵻� false
	}
public:
	bool hasPathSum(treeNode* root, int targetSum) 
	{
		if (root == nullptr)return false; // ��������Ϊ�գ��򷵻� false
		return backTrack(root, targetSum - root->val); // �ݹ���������
	}
};

// 13�������������û̫��
// ����һ��������������������������������
//ע��: ����Լ�������û���ظ���Ԫ�ء�
//���磬����
//������� inorder = [9, 3, 15, 20, 7]
//������� postorder = [9, 15, 7, 20, 3] �������µĶ�������
// ��ÿ������ұ�������[[3],[9,20],[15,7]]

// ����˼·��
//�� ������������һ��Ԫ��Ϊ�и�㣬�����������飬�����������飬���������к������顣
//һ��һ������ȥ��ÿ�κ����������һ��Ԫ�ؾ��ǽڵ�Ԫ�ء�
//����������������ӣ����ݺ��������֪�����Ϊ 3���ٿ�������������飬
// ��֪ 9 �Ǹ������������Ψһ��㣬15,20,7 �Ǹ�����������ϵĽ�㣬
// �ٸ��ݺ�������� 15,7,20 ��˳��ȷ�� 20 �Ǹ�����������ĵ�һ����㣬15 �� 7 �ֱ��� 20 �����ҽ��

//��һ��һ���и��Ӧ���뵽�˵ݹ顣
//����һ��һ���ּ�����
//��һ������������СΪ��Ļ���˵���ǿսڵ��ˡ�
//�ڶ����������Ϊ�գ���ôȡ�����������һ��Ԫ����Ϊ�ڵ�Ԫ�ء�
//���������ҵ������������һ��Ԫ�������������λ�ã���Ϊ�и��
//���Ĳ����и��������飬�г���������������������� ��˳���㷴�ˣ�һ���������������飩
//���岽���и�������飬�гɺ���������ͺ���������
//���������ݹ鴦���������������

class binaryTree13
{
private:
	treeNode* tranversal(vector<int>& inorder, vector<int>& postorder)
	{
		if (postorder.size() == 0)return nullptr; // ��Ϊ��
		int rootValue = postorder[postorder.size() - 1]; // ���ݺ�������ҵ�������ֵ
		treeNode* root = new treeNode(rootValue); // ���������
		if (postorder.size() == 1)return root; // ������ֻ��һ�������

		// �ҵ�����������и�㡣�Ը�������и��������������
		int delimiterIndex;
		for (delimiterIndex = 0; delimiterIndex < inorder.size(); ++delimiterIndex)
		{
			if (inorder[delimiterIndex] == rootValue)
				break;
		}

		// �и��������飬�����ǰ�������ҿ�������
		// ����ҿ����䣺[0, delimiterIndex)
		vector<int>leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
		// [delimiterIndex + 1, end)
		vector<int>rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());

		// �������������ɾ�������������СҪ��С 1
		postorder.resize(postorder.size() - 1);

		// �и��������
		// ��Ȼ����ҿ���ע������ʹ���������������С��Ϊ�и��
		// [0, leftInorder.size)
		vector<int>leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
		// [leftInorder.size(), end)
		vector<int>rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

		// �ݹ�
		root->left = tranversal(leftInorder, leftPostorder);
		root->right = tranversal(rightInorder, rightPostorder);
		return root;
	}
public:
	treeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
	{
		if (inorder.size() == 0 || postorder.size() == 0)return nullptr;
		return tranversal(inorder, postorder);
	}
};

// 14������������������
//����һ�������ظ�Ԫ�ص��������顣һ���Դ����鹹�������������������£�
//�������ĸ��������е����Ԫ�ء�
//��������ͨ�����������ֵ��߲��ֹ����������������
//��������ͨ�����������ֵ�ұ߲��ֹ����������������
//
//ͨ�����������鹹�������������������������ĸ��ڵ㡣

// 15���ϲ�������������
// �����������������������е�һ�����ǵ���һ����ʱ��������������һЩ�ڵ����ص���
// ����Ҫ�����Ǻϲ�Ϊһ���µĶ��������ϲ��Ĺ�������������ڵ��ص���
// ��ô�����ǵ�ֵ�����Ϊ�ڵ�ϲ������ֵ������Ϊ NULL �Ľڵ㽫ֱ����Ϊ�¶������Ľڵ㡣

class binaryTree15
{
public:
	// ʹ�ò���˼·�����ö��У��������������Ľ��������ӣ�Ȼ�����γ��ӣ�����������ֵ��ӣ�
	treeNode* mergeTrees(treeNode* t1, treeNode* t2)
	{
		if (t1 == nullptr)return t2;
		if (t2 == nullptr)return t1;
		queue<treeNode*>que;
		que.push(t1);
		que.push(t2);
		while (!que.empty())
		{
			treeNode* node1 = que.front();
			que.pop();
			treeNode* node2 = que.front(); 
			que.pop();
			node1->val += node2->val;

			if(node1->left && node2->left)
			{
				que.push(node1->left);
				que.push(node2->left);
			}
			if (node1->right && node2->right)
			{
				que.push(node1->right);
				que.push(node2->right);
			}
			if (node1->left == nullptr && node2->left != nullptr)
				node1->left = node2->left;
			if (node1->right == nullptr && node2->right != nullptr)
				node1->right = node2->right;
		}
        return t1;
	}
};

// 16��������������
// ����������������BST���ĸ��ڵ��һ��ֵ�� ����Ҫ��BST���ҵ��ڵ�ֵ���ڸ���ֵ�Ľڵ㡣 
// �����Ըýڵ�Ϊ���������� ����ڵ㲻���ڣ��򷵻� NULL��

class binaryTree16
{
public:
	// �ݹ鷨
	treeNode* searchBST(treeNode* root, int targetVal)
	{
		// ��������Ϊ�ջ��߸�����ֵ����Ŀ��ֵ���򷵻ظ����
		if (root == nullptr || root->val == targetVal)return root;
		treeNode* result = nullptr; // ����һ���������ڴ洢���

		// ���������ֵ����Ŀ��ֵ�������������в���
		if (root->val > targetVal)result = searchBST(root->left, targetVal);
        // ���������ֵС��Ŀ��ֵ�������������в���
		if (root->val < targetVal)result = searchBST(root->right, targetVal);
		return result;

		// Ҳ���Բ�ʹ�ñ������洢�����ֱ�ӷ��أ����£�
		// if(root==nullptr || root->val == targetVal)return root;
		// if(root->val>targetVal)return searchBST(root->left, targetVal);
		// if (root->val < targetVal)return searchBST(root->right, targetVal);
	}

	// ������������������������ģ����Բ���Ҫ�������У�ֱ��ʹ��ѭ�����ɡ�
	treeNode* searchBST2(treeNode* root, int targetVal)
	{
		while (root != nullptr) // �������㲻Ϊ�գ����������
		{
			// ���������ֵ����Ŀ��ֵ���򷵻ظ����
			if (root->val == targetVal)return root; 

			// ���������ֵ����Ŀ��ֵ�������������в��ң��������������в���
			root = root->val > targetVal ? root->left : root->right; 
		}
        return nullptr; // ���û���ҵ����򷵻ؿ�ָ��
	}
};

// 17���ж�һ�ö������ǲ�����Ч�Ķ�����������
// ˼·��
// ��������£�����Ķ����������ڵ����ֵ���������С�
// ����������ԣ���֤���������������൱�ڱ�����ж�һ�������ǲ��ǵ������ˡ�
class binaryTree17
{
private:
	vector<int>vec; // ����һ���������ڴ洢��������Ľ��	
	void inOrder(treeNode* root) 
	{
		if (root == nullptr)return; // ��������Ϊ�գ���ֱ�ӷ���
		inOrder(root->left); // �ݹ����������
		vec.push_back(root->val); // ��������ֵ����������
		inOrder(root->right); // �ݹ����������
	}
public:
	bool isValidBST(treeNode* root) 
	{
		vec.clear(); // �������
		inOrder(root); // �����������������
		for (int i = 1; i < vec.size(); ++i) // �����������ж��Ƿ����
		{
			if (vec[i] <= vec[i - 1])return false;
		}
		return true;
	}
};

// 18������һ�����нڵ�Ϊ�Ǹ�ֵ�Ķ�����������������������������ڵ�Ĳ�ľ���ֵ����Сֵ��
// ��ֱ�۵��뷨�����ǰѶ���������ת�����������飬Ȼ�����һ�����飬��ͳ�Ƴ�����С��ֵ�ˡ�
class binaryTree18
{
private:
	vector<int>vec; // ����һ���������ڴ洢��������Ľ��
	void inOrder(treeNode* root)
	{
		if (root == nullptr)return; // ��������Ϊ�գ���ֱ�ӷ���
		inOrder(root->left); // �ݹ����������
		vec.push_back(root->val); // ��������ֵ����������
		inOrder(root->right); // �ݹ����������
	}
public:
	int getMinimumDifference(treeNode* root) 
	{
		vec.clear(); // �������
		inOrder(root); // �����������������
		if (vec.size() < 2)return 0; // ��������Ĵ�СС��2���򷵻�0
		int result = INT_MAX; // ����һ���������ڴ洢���
		for (int i = 1; i < vec.size(); ++i) // �����������ж��Ƿ����
		{
			result = min(result, vec[i] - vec[i - 1]);
		}
		return result;
	}
};

