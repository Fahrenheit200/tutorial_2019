#include "list.h"
using namespace std;
ListNode* Createlist(void)
{
	int num=0;
    cout<<"位数:";
    cin>>num;
    ListNode* p=NULL;
    for(int i=0; i<num; ++i)
     {
         ListNode* pNewNode = new ListNode(0);
         cin>>pNewNode->val;
         pNewNode->next=p;
         p=pNewNode;
     }
	return p;		
		
}

void Outputlist(ListNode* head)
{
	ListNode *newhead = NULL;
	while(head!=NULL)
	{
		ListNode* temp = head->next;
		head->next = newhead;
		newhead=head;
		head=temp;
	}
	ListNode* p=newhead;
	while(p)
	{
		cout<<p->val;
		p=p->next;
	}
	while(newhead!=NULL)
	{
		ListNode* temp = newhead->next;
		newhead->next = head;
        head=newhead;
        newhead=temp;		
	}
}






int main()
{
	ListNode* p1=Createlist();
	Outputlist(p1);
	cout<<endl;
	ListNode* p2=Createlist();
	Outputlist(p2);
	cout<<endl;
	ListNode* h=addTwoNumbers(p1,p2);
	Outputlist(h);
	cout<<endl;
	return 0;
		
}
