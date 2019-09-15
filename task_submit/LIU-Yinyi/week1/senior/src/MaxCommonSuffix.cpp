#include "MaxCommonSuffix.hpp"

using namespace std;

string longestCommon(const vector<string>& strs)
{
	if(strs.size() <= 0)
		return string();
	else if(strs.size() == 1)
		return strs[0];

	string str = strs[0];
	int common_count = 0, idx = 0;

	bool isEqual = true;
	while(isEqual)
	{
		idx = str.size() - common_count - 1;
		char chr = str[idx];
		for(int i = 1; i < strs.size(); i++)
		{
			int idy = strs[i].size() - common_count - 1;
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
