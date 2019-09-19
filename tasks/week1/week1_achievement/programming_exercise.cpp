#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

string longestCommon(vector<string>& strs)
{
    	string longestCommon;							//返回值
    	int flag ;								//给相同的字符计数
    	int s = strs.size();							//获取该向量的大小
    	int len0 = strs[0].length();						//获取第一次输入的字符串大小
    	for (int i = 0;i < s;i++) {						//遍历这个vector
        	int len = strs[i].length();					//获取每一个字符串的长度
        	flag = 0;							//在遍历一个新的字符串之前将相同字符数重置为0
        	for (flag = 0;len0-1-flag>=0&&len-1-flag>=0; flag++){		//从字符串的末尾向前遍历
            		if(strs[i][len-1-flag]-strs[0][len0-1-flag]==0)		//判断两字符是否相等
                		continue;					//若相当则继续循环
            			else break;					//若不相等则跳出循环	
        	}
    	}
    	if(flag==0)								//若无字符相等，则输出空格
        	longestCommon = " ";
    	else{									//有字符相等则将相等的字符串赋值给返回值
        	string common (strs[0],len0-flag,len0-1);
        	longestCommon = common;
    	}
    	cout << longestCommon << endl;						//输出返回值
    	return longestCommon;							//返回值
}
int main()
{	
		
	vector<string> strs;							//创建字符串向量
	string input;								//用于输入字符串
	while (cin >> input&&input!="!") {					//当输入的字符不为"!"时将其push到vector中
        	strs.push_back(input);
    	}
	longestCommon(strs);							//调用longestCommon函数
	return 0;
}
