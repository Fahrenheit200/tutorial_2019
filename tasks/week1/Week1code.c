
string longestCommon(vector<string>& strs){
	int len=strs.size(); 
	int minl=min(strs[0].size(),strs[len-1].size());//找出最短的字符串字符数 
	string str;
	for(int i=0;i<len;i++)
		reverse(strs[i].begin(),strs[i].end());//对容器中每个字符串倒序 
	sort(strs.begin(),strs.end());//对倒序后的字符串排序 
    for(int i=0;i<minl;i++) 
    {
    	if(strs[0][i]!=strs[len-1][i])//比较第一个与最后一个字符串 
    	{
		    str=strs[0].substr(0,i);
    	    reverse(str.begin(),str.end());//再将倒序后的字符串恢复以输出 
    	    return str;
    	}
	}
	str=strs[0].substr(0,minl);
	reverse(str.begin(),str.end());
	return str;
}
