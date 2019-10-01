#include "MaxCommonSuffix.hpp"

using namespace std;

string longestCommon(const std::vector<string>& strs)
{
	if(!strs.size())
		return string();

	std::vector<int> strs_len {};
	for(string str : strs)
		strs_len.push_back(str.length());

	int loop_times = *std::min_element(strs_len.begin(), strs_len.end());
	if(loop_times)
	{
		bool flag = true;
		int i = 0;
		for(i = 1; i <= loop_times && flag; )
		{
			char chr = strs[0][strs[0].size() - i];
			for(string str : strs)
			{
				if(chr != str[str.size() - i])
				{
					flag = false;
					break;
				}
			}
			if(flag)
				i++;
			else
				i--;
		}
		if(i >= loop_times)
			i--;
		int index = strs[0].size() - i;
		return strs[0].substr(index, i);
	}
	else
	{
		return string();
	}
}
