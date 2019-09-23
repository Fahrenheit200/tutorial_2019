/**
 * @brief 将l1与l2两个链表相加得到L3
 * 函数使用后得到的L3，需要将各个node delete 释放空间
 * @param l1 第一个链表
 * @param l2 第二个链表
 * @return 返回第三个链表的head 
 * @note  l3的node 要delete 释放空间
 * @par  示例
 * @code 
 *     //通过链表加法得到第三个链表
 *      ListNode * l3=addTwoNumbers(l1,l2)
 * @encode 
 */
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode *l3=NULL;  
    ListNode *l4;
    ListNode*head;
    ListNode *p1=l1;
    ListNode *p2=l2;   ///需要的指针  p1,p2跟踪l1,l2   
    int flag=1;  /// 第一次new的时候 将head指向 l3
    while(p1&&p2) /// 链表相加
    {
        l4=l3;
        l3=new ListNode(p1->val+p2->val) ;
        if(l4!=NULL)
        l4->next=l3;
        p1=p1->next;
        p2=p2->next;
        if (flag)
            head=l3;
        flag=0;
    }
    while(p1||p2)  ///如果有多出来的 继续加
    {
        l4=l3;
        if (p1==NULL)
        {

            l3=new ListNode(p2->val);
            l4->next=l3;
            p2=p2->next;
        }
        else
        {
            l3=new ListNode(p1->val);
            l4->next=l3;
            p1=p1->next;
        }
    }
    return head;

}

