#include<string>
#include<iostream>

using namespace std;

string longestCommon(string a,string b)
{
	int len_a, len_b;
	len_a =a.length();
	len_b =b.length();
	//长度
	string back = "";
	//返回值
	int pa, pb;
	//作为控制数遍历字符串
	for (pa = len_a - 1, pb = len_b - 1; (pa >= 0) && (pb >= 0); --pa, --pb)
	{
		if (a[pa] == b[pb])
		{
			back =a[pa]+back;
		}
		else break;
	}
	return back;
}
int main()
{
	string a, b;
	cout << "输入数组" << endl;
	cin >> a ;
	cout << "输入第二个数组" << endl;
	cin >> b;
	while (cin.get()!=0)
	{
		a= longestCommon(a,b);
		cout <<"相同的后缀为："<< a << endl;
		if (a == "")
			break;
		else
		cout << "输入非0数则视为继续输入数组" << endl;
		cin >> b;
	}
	cout << "无相同后缀默认结束" << endl;
	system("pause");
}
