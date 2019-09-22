#include"longest.h"

string longestCommon(vector<string>& str)
{
	//寻找输入字符串中最短字符串的长度
	int m = sizeof(str[0]);	//m用于储存最短字符串的长度
    for (auto v : str) {	
		if (sizeof(v) < m) {
			m = sizeof(v);
		}
	}
	//找到最大公共后缀
    string ans;		//ans用于储存结果
    char temp;		//temp用于暂存倒数第i个字符
    for (int i = 0; i < m ; i++) {		
        temp = str[0][str[0].length() - i - 1];	
        for (auto v : str) {
			if (temp != v[v.length() - i - 1])	
				return ans;	//当不匹配时退出循环，函数返回ans
		}
		string t; t += temp;	
		ans.insert(0, t);		//将temp插入到ans前
    }
	return ans;
}

