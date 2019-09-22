#include <iostream>
#include<vector>
#include <string>

using namespace std;

string longestCommon(vector<string> strs)
{
	string back = "";//返回值
	if (strs.empty())//判断是否为空 空则返回空值
		return back;
	int len_a;
	len_a = strs[0].length();//赋值长度 至少比较两个字符串
	int i = 1;//作为b 做比较
	int pa, pb;

	for (pa = len_a - 1, pb = strs[i].length() - 1; (pa >= 0) && (pb >= 0); --pa, --pb)
	{
		if (strs[0][pa] == strs[i][pb])
		{
			back = strs[0][pa] + back;
		}
		else break;
	}
	return back;//输出结果

}
int main()
{
	vector<string> strs{10};
	int i = 0;
	do
	{
		strs.reserve(i + 1);
		cout << "输入第" << i +1<< "个字符串" << endl;
		cin >> strs[i];
		cout << "输入回车结束一段字符输入 或只输入0结束输入" << endl;
		i++;
	
	} while (strs[i-1] != "0");
	cout <<"公共后缀"<< longestCommon(strs)<<endl;
	system("pause");
}
