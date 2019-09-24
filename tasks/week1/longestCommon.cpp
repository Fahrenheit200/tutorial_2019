#include <algorithm>
using namespace std;
string longestCommon(vector<string> &strs){
	string result = "";
	string min_str = *min_element(strs.begin(), strs.end(),
			[](const string &s1, const string &s2){return s1.length() < s2.length();});
	for(unsigned int i = 1; 1 < min_str.length(); i++){
		for(auto s : strs)
			if(s[s.length()-i] != min_str[min_str.length()-i]){
				reverse(result.begin(), result.end());
				return result;
			}
		result += min_str[min_str.length()-i];
	}
	reverse(result.begin(), result.end());
	return result;
}

