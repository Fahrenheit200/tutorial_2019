/************************************************************
*  @file     listAddtion.cpp                                              
*  @brief    the addtion of lists consist of positive integer 
*  Details.                                                                  
*                                                                          
*  @author   Jili Liao                                                      
*  @email    915836449@qq.com                                         
*  @version  1.0.0.0                                                 
*  @date     2019/09/25                                                                                                                  
*----------------------------------------------------------
*  Remark         : Description                                              
*----------------------------------------------------------
*  Change History :                                                          
*  <Date>    | <Version> | <Author>     | <Description>                   
*----------------------------------------------------------
*  2019/09/25| 1.0.0.0   | Jili Liao    | Create file                     
*----------------------------------------------------------
*                                                                            
*************************************************************/
    
#include <cmath>


/** 
* @brief  node of list 
*/
struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};


/** 
* @brief  add two list and create a new list containing the result
* @param[in]  l1  --  pointer pointing to list1 
* @param[in]  l2  --  pointer pointing to list2  
*
* @return the pointer pointing to list of the result
*/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    /* a and b are used to store the number contained in list1 and list2 */
    int a = 0, b = 0, c, i;

    /* get the number contained in list1 */
    i = 0;
    while(l1 != NULL){
        a = a + l1->val * pow(10, i);
        l1 = l1->next;
        i++;
    }
    
    /* get the number contained in list2 */ 
    i = 0;
    while(l2 != NULL){
        b = b + l2->val * pow(10, i);
        l2 = l2->next;
        i++;
    }
    
    /* add two numbers */
    c = a + b;

    /* create a new list to contain the result */
    ListNode* list_entry = new ListNode(c % 10);
    ListNode* list_entry_tmp = list_entry;
    while(c / 10){
        c = c / 10; 
        list_entry_tmp -> next = new ListNode(c % 10);
        list_entry_tmp = list_entry_tmp -> next;
    }   
    
    return list_entry;
}
