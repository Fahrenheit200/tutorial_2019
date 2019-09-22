string longestCommon(vector<string>& strs)
{
	if(strs.empty()==1)return "";  //判断是否为空
	int common_length;
	string goal_string = strs.at(0); //默认第一个字符串为初始字符串

	for(int i=1;i < strs.size(); i++)
	{
		if(goal_string.length()>strs.at(i).length())//比较两个字符串长度大小，以较小的那个作为循环索引
		{
			common_length = strs.at(i).length();
		}
		else
		{
			common_length = goal_string.length();
		}

		int j;
		int flag = 0;
		int m1 = strs.at(i).length() - 1;
		int m2 = goal_string.length() - 1;

		for(j = 0;j < common_length;j++)//从最后一位开始比较两个字符串的字符，得到后缀长度
		{
			if(goal_string.at(m2) == strs.at(i).at(m1))
			{
				flag++;
			}
			m1--;
			m2--;
		}

		bool m = i==1&&flag == goal_string.length();

		if(flag == strs.at(i).length()||m)//判断得到的后缀是否为字符串
		{
			flag--;
		}
		goal_string = goal_string.substr(goal_string.size() - flag);//得到后缀
	}
	return goal_string;//循环之后得到最长公共后缀并返回
}

