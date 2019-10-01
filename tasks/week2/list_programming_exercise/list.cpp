#include "list.h"
using namespace std;
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	//判断链表是否为空
	if(l1==NULL && l2==NULL) return NULL;
	if(l1==NULL) return l2;
	if(l2==NULL) return l1;

	ListNode* i=l1, * j=l2;
	ListNode* sum = new ListNode(0);
	ListNode *p = sum;
	int flag = 0;   //flag为进为标志
	while(i!=NULL || j!=NULL)
	{
		int temp = flag;
		if(i!=NULL)
		{
			temp += i->val;
			i = i->next;
		}
		if(j!=NULL)
		{
			temp += j->val;
			j=j->next;
		}
		if(temp>9)
		{
			temp-=10;
			flag=1;
		}else{
			flag=0;		
		}
		p->next = new ListNode(temp);
		p = p->next;
	}
	if(flag==1)
	{
		p->next = new ListNode(1);		
	}
	return sum->next;
}
