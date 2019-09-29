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
	ListNode* res = new ListNode(0), *l;
	ListNode* ans = res;
	int jin = 0, val = 0;
	while (l1 != NULL && l2 != NULL)
	{
		val = l1->val + l2->val + jin;
		jin = val / 10;
		val = val % 10;
		res->val = val;
		res->next = new ListNode(0);
		res = res->next;
		l1 = l1->next;
		l2 = l2->next;
	}
	if (l1 || l2)
	{
		l = l1 ? l1 : l2;
		while (l)
		{
			res->val = (l->val + jin) % 10;
			jin = (l->val + jin) / 10;
			res->next = new ListNode(0);
			res = res->next;
			l = l->next;
		}
	}
	res->val = jin;
	return ans;
}
