#include<vector>
#include<iostream>
using namespace std;
string longestCommon(vector<string>& strs);
int main()
{	unsigned n;
	cout<<"Enter the number of strings:";
	cin>>n;
	string strs[n];
	vector<string>v1;
	for(int i=0;i<n;i++){
		cin>>strs[i];
		v1.push_back(strs[i]);
	}
    cout<<longestCommon(v1);
	return 0;
}
string longestCommon(vector<string>& strs){
	int num=sizeof(strs)/sizeof(string);
	int len[num],j;
	vector<char>vec;
	
	for(int i=0;i<num;i++)
		len[i]=strs[i].size();
		
	for(j=1;j<=len[0];j++){
		for(int i=1;i<num;i++){
		if(strs[0][len[0]-j]==strs[i][len[i]-j])
			continue;
		else
			goto out; 
		}
		vec.push_back(strs[0][len[0]-j]);
	}
	out:;
	char c[j-1];//相同的字符串序列长度为j-1
	for(int i=0;i<j-1;i++){
		c[j-2-i]=vec[i];
	}
	string s(&c[0],&c[j-1]);
	return s;
}

