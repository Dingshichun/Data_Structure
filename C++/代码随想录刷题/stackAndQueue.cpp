#include"head.h"

// 在标准模板库 STL 中可以控制使用哪种容器来实现栈，所以栈一般不被归类为容器，
// 而被归类为容器适配器(container adapter)
// STL 中，栈的底层实现可以是 vector，deque，list ，主要就是数组和链表的底层实现。

// 常用的SGI STL，如果没有指定底层实现的话，默认是以 deque 为缺省情况下栈的底层结构。
// deque 是一个双向队列，只要封住一段，只开通另一端就可以实现栈的逻辑了。


// 1、用栈实现队列

// 思路：
// 使用栈来模拟队列的行为，如果仅仅用一个栈，是一定不行的，
// 所以需要两个栈，一个输入栈，一个输出栈，这里要注意输入栈和输出栈的关系。

// 在 push 数据的时候，只要数据放进输入栈就好，但在 pop 的时候，操作就复杂一些，
// 输出栈如果为空，就把进栈数据全部导入进来（注意是全部导入），再从出栈弹出数据，
// 如果输出栈不为空，则直接从出栈弹出数据就可以了。
// 最后如何判断队列为空呢？如果进栈和出栈都为空的话，说明模拟的队列为空了。

class myQueue
{
public:
	stack<int>stkIn; // 输入栈
	stack<int>stkOut; // 输出栈
	myQueue(){} // 构造函数

	// 元素进入队列
	void push(int x) { stkIn.push(x); }
	
	// 从队列首部移除元素，注意队列首部的元素被弹出了
	int pop()
	{
		if (!stkIn.empty()) // 输入栈非空，就将其元素全部添加到输出栈
		{
			stkOut.push(stkIn.top());
			stkIn.pop(); // 注意要弹出，才能添加输入栈中的下一个元素到输出栈
		}
		// 从输入栈弹出
		int result = stkOut.top();
		stkOut.pop();
		return result;
	}

	// 返回队列首部的元素，借助了上面定义的 pop 函数，
	// 队列首部的元素仍在队列中，只是获取到它的值
	int peek()
	{
		int res = this->pop(); // 弹出队首元素
		stkOut.push(res); // 再将弹出的队首元素加入到队列中，保持队列不变
		return res;
	}

	bool empty()
	{
		return stkIn.empty() && stkOut.empty();
	}
};

// 2、用单向队列实现栈

// 思路：用一个队列即可实现栈，虽然两个也行，但是比较麻烦。
// 入栈操作就是往队列添加元素，
// 出栈则将队列的元素依次弹出，并再次添加到队列中，全部弹出并添加到队列后
// 再弹出元素就跟出栈的顺序一样了。只是每次添加了新元素都要重复上面的出栈操作。

class myStack
{
public:
	queue<int>que; // 用于构造栈的队列
	myStack(){} // 构造函数

	void push(int x) { que.push(x); } // 入栈

	// 弹出栈顶元素
	int pop()
	{
		int len = que.size();
		--len;

		while (len--)
		{
			que.push(que.front());
			que.pop();
		}
		int result = que.front();
		que.pop();
		return result;
	}
	
	// 获取栈顶元素的值
	int top()
	{
		int len = que.size();
		--len;
		while (len--)
		{
			que.push(que.front());
			que.pop();
		}
		int result = que.front();
		que.push(que.front());
		que.pop(); // 这句没懂
		return result;
	}

	bool empty()
	{
		return que.empty();
	}
};

// 3、有效的括号
// 给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串，判断字符串是否有效。
// 有效字符串需满足：
// • 左括号必须用相同类型的右括号闭合。
// • 左括号必须以正确的顺序闭合。
// • 注意空字符串可被认为是有效字符串。

// 解决思路
// 不匹配的情况有以下三种：
// 1、字符串里面左括号多余
// 2、括号不匹配
// 3、右括号多余

// 解法 1：遍历字符串时将左括号入栈，遇到对应的右括号再将左括号出栈，
// 第一种情况：已经遍历完了字符串，但是栈不为空，说明有相应的左括号没有右括号来匹配，所以 return false
// 第二种情况：遍历字符串匹配的过程中，发现栈里没有要匹配的字符。所以 return false
// 第三种情况：遍历字符串匹配的过程中，栈已经为空了，没有匹配的字符了，说明右括号没有找到对应的左括号 return false
bool bracketIsValid(string str)
{
	// 括号匹配的话长度肯定是偶数
	if (str.size() % 2 != 0)
		return false;

	stack<char>stk; // 存放右括号的栈
	for (int i = 0; i < str.size(); ++i) // 遍历
	{
		// 遇到左括号，就将对应的右括号入栈
		if (str[i] == '(')
			stk.push(')');
		else if (str[i] == '{')
			stk.push('}');
		else if (str[i] == '[')
			stk.push(']');

		// 还在遍历的时候，如果栈已经为空，说明右括号多了
		// stk.top() != str[i] 是说没有匹配的字符串
		else if (stk.empty() || stk.top() != str[i])
			return false;
		else stk.pop();
	}
	// 遍历完后，栈如果不为空，说明左括号多了
	return stk.empty();
}

// 4、删除字符串中的所有相邻重复项
// 在 S 上反复执行重复项删除操作，直到无法继续删除。
// 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
// 比如 "abbaca"，删除后变为 "ca"。即删掉一个重复项之后，剩下的拼接在一起还是重复的话继续删。

string removeNeiborDuplicates(string str)
{
	stack<char>stk;
	for (auto s : str)
	{
		// 栈为空或遍历的字符不等于栈顶元素，则将元素入栈
		if (stk.empty() || s != stk.top())
			stk.push(s);
		else
			stk.pop(); // 遍历的字符和栈顶元素相同则弹出栈顶的元素
	}

	string result = ""; // 储存删除重复字母后的结果
	while (!stk.empty()) // 取出栈中的字母
	{
		result += stk.top();
		stk.pop();
	}
	reverse(result.begin(), result.end()); // 反转之后才是最终结果
	return result;
}

// 5、逆波兰表达式求值

// 根据 逆波兰表示法，求表达式的值。
// 有效的运算符包括 + , -, *, / 。每个运算对象可以是整数，也可以是另一个逆波兰表达式。
// 说明：
// 整数除法只保留整数部分。 给定逆波兰表达式总是有效的。
// 换句话说，表达式总会得出有效数值且不存在除数为 0 的情况。

// 示例 1：
// 输入 : ["2", "1", "+", "3", " * "]
// 输出 : 9
// 解释 : 该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9

// 解题思路：
// 适合用栈操作运算：遇到数字则入栈；
// 遇到运算符则取出栈顶两个数字进行运算符对应的计算，并将结果压入栈中。

long long reverPolanExpression(vector<string>& tokens)
{
	stack<long long>stk; // 存放数字的栈
	for (string tok : tokens) // 遍历字符串容器
	{
		if (tok == "+" || tok == "-" || tok == "*" || tok == "/")
		{
			// 遇到运算符则取出栈顶两个数字进行计算，并将结果压入栈中。
			long long num1 = stk.top();
			stk.pop();
			long long num2 = stk.top();
			stk.pop();
			if (tok == "+")stk.push(num1 + num2);
			if (tok == "-")stk.push(num1 - num2);
			if (tok == "*")stk.push(num1 * num2);
			if (tok == "/")stk.push(num1 / num2);
		}
		else
		{
			// 使用 stoll 将字符串转换为对应的整数
			stk.push(stoll(tok));
		}
	}

	// 弹出最后栈中的元素，即最后运算的结果
	long long result = stk.top();
	stk.pop();
	return result;
}

// 6、求滑动窗口最大值。没懂
// 使用单调队列

// 7、前 k 个高频元素
