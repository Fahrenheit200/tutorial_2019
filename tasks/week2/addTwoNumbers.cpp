ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
	ListNode *temp1 = l1, *temp2 = l2,*temp3=NULL,*buff=NULL,*l3=NULL;
	bool jinwei = 0;//进位标志
	while (temp1 || temp2) 
	{
		temp3 = buff;
		if (temp1 && temp2)
		{
			if (jinwei + temp1->val + temp2->val < 10)
			{
				buff = new ListNode(jinwei+temp1->val + temp2->val);
				jinwei = 0;
			}
			
			else
			{
				buff = new ListNode((jinwei+temp1->val + temp2->val)%10);
				jinwei = 1;
			}
			temp1 = temp1->next;
			temp2 = temp2->next;
				
		}
		else if (temp1)
		{
			if(jinwei + temp1->val<10)
			{
				buff = new ListNode(jinwei + temp1->val);
				jinwei = 0;
			}
			else
			{
				buff = new ListNode((jinwei + temp1->val)%10);
				jinwei = 1;
			}
			temp1 = temp1->next;
		}
		else
		{
			if (jinwei + temp2->val < 10)
			{
				buff = new ListNode(jinwei + temp2->val);
				jinwei = 0;
			}
			else
			{
				buff = new ListNode((jinwei + temp2->val) % 10);
				jinwei = 1;
			}
			temp2 = temp2->next;
		}

		if (temp3)
			temp3->next = buff;
		else//如果这是第一个元素 记录下地址 作为表头返回
			l3 = buff;
		
	}
	if (jinwei)//如果相加完成但还有进位 新开辟一个位
	{
		temp3 = buff;
		buff = new ListNode(1);
		temp3->next = buff;
	}
	return l3;
}
