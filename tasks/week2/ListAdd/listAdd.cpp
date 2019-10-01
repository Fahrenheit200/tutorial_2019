ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		if(l1==NULL && l2==NULL) return NULL;
        if(l1==NULL) return l2;
        if(l2==NULL) return l1;
		ListNode* res = new ListNode(-1);
        ListNode* p1 = l1;
        ListNode* p2 = l2;
        ListNode* p = res;

        int flag = 0;
        while (p1 != NULL || p2 != NULL) {
            int temp = flag;
            if (p1 != NULL) {
                temp += p1->val;
                p1 = p1->next;
            }
            if (p2 != NULL) {
                temp += p2->val;
                p2 = p2->next;
            }
            if (temp > 9) {
                temp -= 10;
                flag = 1;
            } else {
                flag = 0;
            }
            p->next = new ListNode(temp);
            p = p->next;
        }
        if (flag == 1) {
            p->next = new ListNode(1);
        }
        return res->next;
}
