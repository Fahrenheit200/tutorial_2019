    helloworld程序直接运行即可，代码较为简单
  
      公共后缀程序要添加头文件<algorithm>
 
      向程序输入已创建好的strs即可运行
  
      下面是我自己用来测试该程序的主函数，正常输出为jk
  
     #include<iostream>
  
     #include<vector>
  
     #include<string>
  
     #include<algorithm>
  
    using namespace std;
 
    string longestCommon(vector<string>& strs);
  
    int main()
 
   {
            vector<string> strs;
  
            strs.push_back("xhjk");
 
            strs.push_back("xjk");
 
            strs.push_back("ljk");
 
            cout<<longestCommon(strs);
 
           return 0；
    }

