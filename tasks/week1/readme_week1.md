# week1 task readme 第一周任务  

## 一、工作总结

    安装ubuntu18.04系统，安装各种配置，熟练vim等基本操作方法。
配置git,熟悉git和GitHub的使用。编写*hello world*工程文件，并使用g++编译器编译输出。
编写程序设计练习第一题，使用g++编译器，测试并修改。安装**OpenCV**库。学习Linux中的man和help命令，尝试使用Hosts,但是未成功。  

## 二、编程说明  

### hello world 工程
  主要使用
```
   cout<<"hello world"<<endl;
```
语句来实现  

### longestCommon 工程
主要思路：
以第一个字符串作为初始字符串*goal_string*,将它与其它字符串相比较得到较短字符串的长度，作为检查最长公共后缀的idex，再与该字符串进行比较得到相同的子串长度，进而得出这两组字符串的公共后缀。循环完成后即可得到字符串数组的最大后缀。  

**注意**
默认字符串不作为后缀
即，以下输入
**INPUT**
```
   pp
   pplpp
   lpp
```
的输出为
**OUTPUT**
```
   pp
```

