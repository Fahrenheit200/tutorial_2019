#include<iostream>
#include<list>
#include<stack>
#include<algorithm>

using namespace std;

struct ListNode{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};

/*为链表添加新结点*/ 
ListNode *addListNode(ListNode *head,int new_val)
{
	ListNode *new_node=new ListNode(new_val);//创建新节点
	ListNode *p_node;
	p_node=head;//pNode指向头结点
	if(head==NULL)//如果此时链表没有元素 
	    head=new_node;
	else
	{
		while(p_node->next!=NULL)//找到链表尾结点 
		    p_node=p_node->next;
		p_node->next=new_node;//插入新节点 
	} 
	return head;
}

/*反向打印链表*/ 
void printListNode(ListNode *head)
{
	if(head==NULL)
	    cout<<"此链表为空"<<endl;
	else
	{
		stack<ListNode*> listNodeStack;
		ListNode *p_node=head;
		while(p_node!=NULL)
		{
			listNodeStack.push(p_node);//将链表存在栈中 
			p_node=p_node->next;
		}
		while(!listNodeStack.empty())
		{
			//利用栈反向输出链表 
			p_node=listNodeStack.top();
			cout<<p_node->val;
			listNodeStack.pop(); 
		} 
	} 
}

/*两个链表相加*/ 
ListNode *addTwoNumbers(ListNode *l1,ListNode *l2)
{
    int i,j;//i为两数相加的个位数，j为十位数 
    i=l1->val+l2->val; 
    j=i/10;
    i-=j*10;
	ListNode *p_result=new ListNode(i);
	l1=l1->next;
	l2=l2->next;
	while(l1!=NULL&&l2!=NULL) 
    {
    	i=l1->val+l2->val+j;//i当前为两个链表当前对应数相加以及进位的和 
    	j=i/10;//j为进位数 
    	i-=j*10;//i为链表当前值
    	p_result=addListNode(p_result,i);
    	l1=l1->next;
    	l2=l2->next;//移动链表指针
	}
	if(l1!=NULL)//如果是l2空了 
	    while(l1!=NULL)
		{
			i=l1->val+j;//加上进位数
			j=i/10;
			i-=j*10;
			p_result=addListNode(p_result,i);
			l1=l1->next; 
		}
	else if(l2!=NULL)//如果是l1空了
	    while(l2!=NULL)
		{
			i=l2->val+j;//加上进位数
			j=i/10;
			i-=j*10;
			p_result=addListNode(p_result,i);
			l2=l2->next; 
		}
	if(j==1)//如果需要进位 
	    p_result=addListNode(p_result,1);
	//l1和l2都空了就直接返回 
	return p_result;
}
