string longestCommon(vector<string>& strs)
{
	int num=strs.size() ;
	int b[num];
	
	for(int i=0;i<num;i++)
	{
		b[i]=strs[i].length();
	}
	
	int minlen=*min_element(b,b+num);
	vector<char> c;
	int n=0;
	
	for(int j=0;j<minlen;j++)
	{
	for(int k=1;k<num;k++)
	{
	
		if(strs[0][b[0]-j-1]==strs[k][b[k]-j-1])
		{
	
		if(k==(num-1) ){c.push_back(strs[0][b[0]-j-1]) ;n++;}
		continue;
		}
		else
		break;
	}}	

char temp;                         
char *d=new char[n];
for(int i=0;i<n;i++)
	{
		
		d[n-1-i]=c[i];
		
	}
		
string x;
if(n!=0)x=d;
return x;
}
