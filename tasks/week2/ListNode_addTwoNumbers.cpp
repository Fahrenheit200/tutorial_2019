// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode* next;
	ListNode(int x) : val(x), next(NULL) {}
};

// Definiyion for some functions used in "addTwoNumbers".
int getNumber(ListNode* l) {
	int num=0,digit=1;
	while (l != NULL) {
		num += ((l->val) * digit);
		digit *= 10;
		l = l->next;
	}
	return num;
}

int* numberDivide(int num,int &size) {
	int digit=0,num_copy=num;
	for (digit = 1; num_copy /= 10; digit++);
	size = digit;
	int *num_divide = new int[digit];
	for (int count = 0; count < digit; count++,num/=10) num_divide[count] = num % 10;
	return num_divide;
}

ListNode* numStore(int* num,int size) {
	ListNode* head = new ListNode(0);
	ListNode* lptr = head;
	for (int i = 0; i < size-1; i++) {
		lptr->val = num[i];
		lptr->next = new ListNode(0);
		lptr = lptr->next;
	}
	lptr->val = num[size - 1];
	lptr->next=NULL;
	
	return head;
}

// Definition for function addTwoNumbers.
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int num_1=getNumber(l1), num_2=getNumber(l2);
	int size;
	int* num_divide = numberDivide(num_1 + num_2, size);
	ListNode *head = numStore(num_divide,size);
	delete [] num_divide;
	return head;
}

