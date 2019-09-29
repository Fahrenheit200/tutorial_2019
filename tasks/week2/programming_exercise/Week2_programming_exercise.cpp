/*****************************************************************
 * @file        addTwoNumbers.cpp
 * @brief       这是一个用于计算两个链表加法的函数，输入两个链表的指针，返回一个链表的指针，返回指针的节点数值为输入链表的值之和
 * Details.
 *
 * @Author      Lomgahong
 * @email       1073097404@qq.com
 * @version     1.0.0
 * ---------------------------------------------------------------
 * Change History:
 *    <Date>  |<Version>|<Author> |<Description>
 * 2019/09/29 |  1.0.0  |Lomgahong|Create file
 *---------------------------------------------------------------
 *
 * **************************************************************/

/**
 * 链表节点的定义 
 * struct ListNode{
 *	int val;
 *	ListNode *next;
 *	ListNode(int x):val(x),next(NULL){}
 * }; 
*/


/**
 * 用于计算链表加法的函数
 */
ListNode* addTwoNumbers(ListNode* l1,ListNode* l2){
	//新建头指针用于储存结果
	ListNode *p=new ListNode(0);
	ListNode *result=p;
	//这两个指针用于引入计算量
    	ListNode *p1=l1;
    	ListNode *p2=l2;
    	//定义flag来标记是否进位
    	int flag=0;
	//当数据未输入完毕前或前一位有进位时，继续循环
    	while (p1!=NULL||p2!=NULL||flag==1){
		//记录进位
        	int temp=flag;
		//将两链表相同位置的数相加
        	if(p1!=NULL) {
            		temp+=p1->val;
            		p1=p1->next;
        	}
        	if (p2!=NULL){
            		temp+=p2->val;
            		p2=p2->next;
        	}
		//判断是否进位
        	if(temp>9){
            		temp-=10;
            		flag=1;
        	} 
		else{
            		flag=0;
       		}
		//如果数据读取完毕，则下一个节点为空
        	if(p1==NULL&&p2==NULL&&flag==0)
        		p->next=NULL;
		//否则，建立下一个节点
        	else
        		p->next=new ListNode(0);
		//记录当前节点的值
        	p->val=temp;
		//跳到下一个节点
		p=p->next;  	
    }
    return result;
};



