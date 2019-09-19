#include<iostream>
#include<vector>
#include<string>
using namespace std;
string longestCommon(vector<string>& strs);

int main()
{
	vector<string> strs;
	
	string temp;
	cout << "请输入要比较的字符串 按ctrl+D输入结束\n";
	while (cin >> temp)
	{
		strs.push_back(temp);
	}
	
	cout << "the longest common postfix is:"<<longestCommon(strs) << endl;;

	return 0;
}

string longestCommon(vector<string>& strs)
{
	bool equal = true;	
	bool over = false;

	int cnt = 0, num = strs.size(), L0 = strs[0].length(),no_char=0;
	//cnt：索引变量，指示当前正在和基准被比较的字符串的编号；
	//no_char：索引变量，指示当前正在的基准字符在字符串中的编号
	//num：vector中含有的字符串总数；L0：基准字符串的长度；
	//基准可以任选，故选择第一个字符串为基准

	vector<char> post_fix;
	int temp_length;//临时变量，用来放当前被比的字符串的长度
	while (equal&&no_char<L0&&!over)//退出条件：出现了不同的字符 或 有字符串已经结束
	{
		char ref = strs[0][L0-1-no_char];//ref:当前的基准字符
		for (cnt = 1; cnt < num; cnt++)//对于ref字符串的每一个字符 每一个字符串都要和它比较一次
		{
			temp_length = strs[cnt].size();
			if (no_char == temp_length)//如果已经有字符串结束了 直接退出
			{
				over = true;
				break;
			}
				
			if (ref!=strs[cnt][temp_length-1-no_char])//出现了不同的字符直接终止比较
			{
				equal = false;
				break;
			}
		}
		if (equal&&!over)//如果所有字符串都有这个ref字符
		{
			post_fix.push_back(ref);//那么这个字符就是后缀的一部分
		}
		else//已经出现了不相等字符或已经比完了 退出循环
		{
			equal = false;
			break;
		}

		no_char++;//比较下一个字符
	}

	//上面的操作实际上得到的是后缀的倒序 下面把它正过来
	int fix_length =no_char;
	char* temp = new char[fix_length];
	int j;
	for(j=0;j<fix_length;j++)
	{
		temp[j] = post_fix[fix_length - j -1];
	}
	temp[j] = '\0';

	//正过来之后赋值给一个strin对象然后返回
	string out = temp;
	return out;
	
}

