	

string longestCommon( vector<string> a)
{
	int i=0,n=0;
	for(i=0;1;i++)
	{
		string temp;
		getline(cin,temp);//read a line
		if(temp.size()==0)  break;//if the string is NULL,end the reading
		a.push_back(temp);//push temp into a
	}
	n=a.size();
	int  f=0,loca=-1;/*'f' is used to record the longest length of common string 
			  'loca' is used to record the location of longestcommon string*/
	for(i=0;i<n;i++)// to compare every two string on an contrary sequence
	{
		for(int j=i+1;j<n;j++)
		{
			int k=0;
			int len=min(a[i].size(),a[j].size());
			while(1)
			{
				if (k>len) break;//in case invalid visit
				if(a[i][a[i].size()-k]==a[j][a[j].size()-k])
				{
					 k++;
				}
				else break;
			}
			if (k>f){ f=k;loca=i;}
		}
	}
	string temp;
	temp=a[loca].substr(a[loca].size()+1-f,f);
	return temp;
}

	

