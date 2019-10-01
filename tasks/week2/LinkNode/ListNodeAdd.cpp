#include "ListNodeAdd.h"

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
{
    ListNode* l3 = new ListNode(0);
    ListNode *l1_current = l1, *l2_current = l2, *l3_current = l3;
    int carry = 0, sum = 0;
    /*
    Deal with the common part of two list.
    */
    while (l1_current != NULL && l2_current != NULL)
    {
        sum = carry + l1_current->val + l2_current->val;
        l3_current->val = sum % 10;
        carry = sum / 10;
        if (l1_current->next != NULL && l2_current->next != NULL)
        {
            l3_current->next = new ListNode(0);
            l3_current = l3_current->next;
        }
        l1_current = l1_current->next;
        l2_current = l2_current->next;
    }
    /*
    Deal with the extra part of l1 or l2.
    */
    if (l1_current != NULL)
    {
        while (l1_current != NULL)
        {
            sum = carry + l1_current->val;
            l3_current->val = sum % 10;
            carry = sum / 10;
            if (l1_current->next != NULL)
            {
                l3_current->next = new ListNode(0);
                l3_current = l3_current->next;
            }
            l1_current = l1_current->next;
        }
    }
    else if (l2_current != NULL)
    {
        while (l2_current != NULL)
        {
            sum = carry + l2_current->val;
            l3_current->val = sum % 10;
            carry = sum / 10;
            if (l2_current->next != NULL)
            {
                l3_current->next = new ListNode(0);
                l3_current = l3_current->next;
            }
            l2_current = l2_current->next;
        }
    }
    /*
    Deal with the extra carry.
    */
    if (carry != 0)
    {
        l3_current->next = new ListNode(0);
        l3_current = l3_current->next;
        l3_current->val = carry;
    }
    return l3;
}