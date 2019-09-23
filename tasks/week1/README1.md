  1    helloworld程序直接运行即可，代码较为简单
  
  2    公共后缀程序要添加头文件<algorithm>
  
  3    向程序输入已创建好的strs即可运行
  
  4    下面是我自己用来测试该程序的主函数，正常输出为jk
  5 
  6   #include<iostream>
  
  7   #include<vector>
  
  8   #include<string>
  
  9   #include<algorithm>
  
 10   using namespace std;
 
 11   string longestCommon(vector<string>& strs);
  
 12   int main()
 
 13  {
 14           vector<string> strs;
  
 15           strs.push_back("xhjk");
 
 16           strs.push_back("xjk");
 
 17           strs.push_back("ljk");
 
 18           cout<<longestCommon(strs);
 
 19          return 0；
 20   }

