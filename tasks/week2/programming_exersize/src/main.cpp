#include <cstdlib>
#include <time.h>
#include "ListNode.h"
#include "addTwoNumbers.cpp"


using namespace std;

int main(){						//下面是测试的代码
	int i = 0;
	srand(time(NULL));
	ListNode* l1 = new ListNode(0);
	for (i = 0 ; i < 1+ rand() % 10 ; i++){
		ListNode* p = new ListNode(rand() % 10);
		p->next = l1->next;
		l1->next = p;
	}
	l1 = l1->next;
	ListNode* l2 = new ListNode(0);
	for (i = 0 ; i < 1+rand() % 10 ; i++){
		ListNode* p = new ListNode(rand() % 10);
		p->next = l2->next;
		l2->next = p;
	}
	l2 = l2->next;
	ListNode* l3 = addTwoNumbers(l1,l2);
	ListNode* result = l3;
	while(l1!=NULL) {
		cout << l1->val ;
		l1 = l1->next;
	}	
	cout << endl;
	while(l2!=NULL) {
		cout << l2->val;
		l2 = l2->next;
	}
	cout << endl;
	while(result!=NULL) {
		cout << result->val;
		result = result->next;
	}
	cout << endl;
	return 0;
}
