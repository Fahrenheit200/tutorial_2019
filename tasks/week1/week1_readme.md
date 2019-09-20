1.关于‘longestcommon。cpp’
  因为没有给出输入时有多少组数据，所以当读入到一个空字符串是判定结束输入。例如：
  asdf/n  
  asdfrt/n  
  artfrt/n  
  /n

  此时相当于输入了三组数据，输出为frt（舍弃最后读入的空字符串）
