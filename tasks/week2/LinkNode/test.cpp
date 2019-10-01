#include <iostream>
#include <string>

#include "ListNodeAdd.h"

//This is the test source code for add LinkNode

int main()
{
    std::string n1, n2;
    ListNode *l1 = new ListNode(0);
    ListNode *l2 = new ListNode(0);
    ListNode *l1_head = l1, *l2_head = l2;
    std::cin >> n1;
    std::cin >> n2;
    for (int i = n1.length() - 1; i >= 0; --i)
    {
        int digit = n1[i] - '0';
        l1->val = digit;
        if (i != 0)
        {
            l1->next = new ListNode(0);
            l1 = l1->next;
        }
    }
    for (int i = n2.length() - 1; i >= 0; --i)
    {
        int digit = n2[i] - '0';
        l2->val = digit;
        if (i != 0)
        {
            l2->next = new ListNode(0);
            l2 = l2->next;
        }
    }
    ListNode *l3 = addTwoNumbers(l1_head, l2_head);
    ListNode *l3_head = l3;
    while (l3 != NULL)
    {
        std::cout << l3->val;
        l3 = l3->next;
    }
    std::cout << std::endl;
    ListNode *temp;
    l1 = l1_head;
    l2 = l2_head;
    l3 = l3_head;
    while (l1 != NULL)
    {
        temp = l1;
        l1 = l1->next;
        delete temp;
    }
    while (l2 != NULL)
    {
        temp = l2;
        l2 = l2->next;
        delete temp;
    }
    while (l3 != NULL)
    {
        temp = l3;
        l3 = l3->next;
        delete temp;
    }
}