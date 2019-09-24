string longestCommon(vector<string> &strs){
  if (strs.size() == 0) return "";
  for (int i = 0; i < strs[0],length(); i ++){
	  char c = strs[0].at(strs[0].length() - 1 - i);
	  for (int j = 1; j < strs.size(); j ++){
		  if (i == strs[j].length() || strs[j].at(strs[j].length() - 1 - i) != c){
			  string tmp = strs[0].substr(str[0].length - i, i);
			  return tmp;
	          }
	}
  }
  return strs[0];
}

