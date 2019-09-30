#include <iostream>

using namespace std;

/* Definition for singly-linked list */
struct ListNode {
    public:
        int val;
        ListNode *next;
        ListNode() : next(NULL) {}
        ListNode(int x) : val(x), next(NULL) {}
};

/* Make a list */
class MakeList{
    public:
        ListNode *head ;
        ListNode *p;
        MakeList() : head(NULL) {}
        void insert(int a);
        void print();
};

void MakeList::insert(int a){
    ListNode *new_node;
    new_node = new ListNode(a);
    if(head == NULL)
    {      
        head = new_node;
        p = new_node;
    }
    else
    {
        p->next = new_node;
        p = new_node;
    }    
}

void MakeList::print()
{
    ListNode *head1 = head;
    while(head1 != NULL)
    {
        cout << head1->val;
        head1 = head1->next;
    }
}


int main()
{  
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
    
    MakeList list1, list2;  
    ListNode *add_list_head; 
    
    list1.insert(9);
    list1.insert(9);
    list1.insert(9);

    list2.insert(9);
    list2.insert(9);
    list2.insert(9);
    list2.insert(9);
    list2.insert(9);

    cout << "## 逆序列 ##" << endl; 
    cout << "List1:";
    list1.print();
    cout << endl << "List2:";
    list2.print();
    cout << endl << "Add_List:";

    add_list_head = addTwoNumbers(list1.head, list2.head);

    while(add_list_head != NULL)
    {
        cout << add_list_head->val;
        add_list_head = add_list_head->next;
    }

    return 0;
}

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    MakeList add_list;
    bool carry = false;
    while((l1 != NULL) && (l2 != NULL))
    {
        int add = l1->val + l2->val;

        if(add > 9)
        {
            if(carry)
                add_list.insert(add - 10 +1);
            else
                add_list.insert(add - 10);
            carry = true;
        }
        else
        {
            if(carry)
                add_list.insert(add + 1);
            else
                add_list.insert(add);
            carry = false;
        }

        l1 = l1->next;
        l2 = l2->next;
    }

    while(l1 != NULL)
    {
        if(carry)
            {
                if(l1->val + 1 > 9)
                    {
                        add_list.insert(l1->val + 1 - 10);
                        if(l1->next == NULL)
                        add_list.insert(1);
                    }
                else
                {
                    add_list.insert(l1->val + 1);
                    carry = false;
                }
            }
        else
            add_list.insert(l1->val);
        
        l1 = l1->next;
    }

    while(l2 != NULL)
    {
        if(carry)
            {
                if(l2->val + 1 > 9)
                    {
                        add_list.insert(l2->val + 1 - 10);
                        if(l2->next == NULL)
                        add_list.insert(1);
                    }
                else
                {
                    add_list.insert(l2->val + 1);
                    carry = false;
                }
            }
        else
            add_list.insert(l2->val);
        
        l2 = l2->next;
    }


    return add_list.head;
}