#ifndef _LISTNODE_MODULE_H_
#define _LISTNODE_MODULE_H_

#include <stddef.h>

struct ListNode
{
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);

#endif