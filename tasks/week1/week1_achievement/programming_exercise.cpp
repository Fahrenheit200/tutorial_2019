#include <iostream>
#include <cstring>
#include <vector>

using namespace std;

string longestCommon(vector<string>& strs)
{
    	string longestCommon;							//返回值
    	int flag,flag_min  ;							//给相同的字符计数
    	int s = strs.size();							//获取该向量的大小
    	int len0 = strs[0].length();						//获取第一个字符串的长度
    	int len1 = strs[1].length();						//获取第二个字符串的长度
    	for (flag_min = 0;len0-1-flag_min>=0&&len1-1-flag_min>=0; ){		//对比前两个字符串中的公共后缀，并作为基准
    		if (strs[0][len0-1-flag_min]-strs[1][len1-1-flag_min] == 0){
    			flag_min++;
    			continue;    		
    		}
    		else break;
    	}						
    	for (int i = 1;i < s;i++) {						//遍历这个vector
        	int len = strs[i].length();					//获取每一个字符串的长度
        	flag = 0;							//在遍历一个新的字符串之前将相同字符数重置为0
        	for (flag = 0;len0-1-flag>=0&&len-1-flag>=0; ){			//从字符串的末尾向前遍历
            		if(strs[i][len-1-flag]-strs[0][len0-1-flag]==0){	//判断并计数公共字符
            			flag++;
            			continue;
            		}	
            		else break;						//若不相等则跳出循环	
        	}
        	if (flag < flag_min)						//将当前字符串与第一个字符串的公共后缀与前两个字符串的公共后缀比较，取较小的一个
        		flag_min = flag;
    	}
    	if(flag_min==0)								//若无字符相等，则输出空格
        	longestCommon = " ";
    	else{									//有字符相等则将相等的字符串赋值给返回值
        	string common (strs[0],len0-flag_min,len0);
        	longestCommon = common;
    	}
    	cout << longestCommon << endl << "min" << flag_min <<"flag" << flag << endl;						//输出返回值
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
