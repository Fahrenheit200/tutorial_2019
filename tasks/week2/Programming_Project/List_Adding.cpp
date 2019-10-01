ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int carry = 0, carryflag = 0;
	int count1 = 0, count2 = 0;
	ListNode*temp1 = l1, *temp2 = l2;
	while (temp1 != NULL) {
		count1++;
		temp1 = temp1->next;
	}
	while (temp2 != NULL) {
		count2++;
		temp2 = temp2->next;
	}
	temp1 = l1;
	temp2 = l2;

	if (count1 > count2) {
		int counter = 0;
		while (temp2 != NULL) {
			carryflag = (temp1->val + temp2->val + carry) / 10;
			temp1->val = (temp1->val + temp2->val + carry) % 10;
			carry = carryflag;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		while (temp1->next != NULL) {
			carryflag = (temp1->val + carry) / 10;
			temp1->val = (temp1->val + carry) % 10;
			carry = carryflag;
			temp1 = temp1->next;
			counter++;
		}
		carryflag = (temp1->val + carry) / 10;
		temp1->val = (temp1->val + carry) % 10;
		carry = carryflag;
		if (carryflag) {
			temp1->next = new ListNode(1);
		}
		return l1;
	}
	else if(count2>count1){
		int counter = 0;
		while (temp1 != NULL) {
			carryflag = (temp1->val + temp2->val + carry) / 10;
			temp2->val = (temp1->val + temp2->val + carry) % 10;
			carry = carryflag;
			temp1 = temp1->next;
			temp2 = temp2->next;
			counter++;
		}
		while(temp2->next != NULL){
			carryflag = (temp2->val + carry) / 10;
			temp2->val = (temp2->val + carry) % 10;
			carry = carryflag;
			temp2 = temp2->next;
			counter++;
		}
		carryflag = (temp2->val + carry) / 10;
		temp2->val = (temp2->val + carry) % 10;
		carry = carryflag;
		if (carryflag) {
			temp2->next = new ListNode(1);
		}
		return l2;
	}
	else {
		int counter = 0;
		while (temp1->next != NULL) {
			carryflag = (temp1->val + temp2->val + carry) / 10;
			temp1->val = (temp1->val + temp2->val + carry) % 10;
			carry = carryflag;
			temp1 = temp1->next;
			temp2 = temp2->next;
		}
		carryflag = (temp1->val + temp2->val + carry) / 10;
		temp1->val = (temp1->val + temp2->val + carry) % 10;
		carry = carryflag;
		if (carryflag) {
			temp1->next = new ListNode(1);
		}
		return l1;
	}
}
