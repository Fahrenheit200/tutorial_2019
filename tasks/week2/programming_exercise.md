## 程序设计能力练习题

- 请使用C++和g++。
- 开设此题的目的只是想让你熟悉基本的C++和程序设计，多动动脑筋。
- 只要简单测试Accepted就可以得分，代码简洁可得满分。请独立认真完成。
- 可能需要先了解的知识：std::string、vector

## 第一周题目 —— 最大公共后缀

### Description

编写一个函数来查找字符串数组中的最长公共后缀。

如果不存在公共前缀，返回空字符串 ""。

### Input
编写一个函数，接口如下:
```
string longestCommon(vector<string>& strs) {

}
```

### Output
返回最长的公共后缀

### Sample Input
```
ppp
pplpp
lpp
```

### Sample Output
```
pp
```


## 第二周题目 —— 链表加法

### Description
编写一个函数实现链表的加法，首先得了解什么是链表这种数据结构

### Input
编写一个函数，接口如下:
```
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        
}
```

### Output
A + B链表的结果值 

### Sample Input And Output
```
输入链表是逆序的
链表A 1->2->3
链表B 3->4->5
链表C 4->6->8
321 + 543 = 864
链表A 1->2->3->4
链表B 2->3->4
链表C 3->5->7->4
4321 + 432 = 4753
```
