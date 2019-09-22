#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

string longestCommon(vector<string>& strs) {
	string res = "";
    if(strs.size() == 0) return res;
	for(int i=0; i<strs.size(); i++) {
		reverse(strs[i].begin(),strs[i].end());
cout<<strs[i]<<endl;
	}
    for(int i = 0; i<strs[0].size(); i++) {
        res += strs[0][i];
        for(int j = 0; j<strs.size(); j++) {
            if(res[i] != strs[j][i]) return res.substr(0, res.size() - 1);
        }
    }
    return res;
}

