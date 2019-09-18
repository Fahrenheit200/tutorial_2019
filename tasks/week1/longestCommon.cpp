#include<bits/stdc++.h>
using namespace std;

string longestCommon(vector<string>& strs) {
	unsigned int i, j = 1;
	string a;
	while (j) {
		if (j > strs[0].length()) return a;
		a = strs[0].substr(strs[0].length() - j, j);
		for (i = 1; i < strs.size(); i++) {
			if (j > strs[i].length() || a != strs[i].substr(strs[i].length() - j, j))
				return a.substr(a.length() - j + 1, j -1);
		}
		j++;
	}
}
int main() {
	unsigned int i;
	vector<string> strs;
	string a;
	while (cin >> a) strs.push_back(a);
	cout << longestCommon(strs) << endl;
	return 0;
}
