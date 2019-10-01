#include "ListNode.h"


using namespace std;

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	int sum = 0, c = 0;
	vector<int> ans;	//先用向量储存结果
	while (1) {
		sum = (l1->val + l2->val + c) % 10;
		c = (l1->val + l2->val + c) / 10;
		if (l1->next == NULL && l2->next == NULL) {
			ans.push_back(sum);		//储存相加并进位后的结果
			if (c == 1)
				ans.push_back(c);		//储存进位
			break;
		}
		ans.push_back(sum);
		if (l1->next != NULL)		//判断当前指针的下一节点是否存在
			l1 = l1->next;
		else
			l1->val = 0;		//不存在则补零
		if (l2->next != NULL)
			l2 = l2->next;
		else
			l2->val = 0;
		}

	ListNode* head = new ListNode(0);
	ListNode* temp = head;
	for (int i = 0; i < ans.size(); i++) {		//将向量中的结果转存到链表中
		ListNode* p = new ListNode(0);
		p->val = ans[i];
		temp->next = p;
		temp = p;
	}
	return head->next;
}







