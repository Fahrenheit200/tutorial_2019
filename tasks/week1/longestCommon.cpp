string longestCommon(vector<string> &strs) {
	int index = 0;
	bool flag = 1;
	char temp;
	while (flag == 1) {
		if (index == strs[0].length()) break;
		flag = 1;
		temp = strs[0][strs[0].length() - index - 1];
		for (int i = 0; i < strs.size(); i++) {
			if (index == strs[i].length() || strs[i][strs[i].length() - index - 1] != temp) {
				flag = 0;
				break;
			}
		}
		if (flag == 1) index++;
	}
	return strs[0].substr(strs[0].length() - index);
}
