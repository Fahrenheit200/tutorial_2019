string longestCommon(vector<string> &strs)
{
    if(strs.size()==0) return "";
    string tail;
    bool is_Same=true;
    for(int i=strs[0].length()-1;i>0;i--)
    {
        char c=strs[0][i];
        for(unsigned int j=1;j<strs.size();j++)
        {
            if(strs[j][strs[j].length()+i-strs[0].length()]!=c) {is_Same=false;break;}
        }
        if(is_Same) {tail.push_back(c);}
    }
    reverse(tail.begin(),tail.end());
    return tail;
}
