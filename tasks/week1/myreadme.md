Hello_world使用下列命令编译
g++ Hello_world.c -o Hello_world
然后使用下列命令运行编译文件
./Hello_world
输出如下
Hello world!


程序设计题的插口所需要的头文件为
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
输入参数为一个字符串容器
采用算法如下：
1.将每个字符串倒序并排序
2.比较排序后的第一个与最后一个字符串，即可获得倒序的最大公共后缀
3.然后再将其值倒序后返回
调用方式为：
cout<<longestCommon(strs)<<endl;
其中strs为一个容器
编译运行方式与Hello_world文件类似
输出与Sample一致，并尝试了其他输入

