/*****************************************************************
 * @file	programming_exercise.cpp
 * @brief	This file is a function to find the longest common suffix for an array of strings,and the main program to test it.
 * Details.
 *
 * @Author	Lomgahong
 * @email	1073097404@qq.com
 * @version	1.0.0
 * ---------------------------------------------------------------
 * Change History:
 *    <Date>  |<Version>|<Author> |<Description>
 * 2019/09/16 |  1.0.0  |Lomgahong|Create file
 *---------------------------------------------------------------
 *
 * **************************************************************/
#include<vector>
#include<string>
#include<iostream>
using namespace std;
using std::vector;

/**
 * 用于查找最长公共后缀的函数体
 */
string longestCommon(vector<string>& strs) 
{
	//初始化用于输出的字符串output
	string output="";
	//检查数组是否为空，若为空则直接跳过检测，直接输出空 
	if(strs.empty())
		return output;
	//变量n用于控制对某一个字符串的检测位置（代表从后数第n+1位）	
	int n=0;
	//以第一个字符串的长度作为循环次数
	while(n<strs[0].size())
	{
		//提取出第一个字符串的最后一个字符，并暫存
		char temp=strs[0][strs[0].size()-n-1];
		//先读取出字符串数组的大小，作为循环次数。依次与其他字符串相同位置的字符做比较，若发现不同则马上跳出，进行输出
		for(int m=1;m<strs.size();m++)   
		{
			if(strs[m][strs[m].size()-n-1]==temp)
				continue;
			else
				return output;
		}
		//若所有字符串对应同一位置的字符都相同，则属于共同后缀，于是将该字符储存在output中
		output=temp+output;
		//n自增，检查下一位置
		n++;
	}
}

