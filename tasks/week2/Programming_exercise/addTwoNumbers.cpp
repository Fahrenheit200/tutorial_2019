#include<iostream>
using namespace std;
ListNode* addTWoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode* n1 = l1; ListNode* n2 = l2;   //n1,n2用于读取链表
	ListNode* l3 = new ListNode(0);     //l3用于存放结果
	ListNode* n3 = l3;
	int temp = 0;       //temp用于表示相加后是否进位
	ListNode* zero = new ListNode(0);   //zero用于暂存为0的zero->val
	do{
        //当n1,n2为空时指向zero，便于对应位相加
		if (n1 == NULL) n1 = zero;
		if (n2 == NULL) n2 = zero;
        //对应位相加并判断是否进位
		n3->val = n1->val + n2->val + temp;
		if (n3->val >= 10) {
			n3->val -= 10;
			temp = 1;
		}
		else temp = 0;
        //链表向后移动
		n1 = n1->next; n2 = n2->next;   
        //当n1,n2指向不同时为空,为l3申请空间
		if (n1 != NULL || n2 != NULL) { 
			n3->next = new ListNode(0);
			n3 = n3->next;
		}
	} while (n1 != NULL || n2 != NULL); //当n1,n2同时为空时终止循环
	return l3;
}

