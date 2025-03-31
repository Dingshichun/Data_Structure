#include"head.h"

// (一) 二叉树的遍历

// 1、二叉树的递归遍历
// 递归三要素：
// (1)确定递归函数的参数和返回值： 
// 确定哪些参数是递归的过程中需要处理的，那么就在递归函数里加上这个参数， 并且还要明确每次递归的返回值是什么进而确定递归函数的返回类型。

// (2)确定终止条件： 写完了递归算法, 运行的时候，经常会遇到栈溢出的错误，
// 就是没写终止条件或者终止条件写的不对，操作系统也是用一个栈的结构来保存每一层递归的信息，
// 如果递归没有终止，操作系统的内存栈必然就会溢出。

// (3)确定单层递归的逻辑： 确定每一层递归需要处理的信息。
// 在这里也就会重复调用自己来实现递归的过程。


// 以前序遍历为例：
// (1)确定递归函数的参数和返回值
// 因为要打印结点的数值，所以参数中要传入 vector 来存放结点的数值，不用其它操作，
// 也不用返回值，所以返回 void。
// 所以函数类型如下：void traversal(treeNode*cur, vector<int>& result)

// (2)确定终止条件
// 如果当前遍历的结点为空，那么递归就结束
// 即: if(cur == nullptr) return;

// (3)确定单层递归的逻辑
// 前序遍历是根、左、右的顺序，所以递归时要先取根结点的值。
/*
	result.push_back(cur-val);
	traversal(cur->left,result);
	traversal(cur->right,result);
*/

// 前序遍历完整代码如下：
// 前序遍历的单层递归函数 
void preTraversal(treeNode* cur, vector<int>&result)
{
	if (cur == nullptr)return;
	result.push_back(cur->val);
	preTraversal(cur->left, result);
	preTraversal(cur->right, result);
}

// 前序遍历一颗二叉树的函数 
vector<int>preorderTraversal11(treeNode* root)
{
	vector<int>result;
	preTraversal(root, result);
	return result;
}

// 中序遍历的单层递归函数 
void inorderTraversal(treeNode* cur, vector<int>result)
{
	if (cur == nullptr)return;
	inorderTraversal(cur->left, result);
	result.push_back(cur->val);
	inorderTraversal(cur->right, result);
}

// 后序遍历的单层递归函数 
void posterderTraversal(treeNode* cur, vector<int>result)
{
	if (cur == nullptr)return;
	posterderTraversal(cur->left, result);
	posterderTraversal(cur->right, result);
	result.push_back(cur->val);
}

// 2、二叉树的统一迭代遍历方法

// 使用栈迭代遍历的话，无法同时解决访问节点（遍历节点）和处理节点（将元素放进结果集）不一致的情况。
// 那我们就将访问的节点放入栈中，把要处理的节点也放入栈中但是要做标记。
// 如何标记呢，就是要处理的节点放入栈之后，紧接着放入一个空指针作为标记。 
// 这种方法也可以叫做标记法。

// 迭代法中序遍历
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
			stk.pop(); // 将该结点弹出，避免重复操作，再将右、根、左结点添加到栈中
			if (node->right)stk.push(node->right);//添加右结点，空结点不入栈
			
			stk.push(node); //添加根结点
			stk.push(nullptr); // 根结点访问过，但是没有处理，假如空结点作为标记
			if (node->left)stk.push(node->left);//添加左结点，空结点不入栈
		}
		else // 只有遇到空结点，才将下一个结点放入结果集
		{
			stk.pop(); //将空结点弹出
			node = stk.top(); //重新取出栈中元素
			stk.pop();
			result.push_back(node->val); //加入到结果集
		}
	}
	return result;
}

// 迭代法前序遍历
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
				if (node->right) st.push(node->right);  // 右
				if (node->left) st.push(node->left);    // 左
				st.push(node);                          // 中
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

// 迭代法后序遍历
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
				st.push(node);                          // 中
				st.push(NULL);

				if (node->right) st.push(node->right);  // 右
				if (node->left) st.push(node->left);    // 左

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

// 3、二叉数的层序遍历，即按层遍历
// 需要借用一个辅助数据结构即队列来实现，队列先进先出，符合一层一层遍历的逻辑，
// 而用栈先进后出适合模拟深度优先遍历也就是递归的逻辑。
// 而这种层序遍历方式就是图论中的广度优先遍历，只不过我们应用在二叉树上。

vector<vector<int>>levelOrder(treeNode* root)
{
	queue<treeNode*>que; // 创建辅助队列用于遍历二叉树的结点
	if (root)que.push(root); // 根结点添加到队列中
	vector<vector<int>>result; // 将二叉树一层一层地存储到 result
	while (!que.empty())
	{
		int size = que.size();
		vector<int>vec; // 存储二叉树每一层的数
		// 这里一定要使用固定大小 size，不要使用 que.size()，因为 que.size() 是不断变化的
		for (int i = 0; i < size; ++i)
		{
			treeNode* node = que.front(); // 获取队列的头元素
			que.pop(); // 出队一个元素
			vec.push_back(node->val); // 获取结点对应的值
			if (node->left)que.push(node->left); // 将结点的左子结点添加到队列
			if (node->right)que.push(node->right);
		}
		result.push_back(vec); // 记录一层的结果
	}
	return result; // 返回按层存放的结果。
}

// 3、翻转二叉树。利用递归

treeNode* invertTree(treeNode* root)
{
	if (root == nullptr)return root;
	swap(root->left, root->right); // 将根结点的左、右结点进行交换，实际上是将左、右子树交换了
	invertTree(root->left); // 递归交换左子树各结点的左右结点
	invertTree(root->right); // 递归交换右子树各结点的左右结点
	return root; 
}

// 4、对称二叉树。判断一颗二叉树是否对称。
// 判断二叉树是否对称，要清楚对比的是哪两个结点，
// 不是对比左、右结点，而是对比左右子树的内侧和外侧是否相等。

// 递归方法
class binaryTree4 
{
public:
	// 要比较的是根节点的两个子树是否是相互翻转的，进而判断这个树是不是对称树，
	// 所以要比较的是两个树，参数自然也是左子树节点和右子树节点。
	bool compare(treeNode* left, treeNode* right) 
	{
		// 首先排除空节点的情况
		if (left == nullptr && right != nullptr) return false;
		else if (left != nullptr && right == nullptr) return false;
		else if (left == nullptr && right == nullptr) return true;
		
		// 排除了空节点，再排除数值不相同的情况
		else if (left->val != right->val) return false;

		// 此时就是：左右节点都不为空，且数值相同的情况
		// 此时才做递归，做下一层的判断
		bool outside = compare(left->left, right->right);   // 左子树：左、 右子树：右
		bool inside = compare(left->right, right->left);    // 左子树：右、 右子树：左
		bool isSame = outside && inside;                    // 左子树：中、 右子树：中 （逻辑处理）
		return isSame;
	}

	// 判断是否对称
	bool isSymmetric(treeNode* root) 
	{
		if (root == nullptr) return true; // 根结点为空，视作对称
		return compare(root->left, root->right);
	}


};

// 5、二叉树的最大深度。
// 递归。得到左、右子树的最大深度，然后取两者的最大值 +1 即可。
class binaryTree5_1
{
public:
	int getDepth(treeNode* node)
	{
		if (node == nullptr)return 0; // 空结点深度为 0
		int leftDepth = getDepth(node->left); // 左子树深度
		int rightDepth = getDepth(node->right); // 右子树深度
		int depth = max(leftDepth, rightDepth) + 1; // 当前结点深度
		return depth;
	}
	int maxDepth(treeNode* root)
	{
		return getDepth(root);
	}

	// 精简的代码如下
	int maxDepth1(treeNode* root)
	{
		if (root == nullptr)return 0;
		return 1 + max(maxDepth1(root->left), maxDepth1(root->right));
	}
};

// 迭代法求最大深度，利用层序遍历，每遍历一层，深度 +1。
class binaryTree5_2
{
public:
	int maxDepth(treeNode* root)
	{
		if (root == nullptr)return 0; // 空结点深度为 0
		queue<treeNode*>que; // 用队列存放结点
		int depth = 0; // 记录深度
		if (root != nullptr)que.push(root); // 根结点入队
		while (!que.empty()) // 队列不为空，则继续遍历
		{
			int size = que.size(); // 当前层结点个数
			++depth; // 深度 +1
			for (int i = 0; i < size; ++i) // 遍历当前层的所有结点
			{
				treeNode* node = que.front(); // 取出队首结点
				que.pop(); // 出队
				if (node->left)que.push(node->left); // 左结点入队
				if (node->right)que.push(node->right); // 右结点入队
			}
		}
		return depth; 
	}
};

// n 叉树的最大深度。也包括递归法和迭代法。
// 由于没有定义 n 叉树，所以将代码注释放在这里。
/*
class binaryTree5_3
{
public:
	// 递归法
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

	// 迭代法
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


// 6、二叉树的最小深度。
// 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。注意是叶子节点。
// 什么是叶子节点，左右孩子都为空的节点才是叶子节点！
class binaryTree6
{
public:
	// 解法 1：递归法
	int getDepth(treeNode* node)
	{
		if (node == nullptr)return 0; // 空结点深度为 0
		int leftDepth = getDepth(node->left); // 左子树深度
		int rightDepth = getDepth(node->right); // 右子树深度

		// 如果左子树为空，右子树不为空，则返回右子树的最小深度
		if (node->left == nullptr && node->right != nullptr)return rightDepth + 1;

		// 如果右子树为空，左子树不为空，则返回左子树的最小深度
		if (node->left != nullptr && node->right == nullptr)return leftDepth + 1;

		// 如果左右子树都不为空，则返回左右子树最小深度的最小值
		int depth = 1 + min(leftDepth, rightDepth);
		return depth;
	}

	int minDepth(treeNode* root)
	{
		return getDepth(root);
	}

	// 递归法的精简代码如下
	int minDepth1(treeNode* root)
	{
		if (root == nullptr)return 0;

		// 如果左子树为空，右子树不为空，则返回右子树的最小深度
		if (root->left == nullptr && root->right != nullptr)return minDepth1(root->right) + 1;

		// 如果右子树为空，左子树不为空，则返回左子树的最小深度
		if (root->left != nullptr && root->right == nullptr)return minDepth1(root->left) + 1;

		// 如果左右子树都不为空，则返回左右子树最小深度的最小值
		return 1 + min(minDepth1(root->left), minDepth(root->right));
	}
	
	// 解法 2：迭代法
	int minDepth2(treeNode* root)
	{
		if (root == nullptr)return 0; // 空结点深度为 0
		queue<treeNode*>que; // 使用队列进行层序遍历
		int depth = 0; // 记录最小深度
		que.push(root); // 将根节点入队
		while (!que.empty()) // 队列不为空时，循环遍历
		{
			int size = que.size(); // 当前层的结点个数
			++depth; // 深度加 1
			for (int i = 0; i < size; ++i) // 遍历当前层的所有结点
			{
				treeNode* node = que.front(); // 取出队首结点
				que.pop(); // 弹出队首结点
				if (node->left)que.push(node->left); // 将左子树入队
				if (node->right)que.push(node->right); // 将右子树入队 

				// 如果左右子树都为空，则说明找到了叶子结点，返回当前深度
				if (!node->left && !node->right)return depth;
			}
		}
		return depth; // 返回最小深度
	}
};


// 7、完全二叉树的节点个数。
class binaryTree7
{
public:
    // 解法 1：递归法
	int getNum(treeNode* node)
	{
		if (node == nullptr)return 0; // 空结点,个数 0
		int leftNum = getNum(node->left); // 左子树结点个数
		int rightNum = getNum(node->right); // 右子树结点个数 
		int num = leftNum + rightNum + 1; // 当前结点个数
		return num;
	}
	int numTrees(treeNode* root)
	{
		return getNum(root);
	}

	// 递归法的精简
	int numTrees1(treeNode* root)
	{
		if (root == nullptr)return 0; // 空结点,个数 0
		int leftNum = numTrees1(root->left); // 左子树结点个数
		int rightNum = numTrees1(root->right); // 右子树结点个数
		int num = leftNum + rightNum + 1; // 当前结点个数
		return num;
	}
	
	// 解法 2：迭代法,按层遍历
	int numTrees2(treeNode* root)
	{
		if (root == nullptr)return 0; // 空结点,个数 0
		queue<treeNode*>que; // 使用队列进行层序遍历
		int count = 0; // 记录结点个数
		que.push(root); // 将根节点入队
		while (!que.empty()) // 队列不为空时，循环遍历
		{
			int size = que.size();  // 当前层的结点个数
			for (int i = 0; i < size; ++i) // 遍历当前层的所有结点
			{
				treeNode* node = que.front(); // 取出队首结点
				que.pop(); // 弹出队首结点
				++count; // 结点个数加 1
				if (node->left)que.push(node->left); // 将左子树入队
				if (node->right)que.push(node->right); // 将右子树入队
			}
		}
		return count;
	}
};

// 8、判断是不是平衡二叉树。没太懂
// 如果某二叉树中任意结点的左右子树的深度相差不超过 1，那么它就是一棵平衡二叉树。
class binaryTree8
{
public:
	// 返回以该节点为根节点的二叉树的高度，如果不是平衡二叉树了则返回 -1
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

// 9、二叉树的所有路径。回溯
class binaryTree9
{
private:

	// 回溯函数,path 记录路径,result 记录结果,cur 记录当前结点
	void traversal(treeNode* cur, vector<int>& path, vector<string>& result)
	{
		// 将当前结点值加入路径，写在这个位置是因为最后一个结点也要加入 path
		path.push_back(cur->val); 

		// 如果当前结点是叶子结点，则将路径加入结果。叶子结点左右结点都为空
		if (cur->left == nullptr && cur->right == nullptr)
		{
			string sPath; // 将路径转为字符串存储到 sPath
			for (int i = 0; i < path.size() - 1; ++i) // 最后一个结点不加箭头
			{
				sPath += to_string(path[i]); // 将路径转为字符串
				sPath += "->"; // 加箭头
			}
			sPath += to_string(path[path.size() - 1]); // 最后一个结点不加箭头
			result.push_back(sPath); // 将路径加入结果 
			return;
		}
		if (cur->left) 
		{
			traversal(cur->left, path, result); // 左
			path.pop_back(); // 回溯
		}
		if (cur->right)
		{
			traversal(cur->right, path, result); // 右
			path.pop_back(); // 回溯
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

// 10、二叉树中所有左叶子结点的和。有点没看懂
// 如果一个结点的左结点不为空，且左结点没有左右结点，那么这个结点就是左叶子结点。
class binaryTree10
{
public:
	int sumOfLeftLeaves(treeNode* root)
	{
		if (root == nullptr)return 0; // 如果根结点为空，则返回 0
		
		// 如果根结点没有左右结点，则返回 0
		if (root->left == nullptr && root->right == nullptr)return 0; 
		
		int leftVal = sumOfLeftLeaves(root->left); // 左

		// 如果左结点不为空，且左结点没有左右结点，则将左结点的值加入结果
		if (root->left && root->left->left == nullptr && root->left->right == nullptr)
			leftVal = root->left->val;
		int rightVal = sumOfLeftLeaves(root->right); // 右
		int sum= leftVal + rightVal; // 中
		return sum; 
	}

	// 精简版，没太懂
	int sumOfLeftLeaves2(treeNode* root)
	{
		if (root == nullptr)return 0; // 如果根结点为空，则返回 0
		int leftVal = 0; // 左

        // 如果左结点不为空，且左结点没有左右结点，则将左结点的值加入结果
		if (root->left != nullptr && root->left->left == nullptr && root->left->right == nullptr)
			leftVal = root->left->val;
		
		// 左 + 右
		return leftVal + sumOfLeftLeaves2(root->left) + sumOfLeftLeaves2(root->right);
	}
};

// 11、给定一个二叉树，在树的最后一行找到最左边的值。
// 很明显，层序遍历很合适，记录最后一行的第一个结点即可。
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

				// 记录最后一行的第一个结点，每一层都会更新该值，直到最后一层。
				if (i == 0)val = node->val; 

				if (node->left)que.push(node->left);
				if (node->right)que.push(node->right);
			}
		}
		return val;
	}
};

// 12、给定一个二叉树和一个目标和，判断该树中是否存在根节点到叶子节点的路径，
// 这条路径上所有节点值相加等于目标和。

// 思路：很明显可以利用回溯。
// 递归函数的参数为：当前结点，目标和。
// 递归函数的返回值：是否存在这样的路径。
// 递归函数的终止条件：如果当前结点为叶子结点，且路径总和不满足条件，则返回 false；
// 每次遍历一个结点，就将目标和减去当前结点的值，如果减到 0 且当前结点为叶子结点，则返回 true。
// 最后再加上当前结点的值，回溯。
class binaryTree12
{
private:

	// 递归函数,参数为：当前结点，目标和。
	bool backTrack(treeNode* cur, int count)
	{
		// 如果当前结点为叶子结点，且路径总和满足条件，则返回 true
		if (cur->left == nullptr && cur->right == nullptr && count == 0)return true;
		
		// 如果当前结点为叶子结点，且路径总和不满足条件，则返回 false
		if (cur->left == nullptr && cur->right == nullptr)return false;

		// 如果左结点不为空，则递归遍历左结点
		if (cur->left)
		{
			count -= cur->left->val; // 每次遍历一个结点，就将目标和减去当前结点的值

			// 如果递归遍历左结点返回 true，则返回 true
			if (backTrack(cur->left, count))return true; 
			count += cur->left->val; // 最后再加上当前结点的值，回溯
		}
		if (cur->right)  // 如果右结点不为空，则递归遍历右结点
		{
			count -= cur->right->val; // 每次遍历一个结点，就将目标和减去当前结点的值

            // 如果递归遍历右结点返回 true，则返回 true
			if (backTrack(cur->right, count))return true;
			count += cur->right->val; // 最后再加上当前结点的值，回溯
		}
		return false; // 如果左右结点都不满足条件，则返回 false
	}
public:
	bool hasPathSum(treeNode* root, int targetSum) 
	{
		if (root == nullptr)return false; // 如果根结点为空，则返回 false
		return backTrack(root, targetSum - root->val); // 递归遍历根结点
	}
};

// 13、构造二叉树。没太懂
// 根据一棵树的中序遍历与后序遍历构造二叉树。
//注意: 你可以假设树中没有重复的元素。
//例如，给出
//中序遍历 inorder = [9, 3, 15, 20, 7]
//后序遍历 postorder = [9, 15, 7, 20, 3] 返回如下的二叉树：
// 按每层从左到右遍历就是[[3],[9,20],[15,7]]

// 解题思路：
//以 后序数组的最后一个元素为切割点，先切中序数组，根据中序数组，反过来再切后序数组。
//一层一层切下去，每次后序数组最后一个元素就是节点元素。
//比如上面给出的例子，根据后序遍历可知根结点为 3，再看中序遍历的数组，
// 可知 9 是根结点左子树的唯一结点，15,20,7 是根结点右子树上的结点，
// 再根据后序遍历中 15,7,20 的顺序，确定 20 是根结点右子树的第一个结点，15 和 7 分别是 20 的左、右结点

//到一层一层切割，就应该想到了递归。
//来看一下一共分几步：
//第一步：如果数组大小为零的话，说明是空节点了。
//第二步：如果不为空，那么取后序数组最后一个元素作为节点元素。
//第三步：找到后序数组最后一个元素在中序数组的位置，作为切割点
//第四步：切割中序数组，切成中序左数组和中序右数组 （顺序别搞反了，一定是先切中序数组）
//第五步：切割后序数组，切成后序左数组和后序右数组
//第六步：递归处理左区间和右区间

class binaryTree13
{
private:
	treeNode* tranversal(vector<int>& inorder, vector<int>& postorder)
	{
		if (postorder.size() == 0)return nullptr; // 树为空
		int rootValue = postorder[postorder.size() - 1]; // 根据后序遍历找到根结点的值
		treeNode* root = new treeNode(rootValue); // 创建根结点
		if (postorder.size() == 1)return root; // 二叉树只有一个根结点

		// 找到中序遍历的切割点。以根结点来切割中序遍历的数组
		int delimiterIndex;
		for (delimiterIndex = 0; delimiterIndex < inorder.size(); ++delimiterIndex)
		{
			if (inorder[delimiterIndex] == rootValue)
				break;
		}

		// 切割中序数组，这里是按照左闭右开来划分
		// 左闭右开区间：[0, delimiterIndex)
		vector<int>leftInorder(inorder.begin(), inorder.begin() + delimiterIndex);
		// [delimiterIndex + 1, end)
		vector<int>rightInorder(inorder.begin() + delimiterIndex + 1, inorder.end());

		// 后序遍历的数组删除根结点后，数组大小要减小 1
		postorder.resize(postorder.size() - 1);

		// 切割后序数组
		// 依然左闭右开，注意这里使用了左中序数组大小作为切割点
		// [0, leftInorder.size)
		vector<int>leftPostorder(postorder.begin(), postorder.begin() + leftInorder.size());
		// [leftInorder.size(), end)
		vector<int>rightPostorder(postorder.begin() + leftInorder.size(), postorder.end());

		// 递归
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

// 14、最大二叉树。待补充
//给定一个不含重复元素的整数数组。一个以此数组构建的最大二叉树定义如下：
//二叉树的根是数组中的最大元素。
//左子树是通过数组中最大值左边部分构造出的最大二叉树。
//右子树是通过数组中最大值右边部分构造出的最大二叉树。
//
//通过给定的数组构建最大二叉树，并且输出这个树的根节点。

// 15、合并两个二叉树。
// 给定两个二叉树，将它们中的一个覆盖到另一个上时，两个二叉树的一些节点便会重叠。
// 你需要将他们合并为一个新的二叉树。合并的规则是如果两个节点重叠，
// 那么将他们的值相加作为节点合并后的新值，否则不为 NULL 的节点将直接作为新二叉树的节点。

class binaryTree15
{
public:
	// 使用层序思路：利用队列，将两个二叉树的结点依次入队，然后依次出队，将两个结点的值相加，
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

// 16、二叉搜索树。
// 给定二叉搜索树（BST）的根节点和一个值。 你需要在BST中找到节点值等于给定值的节点。 
// 返回以该节点为根的子树。 如果节点不存在，则返回 NULL。

class binaryTree16
{
public:
	// 递归法
	treeNode* searchBST(treeNode* root, int targetVal)
	{
		// 如果根结点为空或者根结点的值等于目标值，则返回根结点
		if (root == nullptr || root->val == targetVal)return root;
		treeNode* result = nullptr; // 定义一个变量用于存储结果

		// 如果根结点的值大于目标值，则在左子树中查找
		if (root->val > targetVal)result = searchBST(root->left, targetVal);
        // 如果根结点的值小于目标值，则在右子树中查找
		if (root->val < targetVal)result = searchBST(root->right, targetVal);
		return result;

		// 也可以不使用变量来存储结果，直接返回，如下：
		// if(root==nullptr || root->val == targetVal)return root;
		// if(root->val>targetVal)return searchBST(root->left, targetVal);
		// if (root->val < targetVal)return searchBST(root->right, targetVal);
	}

	// 迭代法。二叉搜索树是有序的，所以不需要借助队列，直接使用循环即可。
	treeNode* searchBST2(treeNode* root, int targetVal)
	{
		while (root != nullptr) // 如果根结点不为空，则继续查找
		{
			// 如果根结点的值等于目标值，则返回根结点
			if (root->val == targetVal)return root; 

			// 如果根结点的值大于目标值，则在左子树中查找，否则在右子树中查找
			root = root->val > targetVal ? root->left : root->right; 
		}
        return nullptr; // 如果没有找到，则返回空指针
	}
};

// 17、判断一棵二叉树是不是有效的二叉搜索树。
// 思路：
// 中序遍历下，输出的二叉搜索树节点的数值是有序序列。
// 有了这个特性，验证二叉搜索树，就相当于变成了判断一个序列是不是递增的了。
class binaryTree17
{
private:
	vector<int>vec; // 定义一个向量用于存储中序遍历的结果	
	void inOrder(treeNode* root) 
	{
		if (root == nullptr)return; // 如果根结点为空，则直接返回
		inOrder(root->left); // 递归遍历左子树
		vec.push_back(root->val); // 将根结点的值存入向量中
		inOrder(root->right); // 递归遍历右子树
	}
public:
	bool isValidBST(treeNode* root) 
	{
		vec.clear(); // 清空向量
		inOrder(root); // 中序遍历二叉搜索树
		for (int i = 1; i < vec.size(); ++i) // 遍历向量，判断是否递增
		{
			if (vec[i] <= vec[i - 1])return false;
		}
		return true;
	}
};

// 18、给你一棵所有节点为非负值的二叉搜索树，请你计算树中任意两节点的差的绝对值的最小值。
// 最直观的想法，就是把二叉搜索树转换成有序数组，然后遍历一遍数组，就统计出来最小差值了。
class binaryTree18
{
private:
	vector<int>vec; // 定义一个向量用于存储中序遍历的结果
	void inOrder(treeNode* root)
	{
		if (root == nullptr)return; // 如果根结点为空，则直接返回
		inOrder(root->left); // 递归遍历左子树
		vec.push_back(root->val); // 将根结点的值存入向量中
		inOrder(root->right); // 递归遍历右子树
	}
public:
	int getMinimumDifference(treeNode* root) 
	{
		vec.clear(); // 清空向量
		inOrder(root); // 中序遍历二叉搜索树
		if (vec.size() < 2)return 0; // 如果向量的大小小于2，则返回0
		int result = INT_MAX; // 定义一个变量用于存储结果
		for (int i = 1; i < vec.size(); ++i) // 遍历向量，判断是否递增
		{
			result = min(result, vec[i] - vec[i - 1]);
		}
		return result;
	}
};

