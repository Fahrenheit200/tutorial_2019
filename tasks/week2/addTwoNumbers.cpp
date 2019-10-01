ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode* result = new ListNode(0);
    if(l1==NULL && l2==NULL)
    {
        return result;
    }
    int sum = 0, carry = 0;
    ListNode* curr = result;
    while(l1!=NULL || l2!=NULL)
    {
        int num1;
        if(l1==NULL){num1=0;} else{num1=l1->val;}
        int num2;
        if(l2==NULL){num2=0;} else{num2=l2->val;}
        sum=num1+num2+carry;
        curr->next = new ListNode(sum%10);
        curr=curr->next;
        carry=sum/10;
        if(l1!=NULL) {l1=l1->next;}
        if(l2!=NULL) {l2=l2->next;}
    }
    if(carry!=0)
    {
        curr->next = new ListNode(carry);
    }
    return result->next;
}
