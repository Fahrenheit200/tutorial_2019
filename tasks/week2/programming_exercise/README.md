## listAddtion

- Author: JiLi Liao
- Revised: JiLi Liao
- Date: 2019-09-25
- Version: 1.0.0
- Abstract: A C++ function to  add 2 lists which are consist of positive integer

###Depend Libraries
```
<cmath>
```

### Interface

```C++
/* listAddtion.cpp内已经包含ListNode的声明 */

/** 
* @brief  add two list and create a new list containing the result
* @param[in]  l1  --  pointer pointing to list1 
* @param[in]  l2  --  pointer pointing to list2  
*
* @return the pointer pointing to list of the result
*/
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2);
```

### Sample Input
```
链表A 1->2->3
链表B 3->4->5
```

### Sample Output
```
链表C 4->6->8
```
