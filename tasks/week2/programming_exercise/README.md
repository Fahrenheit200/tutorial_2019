## 第二周程序设计题 —— 链表加法

### Description

编写一个函数实现链表的加法

### Input

编写一个函数，接口如下:

```cpp
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
```

### Output

A + B 链表的结果值
### Sample Input And Output

```shell
输入链表是逆序的
链表A 1->2->3
链表B 3->4->5
链表C 4->6->8
321 + 543 = 864
```

