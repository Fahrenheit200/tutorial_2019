#ifndef _LISTNODE_H_
#define _LISTNODE_H_
#include <iostream>
#include <vector>

using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL) {}
};
#endif
