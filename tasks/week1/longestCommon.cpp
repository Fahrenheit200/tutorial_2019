#include <vector>
#include <string>
#include <algorithm>
#include <iostream>
using namespace std;
string longestCommon(vector<string>& strs){
	string common="";
	char temp;
	int i=0,j=0,k=0;
	for(k=0;k<strs.size();k++)
		reverse(strs[k].begin(),strs[k].end());
	for(j=0;j<strs[0].size();j++){
		i=0;
		temp=strs[i][j];
		for(i=0;i<strs.size();i++){
			if(temp==strs[i][j]);
			else return common;
		}
		common+=temp;
	}
	return common;
}

int main(){
	vector<string> str(3);
	str[0]="ppp";
	str[1]="pplpp";
	str[2]="lpp";
	cout<<longestCommon(str)<<endl;
	return 0;
}
