
string longestCommon(vector<string>& strs) {
	string cmptemp, cmpfir;
	cmpfir = strs[0];
	int count = 0;

	while(true){
		int i;
		for (i = 1; i < strs.size(); i++) {
			int flag = 0;
			cmptemp = strs[i];

			for (int h = 0; h < strs.size(); h++) {
				if (strs[h].length() == count ) {
					return strs[h];
				}
			}
			//如果一字符串长度等于count，我们可以直接将此串返回作为最大后缀
			
			if (cmptemp[cmptemp.length() - count - 1] == cmpfir[cmpfir.length() - count - 1]) {
				continue;
			}
			else {
				break;
			}
			//将所有的串的倒数第count位的字符都与第一个串比较，都相等则说明该位字符
			//可以作为后缀，否则就break

		}

		if (i == strs.size()) {
			count++;
			continue;
		}
		else {
			break;
		}
	}

	if (count == 0) {
		return " ";
	}
	else {
		return cmpfir.substr(cmpfir.size() - count, cmpfir.size() - 1);
		//将倒数第count位到最后一位的字符输出
	}
}
