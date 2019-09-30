#include<iostream>
using namespace std;
struct ListNode{
 int val;
 ListNode *next;
 ListNode(int x):val(x),next(NULL){ }
};
ListNode*  addTwoNumbers(ListNode* l1, ListNode* l2)
{
 int i=0,j=0;
 int a=0,b=0,num,temp;
 while(l1!=NULL)     //取出数值1
 {
  temp=l1->val;
  for(int m=0;m<i;m++)
  temp=temp*10;
  a=a+temp;
  l1=l1->next;
  i++;
 }
 while(l2!=NULL)//取出数值2
 {
  temp=l2->val;
  for(int m=0;m<j;m++)
  temp=temp*10;
  b=b+temp;
  l2=l2->next;
  j++;
 }
 
 num=a+b;//得到数值3
 int len=0;
 int x=num;
 
 while(x){         //将数值3放分解成单位数
 x/= 10;
 len++;}
int *array=new int[len];
 i=0;
x=num;
while(x)
{
 if(x!=0)
 {array[i]=x%10;
 x/=10;}
 i++;
}
 
ListNode *c=NULL;      //将数值3放入链表中
ListNode *head=new ListNode(array[0]);
c=head;
for(int i=1;i<len;i++)
{
 head->next=new ListNode(array[i]);
 head=head->next;
}
return c;
}


