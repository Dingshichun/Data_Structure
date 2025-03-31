#include"head.h"

// 1����ת�ַ���
// ��������ַ�����ת�����������ַ������ַ����� char[] ����ʽ������
// ��Ҫ�����������������Ŀռ䣬�����ԭ���޸��������顢ʹ�� O(1) �Ķ���ռ�����һ���⡣
// ����Լ��������е������ַ����� ASCII ����еĿɴ�ӡ�ַ���
// ʾ�� ��
// ���룺["h", "e", "l", "l", "o"]
// �����["o", "l", "l", "e", "h"]

// ����˼·��˫ָ�롣����ָ�����ν�����Ȼ�����м��ƶ���
void reverseString(vector<char>& str) // ע�⣬��Ҫ������
{
	int left = 0;
	int right = str.size() - 1;
	while (left < right) // ѭ����������С���Ҽ��ɣ��ַ�������������ż���������㡣
	{
		// �������ݿ���ʹ�ÿ⺯�� swap����ʵ��Ҳ������һ����
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left;
		--right;
	}
}

// 2����ת�ַ��� II
// ����һ���ַ��� s ��һ������ k�����ַ�����ͷ����, ÿ������ 2k ���ַ���
// �ͷ�ת�� 2k ���ַ��е�ǰ k ���ַ������ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
// ���ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ��������ַ�����ԭ����
// ʾ�� :
// ����: s = "abcdefg", k = 2
// ��� : "bacdfeg"

// ����˼·��
// ����ʱ��ֻҪ�� i += (2 * k)��i ÿ���ƶ� 2 * k �Ϳ����ˣ�Ȼ���ж��Ƿ���Ҫ�з�ת�����䡣
// ��ΪҪ�ҵ�Ҳ����ÿ 2 * k �������㣬����д��������Ч�ܶࡣ

// �ȶ���һ���ַ�����ת����
void reverseStr(string& str, int start, int end)
{
	int left = start;
	int right = end;
	while (left < right)
	{
		char temp = str[left];
		str[left] = str[right];
		str[right] = temp;
		++left;
		--right;
	}
}

// ʵ����Ŀ
void reverseStringII(string& str, int k)
{
	for (int i = 0; i < str.size(); i += (2 * k))
	{
		// 1. ÿ�� 2k ���ַ���ǰ k ���ַ����з�ת
		// 2. ʣ���ַ�С�� 2k �����ڻ���� k ������תǰ k ���ַ�
		if (i + k <= str.size())
		{
			reverseStr(str, i, i + k - 1);
			continue; // �˳�����ѭ������ʼ��һ��ѭ����ֱ�� i+k > str.size()
		}

		// 3. ʣ���ַ����� k ������ʣ���ַ�ȫ����ת��
		reverseStr(str, i, str.size() - 1);
	}
}

// 3�������ת�ַ����е�ÿ�����ʣ�(*****)
// �ַ���ǰ����ߺ����������Ŀո񣬵��Ƿ�ת����ַ����ܰ�����
// ����������ʼ��ж���Ŀո񣬽���ת�󵥴ʼ�Ŀո���ٵ�ֻ��һ����
// ����ת����βû�пո񣬵���֮��ֻ����һ���ո�

// ��Ҫʹ�ø����ռ䣬�ռ临�Ӷ�Ҫ��ΪO(1)��

// ����˼· 1��
// �Ƴ�����ո� ����> ��ת�ַ��� ����> ��ÿ�����ʷ�ת

// ɾ������Ŀո�����ʹ�õ��� erase ����������Ĳ����ǵ�����
// ��������ʱ�临�ӶȽϸߣ�erase Ϊ O(n)�������� for ѭ������ O(n^2)
void removeExtraSpaces(string& str)
{
	for (int i = 0; i < str.size()-1; ++i)
	{
		// ����ɾ������Ŀո����пո��λ��ֻ����һ���ո�
		// ��ǰ���ɾ����Ӻ���ǰɾ����
		if (str[i] == str[i + 1] && str[i] == ' ')
			str.erase(str.begin()+i);
	}

	// ɾ���ַ���ǰ��Ŀո�ע��Ҫ���ж��ַ����ĳ����Ƿ���� 0
	if (str.size()>0 && str[0] == ' ')
		str.erase(str.begin());

	// ɾ���ַ�������Ŀո�ҲҪ�жϳ����Ƿ���� 0
	if (str.size() > 0 && str[str.size() - 1] == ' ')
		str.erase(str.begin()+str.size() - 1);
}

// ʹ��˫ָ���Ƴ��ո������ resize �ַ����Ĵ�С��ʱ�临�Ӷ�Ϊ O(n)
// ������ʹ��˫ָ���Ƴ������е�Ԫ�أ���ʹ�ö���ռ䡣
void removeExtraSpace1(string& str)
{
	int slow = 0;
	int fast = 0;

	// ȥ���ַ���ǰ��Ŀո�Ҳ�����ƶ���ָ�뵽��һ���ǿ��ַ���λ��
	while (str.size()>0 && fast<str.size() && str[fast] == ' ')
		++fast;

	// ȥ���ַ����м�Ķ���ո�ֻ����һ���ո�
	for (; fast < str.size(); ++fast)
	{
		// ע�����������
		if (fast - 1 > 0 && str[fast] == str[fast - 1] && str[fast] == ' ')
			continue;
		else
			str[slow++] = str[fast]; // slow++ ������ ++slow ����ΪҪ��ʹ�� slow ��ֵ���ټ�һ
	}

	// ȥ���ַ���ĩβ�Ŀո�
	if (slow - 1 > 0 && str[slow - 1] == ' ')
		str.resize(slow - 1); // ���������ַ����Ĵ�С
	else
		str.resize(slow); // ���������ַ�����С
}

// ������˫ָ��Ҳ���Ը��Ӿ���
void removeExtraSpaces2(string& str)
{
	int slow = 0;
	for (int i = 0; i < str.size(); ++i)
	{
		if (str[i] != ' ')
		{
			if (slow != 0)str[slow++] = ' ';
			while (i < str.size() && str[i] != ' ')
				str[slow++] = str[i++];
		}
	}
	str.resize(slow);
}


// 4��