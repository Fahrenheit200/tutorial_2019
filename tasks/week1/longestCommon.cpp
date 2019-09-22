/*需要algorithm,iostream,vector,string*/
string longestCommon(vector<string>& strs)
{
    string an;
    int i,j;


    for ( i=0;i<strs.size();i++)
        reverse((strs[i]).begin(),(strs[i]).end());  //将所有string倒置

    int min=999;
    for ( i=0;i<strs.size();i++)     //找到最短的string长度
        if (min>=strs[i].length())
            min=strs[i].length();

    int flag=1;
    for( i=0;i<min;i++)
        {for( j=0;j<strs.size()-1;j++)
            if(strs[j][i]!=strs[j+1][i])        //通过逐个判断字符是否相同来确定其后缀
                {
                    flag=0;
                    break;
                }
            if(flag)
      		an+=strs[j][i];
	   	flag=1;
	}
    reverse(an.begin(),an.end());//再倒置一次
    return an;


}
