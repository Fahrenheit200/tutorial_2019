#include <iostream>
#include <string>
#include <vector>
using namespace std;

string longestCommon(vector<string>& strs)
{
    string result="";
    if(strs.empty())           //判断字符串数组是否为空
        return result;
    int i=1, t=strs[0].size();//t为字符串数组第一个元素的长度
    int m=strs.size();        //m为数组长度
    //以第一个元素作为标准，依次检查其余元素对应位置的字符是否与第一个元素相同
    while(t > 0)
    {
        char temp = strs[0][strs[0].size()-i];//temp为strs[0]倒数第i个字符
        //依次检查其余元素的倒数第i个字符是否与temp相同
        for(int j=1; j<m; j++)
        {
            if(strs[j][strs[j].size()-i] == temp)
                  continue;                   //如果相同继续检查下一个
            else
                  return result;              //如果有不同则说明此temp不是公共后缀，结束函数，返回最大公共后缀
        }
        result = temp + result;   //能来到这里说明所有元素倒数第i个字符相同，把这个字符加到result最前面
        //检查下一个字符
        t--;      
        i++;
            
    }
    return result;
}

int main()
{
    vector<string>str;
    string input;
    cout<<"enter the string array(输完回车并clrt+d):";
    while(cin>>input)
            str.push_back(input);
    cout<<longestCommon(str)<<endl;
    return 0;
        }
