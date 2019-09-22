#include<iostream>
#include"longest.h"
using namespace std;

int main()
{
	vector<string> vstr;
	string s;
	while (cin >> s) vstr.push_back(s);
	cout << longestCommon(vstr) << endl;
	return 0;
}
