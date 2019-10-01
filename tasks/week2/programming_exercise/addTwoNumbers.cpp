#include <iostream> 
using namespace std;

/*
*定义节点结构
*/
struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int value) :val(value), next(NULL) {};
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode *dummy = new ListNode(-1);
	ListNode *p1 = l1;
	ListNode *p2 = l2;
	ListNode *p = dummy;
	int flag = 0;       //进位标识
	while (p1 != NULL || p2 != NULL) 
	{
		int temp = flag;            
		if (p1 != NULL)       //判断不为空
		{
			temp += p1->val;
			p1 = p1->next;
		}
		if (p2 != NULL)       //判断不为空
		{
			temp += p2->val;
			p2 = p2->next;
		}
		if (temp > 9)       //需要进位
		{
			temp -= 10;    //取个位的数字
			flag = 1;
		}
		else 
			flag = 0;
		p->next = new ListNode(temp);
		p = p->next;
	}
	if (flag == 1)       //进位
		p->next = new ListNode(1);
	return dummy->next;	
}
