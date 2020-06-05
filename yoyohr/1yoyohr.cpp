// yoyohr.cpp : ¶¨Òå¿ØÖÆÌ¨Ó¦ÓÃ³ÌÐòµÄÈë¿Úµã¡£
//


#include <stdio.h>
#include <tchar.h>

#include <iostream>

using namespace std;
typedef struct LNode
{
	int data;
	struct LNode* next;
	int length;
}LinkList;

LinkList* CreateLinkListHead()
{
	LNode *head;
	head = new LNode;
	if (head == nullptr)
	{
		cout << "ÄÚ´æ·ÖÅäÊ§°Ü£¡" << endl;
		exit(0);
	}
	head->length = 1;
	head->next = nullptr;
	return head;
}

void InsertNodeHead(LinkList *L, int data)
{
	LNode *new_node;
	new_node = new LNode;
	new_node->data = data;
	
	new_node->next = L->next;
	L->next = new_node;
	L->length++;
}

void InsertNodeTail(LinkList *L, int data)
{
	LNode *new_node;
	new_node = new LNode;
	new_node->data = data;
	new_node->next = nullptr;

	LNode *p = L;
	while (p->next != nullptr)
	{
		p = p->next;
	}
	p->next = new_node;
}

void InsertNodeIndex(LinkList *L, int data, int indices)
{
	LNode *new_node;
	new_node = new LNode;
	new_node->data = data;
	new_node->next = nullptr;

	LNode *p = L;
	int num = 0;
	while (num != indices)
	{
		p = p->next;
		num++;
	}
	new_node->next = p->next;
	p->next = new_node;
	L->length++;
}

void ShowList(LinkList *L)
{
	LNode *p;
	p = L->next;
	while (p)
	{
		if (p->next == nullptr)
		{
			cout << p->data ;
		}
		else
		{
			cout << p->data << "->";
		}
		p = p->next;
	}
	cout << endl;
}

void SortList(LinkList *L)
{
	LNode *p = L->next, *q;
	int min;
	while (p)
	{
		q = p->next;
		while (q)
		{
			if (p->data > q->data)
			{
				p->data += q->data;
				q->data = p->data - q->data;
				p->data -= q->data;
			}
			q = q->next;
		}
		p = p->next;
	}
}

void MergeList_1(LinkList *L1, LinkList *L2, LinkList *L3)
{
	LNode *p, *q;
	p = L1->next;
	q = L2->next;
	if (p == nullptr && q != nullptr)
	{
		L3->next = L2->next;
	}
	else if (p != nullptr && q == nullptr)
	{
		L3->next = L1->next;
	}
	else
	{
		while (p->next != nullptr || q->next != nullptr)
		{
			if (p->next == nullptr && q->next != nullptr)
			{
				InsertNodeTail(L3, p->data);
				while (q->next != nullptr)
				{
					InsertNodeTail(L3, q->data);
					q = q->next;
				}
				InsertNodeTail(L3, q->data);
			}
			else if (p != nullptr && q == nullptr)
			{
				InsertNodeTail(L3, q->data);
				while (p->next != nullptr)
				{
					InsertNodeTail(L3, p->data);
					p = p->next;
				}
				InsertNodeTail(L3, p->data);
			}
			else if (p->data <= q->data)
			{
				InsertNodeTail(L3, p->data);
				p = p->next;
				InsertNodeTail(L3, q->data);
				q = q->next;
			}
			else if (p->data > q->data)
			{
				InsertNodeTail(L3, q->data);
				q = q->next;
			}
		}
	}
}

void MergeList_2(LinkList *L1, LinkList *L2, LinkList *L3)
{
	LNode *p, *q;
	p = L1->next;
	q = L2->next;
	if (p == nullptr && q != nullptr)
	{
		L3->next = L2->next;
	}
	else if (p != nullptr && q == nullptr)
	{
		L3->next = L1->next;
	}
	else
	{
		if (L1->length <= L2->length)
		{
			L3->next = L2->next;//head
			LNode *r = L3->next;//first node
			
			int i = 0;
			while (r != nullptr)
			{
				
				if (r->data < p->data)
				{
					r = r->next;
					L3 = L3->next;
				}
				else if (r->data >= p->data)
				{
					InsertNodeIndex(L3, p->data, i);
					r = r->next;
					L3 = L3->next;
					p = p->next;
				}
				if (p == nullptr)
					break;
				i++;
			}
			
		}
		else
		{
			L3->next = L1->next;//head
			LNode *r = L3->next;//first node

			int i = 0;
			while (r != nullptr)
			{

				if (r->data < q->data)
				{
					r = r->next;
					L3 = L3->next;
				}
				else if (r->data >= q->data)
				{
					InsertNodeIndex(L3, q->data, i);
					r = r->next;
					L3 = L3->next;
					q = q->next;
				}
				if (q == nullptr)
					break;
				i++;
			}
		}
	}
}

int main()
{
	cout << "ÊäÈëµÚÒ»¸öÁ´±íÊý¾Ý:" << endl;
	LinkList *L1 = nullptr;
	L1 = CreateLinkListHead();
	for (size_t i = 0; i < 13; i++)
	{
		InsertNodeHead(L1, i);
	}
	SortList(L1);
	ShowList(L1);
	cout << "ÊäÈëµÚ¶þ¸öÁ´±íÊý¾Ý:" << endl;
	LinkList *L2 = nullptr;
	L2 = CreateLinkListHead();
	for (size_t i = 0; i < 5; i++)
	{
		InsertNodeHead(L2, i);
	}
	SortList(L2);
	ShowList(L2);
	cout << "ºÏ²¢Á½¸öÁ´±í²¢Êä³ö:" << endl;
	LinkList *L3 = nullptr;
	L3 = CreateLinkListHead();
	//MergeList_1(L1, L2, L3);
	MergeList_2(L1, L2, L3);
	ShowList(L3);
	system("pause");
    return 0;
}

