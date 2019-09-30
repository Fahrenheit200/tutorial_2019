#include<iostream>
#include<stdlib.h>
using namespace std;
/*1，输入数据，链表的数据格式为倒序，
* 2,对输入的数据进行相加，添入进位机制
* 3，输入相加后的结果
****定义结构体ListNode,使其具有链表的性质，供自己使用
*/


struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) :val(x), next(NULL) {
		//定义自己需要使用的指针和变量，函数
	}
};

ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
	ListNode* result = new ListNode(0);  //使用结果来对应返回值 
	int xpb = 0, xpb1 = 0, xpb2 = 0;
	for (int i = 1; l1 != NULL; i = 10 * i) {
		xpb1 += i * l1->val;		//xpb1用来获取L1，的大小
		l1 = l1->next;
	}
	for (int i = 1; l2->next != NULL; i = 10 * i) {
		xpb2 += i * l2->val;	//xpb2用来获取L2的大小
		l2 = l2->next;
	}
	xpb = xpb1 + xpb2;	//xpb为L1,L1大小之和
	int hahaha = 0;
	while (xpb != 0)
	{
		hahaha = xpb % 10;
		xpb /= 10;
		result->val = hahaha;
		cout << "->" << hahaha ;	//将xpb从个位一次写入结果链中
		result->next = result;
	}
	return result;
}
