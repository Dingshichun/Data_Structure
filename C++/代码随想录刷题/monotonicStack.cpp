#include"head.h"

//����ջ��
// ͨ����һά���飬ҪѰ����һ��Ԫ�ص��ұ߻�����ߵ�һ�����Լ������С��Ԫ�ص�λ�ã�
// ��ʱ���Ǿ�Ҫ�뵽�����õ���ջ�ˡ�ʱ�临�Ӷ�ΪO(n)��

//����ջ�ı����ǿռ任ʱ�䣬��Ϊ�ڱ����Ĺ�������Ҫ��һ��ջ����¼�ұߵ�һ���ȵ�ǰԪ�ظߵ�Ԫ�أ�
//�ŵ�����������ֻ��Ҫ����һ�Ρ�

//��ʹ�õ���ջ��ʱ������Ҫ��ȷ���¼��㣺
//1.����ջ���ŵ�Ԫ����ʲô��
//����ջ��ֻ��Ҫ���Ԫ�ص��±� i �Ϳ����ˣ������Ҫʹ�ö�Ӧ��Ԫ�أ�ֱ�� T[i] �Ϳ��Ի�ȡ��
//2.����ջ��Ԫ���ǵ����أ� ���ǵݼ��أ���Ҫ����ʵ���������

// 1��ÿ���¶�
//�����ÿ�� ���� �б���������һ���б�
//��Ӧλ�õ����Ϊ��Ҫ��۲⵽���ߵ����£�������Ҫ�ȴ���������
//�����������֮�󶼲������ߣ����ڸ�λ���� 0 �����档
//���磬����һ���б� temperatures = [73, 74, 75, 71, 69, 72, 76, 73]��
//������Ӧ����[1, 1, 4, 2, 1, 1, 0, 0]��
class monotonicStack1
{
public:
	vector<int>dailyTemprature(vector<int>& tem)
	{
		stack<int>stk; // ����ջ��������Ԫ������
		vector<int>result(tem.size(), 0); // ������
		stk.push(0); // ��һ��Ԫ�ص����� 0 ��ջ
		for (int i = 1; i < tem.size(); ++i) // �ӵڶ���Ԫ�ؿ�ʼ������������һ��
		{
			if (tem[i] < tem[stk.top()])stk.push(i); // ���һ
			else if (tem[i] == tem[stk.top()])stk.push(i); // �����
			else // �����
			{
				// ��ջ�ǿ��ҵ�ǰ������Ԫ�ش���ջ��Ԫ��ʱ
				while (!stk.empty() && tem[i] > tem[stk.top()])
				{
					result[stk.top()] = i - stk.top(); // ��������� result
					stk.pop(); // ջ��Ԫ�س�ջ
				}
				stk.push(i); // Ԫ����ջ
			}
		}
		return result;
	}
	// ��չ��Ҫ��۲⵽���͵����£�������Ҫ�ȴ���������
	vector<int>dailyTemprature1(vector<int>& tem)
	{
		stack<int>stk; // ����ջ��������Ԫ������
		vector<int>result(tem.size(), 0); // ������
		stk.push(0); // ��һ��Ԫ�ص����� 0 ��ջ
		for (int i = 1; i < tem.size(); ++i) // �ӵڶ���Ԫ�ؿ�ʼ������������һ��
		{
			if (tem[i] > tem[stk.top()])stk.push(i); // ���һ
			else if (tem[i] == tem[stk.top()])stk.push(i); // �����
			else // �����
			{
				// ��ջ�ǿ��ҵ�ǰ������Ԫ��С��ջ��Ԫ��ʱ
				while (!stk.empty() && tem[i] < tem[stk.top()])
				{
					result[stk.top()] = i - stk.top(); // ��������� result
					stk.pop(); // ջ��Ԫ�س�ջ
				}
				stk.push(i); // Ԫ����ջ
			}
		}
		return result;
	}
};