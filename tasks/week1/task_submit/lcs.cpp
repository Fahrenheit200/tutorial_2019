#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

string longestCommon(vector<string>& strs)
{
	if (strs.size() == 1) return strs[0];
	string suffix = strs[0];
	for (int i = 1; i < strs.size(); i++)
	{
		int j, k;
		for (j = suffix.size() - 1, k = strs[i].size() - 1; j >= 0 && k >= 0 && suffix[j] == strs[i][k]; j--, k--);
		suffix = suffix.substr(j + 1, suffix.size() - j - 1);
	}
	return suffix;
}

int main()
{
	vector<string> strs;
	string s;
	while (cin >> s)
	{
		strs.push_back(s);
	}
	cout << longestCommon(strs) << endl;
	return 0;
}
