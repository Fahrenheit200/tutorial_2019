#include<iostream>
#include<cstring>
#include<vector>
#include<algorithm>
using namespace std;

string longestCommon(vector<string> &strs){
    int max_comm = -1;
    int min_len = strs[0].size();
    string res="";
    for(int i=0;i<strs.size();i++)reverse(strs[i].begin(),strs[i].end());
    for(int i=0;i<strs.size();i++)if(strs[i].size()<min_len)min_len=strs[i].size();
    bool flag=false;
    for(int i=0;i<min_len;i++){
        char temp = strs[0][i];
        for(int j=1;j<strs.size();j++){
            if(strs[j][i]!=temp){
                max_comm=i;
                flag=true;
                break;
            }
        }
        if(flag)break;
        res=res+strs[0][i];
    }
    reverse(res.begin(), res.end());
    return res;
}

int main(){
    vector<string> s;
    s.push_back("abcakjdfn");
    s.push_back("abbccdfn");
    s.push_back("cbcdfn");
    cout<<longestCommon(s)<<endl;
}

