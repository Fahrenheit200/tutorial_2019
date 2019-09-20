#include <vector>
#include <string>
#include <algorithm>
using namespace std;
string longestCommon(vector<string>& strs){
	string common="";
	char temp;
	int min;
	int i=0,j=0,k=0;
	for(k=0;k<strs.size();k++)//将每个字符串翻转
		reverse(strs[k].begin(),strs[k].end());
	
	min=strs[0].size();//找到最短的字符串的长度
	for(k=1;k<strs.size();k++)
		if(min>strs[k].size()) min=strs[k].size();
	
	for(j=0;j<min;j++){//遍历最短字符串长度的每一列，即每个字符串的同一位置
		temp=strs[0][j];//以第一个字符串的字符为比较标准
		for(i=1;i<strs.size();i++){//遍历每一行，即每一个字符串
			if(temp==strs[i][j]);
			else{//若有不相等的，则直接返回
				reverse(common.begin(),common.end());//返回字符串前要翻转
				return common;
			}
		}
		common+=temp;
	}
	reverse(common.begin(),common.end());//返回字符串前要翻转
	return common;
}
