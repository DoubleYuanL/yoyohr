// yoyohr.cpp : 定义控制台应用程序的入口点。
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

class LinkLists
{
public:
	LinkLists();
	~LinkLists();
	LinkList* CreateLinkListHead();
	void InsertNodeHead(int data);
	void InsertNodeTail(int data);
	void InsertNodeIndex(int data, int indices);
	void ShowList();
	void SortList();
	void MergeList_1(LinkList *L1, LinkList *L2);
	void MergeList_2(LinkList *L1, LinkList *L2);

	LinkList *L;
};

LinkLists::LinkLists()
{
}

LinkLists::~LinkLists()
{
}

LinkList* LinkLists::CreateLinkListHead()
{
	LNode *head;
	head = new LNode;
	if (head == nullptr)
	{
		cout << "内存分配失败！" << endl;
		exit(0);
	}
	head->length = 1;
	head->next = nullptr;
	return head;
}

void LinkLists::InsertNodeHead(int data)
{
	LNode *new_node;
	new_node = new LNode;
	new_node->data = data;

	new_node->next = L->next;
	L->next = new_node;
	L->length++;
}

void LinkLists::InsertNodeTail(int data)
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

void LinkLists::InsertNodeIndex(int data, int indices)
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

void LinkLists::ShowList()
{
	LNode *p;
	p = L->next;
	while (p)
	{
		if (p->next == nullptr)
		{
			cout << p->data;
		}
		else
		{
			cout << p->data << "->";
		}
		p = p->next;
	}
	cout << endl;
}

void LinkLists::SortList()
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

void LinkLists::MergeList_1(LinkList *L1, LinkList *L2)
{
	LNode *p, *q;
	p = L1->next;
	q = L2->next;
	if (p == nullptr && q != nullptr)
	{
		L->next = L2->next;
	}
	else if (p != nullptr && q == nullptr)
	{
		L->next = L1->next;
	}
	else
	{
		while (p->next != nullptr || q->next != nullptr)
		{
			if (p->next == nullptr && q->next != nullptr)
			{
				InsertNodeTail(p->data);
				while (q->next != nullptr)
				{
					InsertNodeTail(q->data);
					q = q->next;
				}
				InsertNodeTail(q->data);
			}
			else if (p != nullptr && q == nullptr)
			{
				InsertNodeTail(q->data);
				while (p->next != nullptr)
				{
					InsertNodeTail(p->data);
					p = p->next;
				}
				InsertNodeTail(p->data);
			}
			else if (p->data <= q->data)
			{
				InsertNodeTail(p->data);
				p = p->next;
				InsertNodeTail(q->data);
				q = q->next;
			}
			else if (p->data > q->data)
			{
				InsertNodeTail(q->data);
				q = q->next;
			}
		}
	}
}

void LinkLists::MergeList_2(LinkList *L1, LinkList *L2)
{
	LNode *p, *q;
	p = L1->next;
	q = L2->next;
	if (p == nullptr && q != nullptr)
	{
		L->next = L2->next;
	}
	else if (p != nullptr && q == nullptr)
	{
		L->next = L1->next;
	}
	else
	{
		if (L1->length <= L2->length)
		{
			L->next = L2->next;//head
			LNode *h = L;//head node
			LNode *r = L->next;//first node
			int i = 0;
			while (r != nullptr)
			{
				if (r->data < p->data)
				{
					r = r->next;
					h = h->next;
				}
				else if (r->data >= p->data)
				{
					InsertNodeIndex(p->data, i);
					r = r->next;
					h = h->next;
					p = p->next;
				}
				if (p == nullptr)
					break;
				i+=2;
			}

		}
		else
		{
			L->next = L1->next;//head
			LNode *h = L;//head node
			LNode *r = L->next;//first node

			int i = 0;
			while (r != nullptr)
			{
				if (r->data < q->data)
				{
					r = r->next;
					h = h->next;
				}
				else if (r->data >= q->data)
				{
					InsertNodeIndex(q->data, i);
					r = r->next;
					h = h->next;
					q = q->next;
				}
				if (q == nullptr)
					break;
				i+=2;
			}
		}
	}
}

int main()
{
	cout << "输入第一个链表数据:" << endl;
	LinkLists L1;
	L1.L = L1.CreateLinkListHead();
	for (size_t i = 0; i < 13; i++)
	{
		L1.InsertNodeHead(i);
	}
	L1.SortList();
	L1.ShowList();
	cout << "输入第二个链表数据:" << endl;
	LinkLists L2;
	L2.L = L2.CreateLinkListHead();
	for (size_t i = 0; i < 5; i++)
	{
		L2.InsertNodeHead(i);
	}
	L2.SortList();
	L2.ShowList();
	cout << "合并两个链表并输出:" << endl;
	LinkLists L3;
	L3.L = L3.CreateLinkListHead();
	//L3.MergeList_1(L1.L, L2.L);
	L3.MergeList_2(L1.L, L2.L);
	L3.ShowList();
	system("pause");
	return 0;
}

