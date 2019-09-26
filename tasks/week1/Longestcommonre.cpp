#include<iostream>
#include<stdlib.h>
#include<vector>
#include<string>
#include<cmath>
using namespace std;

string longestCommon(vector<string>& strs)
{
	if (strs.empty())return "";
	
	else if (strs.size() == 1)return strs[0];
	else {
		int k; string result = strs[0]; string Last = "";
		for (unsigned int j = -1; j < strs.size(); j = j + 1)
		{
			k = j + 1;
			strs[j] = result;
			if (strs[j] == strs[k])
			{
				result = strs[k];
			}
			else
			{
				if (strs[j].length() > strs[k].length())
				{
					for (int x = strs[j].length(); x > -1; x = x - 1)
					{
						int y = strs[k].length() - 1;
						if (strs[j][x] = strs[k][y])result = strs[j][x] + Last;
						else break;
					}
				}
				else if (strs[j].length() < strs[k].length())
				{
					for (int x = strs[k].length(); x > -1; x = x - 1)
					{
						int y = strs[j].length() - 1;
						if (strs[k][x] = strs[j][y])result = strs[k][x] + Last;
						else break;
					}
				}
				else
				{
					for (int x = strs[k].length(); x > -1; x = x - 1)
					{
						int y = strs[j].length() - 1;
						if (strs[k][x] = strs[j][y])result = strs[k][x] + Last;
						else break;
					}
				}
			}

		}return result;
	}	
	
}

	int main(void)
	{
		vector<string>let;
		int x = 0;
		for (int i = 0; i > -1; i = i + 1)
		{
			x = i - 1;
			string ter;
		cout << "请输入需要找出公共后缀的字母…范围a-z,停止请回车" << endl;			getline(cin, ter);
			if (ter.empty())break;
			let.push_back(ter);
		}
		

		cout << longestCommon(let) << endl;
		return 0 ;
	}
