ListNode* addTwoNumbers(ListNode* listA, ListNode* listB) {
	ListNode *p;
	int store[10];
	int numA = 0, numB = 0, cnt, tot;
	p = listA;
	cnt = 0;
	while (p != NULL) {
		store[cnt++] = p->val;
		p = p->next;
	}
	for (int i = cnt - 1; i >= 0; i--)
		numA = numA * 10 + store[i];
	p = listB;
	cnt = 0;
	while (p != NULL) {
		store[cnt++] = p->val;
		p = p->next;
	}
	for (int i = cnt - 1; i >= 0; i--)
		numB = numB * 10 + store[i];
	tot = numA + numB;

	ListNode *newhead,*pre,*now;
	int temp;
	newhead = new ListNode;
	pre = NULL;
	now = newhead;
	while (tot != 0) {
		temp = tot % 10;
		tot /= 10;
		if (pre == NULL) {
			now->val = temp;
			pre = now;
		}
		else {
			now = new ListNode;
			now->val = temp;
			pre->next = now;
			pre = now;
		}
	}
	return newhead;
}
