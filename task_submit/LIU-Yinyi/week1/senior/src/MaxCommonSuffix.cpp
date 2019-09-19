#include "MaxCommonSuffix.hpp"

using namespace std;

string longestCommon(const vector<string>& strs)
{
	if(strs.size() <= 0)
		return string();
	else if(strs.size() == 1)
		return strs[0];

	string str = strs[0];
	if(str.size() <= 0)
		return string();

	int common_count = 0, idx = 0;

	bool isEqual = true;
	while(isEqual)
	{
		int tmp = str.size() - common_count - 1;
		if(tmp < 0)
			break;
		else
			idx = tmp;
		char chr = str[idx];
		for(int i = 1; i < strs.size(); i++)
		{
			int idy = strs[i].size() - common_count - 1;
			if(idy < 0)
				break;
			if(chr != strs[i][idy])
			{
				isEqual = false;
				break;
			}

		}
		if(isEqual)
			common_count++;
	}

	if(common_count == 0)
		return string();

	return strs[0].substr(idx, common_count);
}
