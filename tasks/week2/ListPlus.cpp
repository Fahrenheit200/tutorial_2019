#include <iostream>
using namespace std;
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL) {}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode * l2) {
	ListNode *l3 = new ListNode(0);
	ListNode *la = l1->next, *lb = l2->next, *lc = l3;
	while (la && lb) {
		lc->next = new ListNode(la->val + lb->val);
		la = la->next;
		lb = lb->next;
		lc = lc->next;
	}
	while (la) {
		lc->next = new ListNode(la->val);
		la = la->next;
		lc = lc->next;
	}
	while (lb) {
		lc->next = new ListNode(lb->val);
		lb = lb->next;
		lc = lc->next;
	}
	ListNode *p = l3->next;
	while (p) {
		if (p->val - 10 >= 0) {
			p->val -= 10;
			if (!(p->next)) {
				p->next = new ListNode(0);
			}
			p->next->val++;
		}
		p = p->next;
	}
	return l3;
}

