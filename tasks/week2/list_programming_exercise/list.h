#ifndef LIST_H
#define LIST_H
#include <iostream>
struct ListNode{
	int val;
	ListNode* next;
	ListNode(int x):val(x), next(NULL){}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

#endif
