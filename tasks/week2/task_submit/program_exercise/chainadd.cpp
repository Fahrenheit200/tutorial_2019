#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x): val(x), next(NULL) {}
};
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode* head = new ListNode(0);
	ListNode* res = head, *l;
	int jin = 0, val = 0;
	while (l1 != NULL && l2 != NULL)
	{
		val = l1->val + l2->val + jin;
		jin = val / 10;
		val = val % 10;
		res->next = new ListNode(val);
		res = res->next;
		l1 = l1->next;
		l2 = l2->next;
	}
	if (l1 || l2)
	{
		l = l1 ? l1 : l2;
		while (l)
		{
			int val = l->val + jin;
			res->next = new ListNode(val % 10);
			jin = val / 10;
			res = res->next;
			l = l->next;
		}
	}
	if (jin) res->next = new ListNode(jin);
	ListNode* p = head; head = head->next; delete p;
	return head;
}
