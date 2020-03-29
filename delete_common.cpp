#include <stdio.h>
#include<windows.h>
#include<stdlib.h>



typedef struct node
{
	int data;
	struct node* next;
}*LinkList, Node;

LinkList input();
LinkList delete_comm(LinkList pA, LinkList pB, LinkList pC);
void outpu(LinkList pD);


int main()
{
    LinkList pa,pb,pc;
    printf("请输入单链表A:\n");
    pa=input();
    printf("请输入单链表B:\n");
    pb=input();
    printf("请输入单链表C:\n");
    pc=input();
    pa=delete_comm(pa,pb,pc);
    outpu(pa);
    return 0;
}




LinkList input()
{
	int i, n;
	LinkList pa, p, q;
	pa = (LinkList)malloc(sizeof(Node));
	q = pa;
	printf("请输入单链表中的结点个数：_");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		q->next = p;
		printf("数据元素[%d]：", i + 1);
		scanf("%d", &p->data);
		if (q != pa && p->data < q->data)
		{
			printf("ERROR,并非按升序输入，请重新输入\n\n");
			exit(0);
		}
		q = q->next;

	}
	q->next = NULL;
	printf("单链表已建成！\n\n");
	return pa;
}
LinkList delete_comm(LinkList pA, LinkList pB, LinkList pC)
{
	int i = 0;
	LinkList p = NULL, p1, p2, p3, pcomm, pcomm_temp, ptemp;     //p1,p2,p3分别是pA,pB,pC上的指针，pcomm 是存放B,C交集的链表的头指针，p是pcomm上的指针
	pcomm = (LinkList)malloc(sizeof(Node));   //存放B、C共同元素
	if (pA->next == NULL || pB->next == NULL || pC->next == NULL)    //只要有一个链表为空链表，则A中不存在B、C的交集，结果仍未pA
		return pA;
	else
	{                //找到B,C的交集，并将其按升序存放在pcomm链表中
		p2 = pB->next;
		p3 = pC->next;
		pcomm_temp = pcomm;
		while (p2 && p3)
		{
			if (p2->data < p3->data)
				p2 = p2->next;
			else if (p2->data > p3->data)
				p3 = p3->next;
			else
			{
				i++;                                //相当于计数器，用来判断该else 子句是否执行，若没有执行，表明pcomm 为空链表
				p = (LinkList)malloc(sizeof(Node));
				pcomm_temp->next = p;
				p->data = p2->data;
				p2 = p2->next;
				p3 = p3->next;
				pcomm_temp = pcomm_temp->next;
			}
		}
		if (i)
			p->next = NULL;
		else
		{
			pcomm->next = NULL; //设置尾节点
			return pA;  //B、C没有公共元素,直接返回pA
		}
	}
	ptemp = pA;
	p1 = pA->next;    //由上面的语句知，若程序运行到此处，则pA,pB,pC中都知道少含有一个节点
	if (p1->data > p->data)
		return pA;   // pA中的第一个结点（即最小的数据元素），比pcomm中最后一个节点的数据元素还大，显然，A中没有B、C交集
	else
	{
		p = pcomm->next;
		while (p->data < p1->data && p != NULL)
		{
			pcomm->next = p->next;
			free(p);
			p = pcomm->next;
		}
		while (p1 != NULL && p != NULL)
		{

			if (p1->data < p->data)
			{
				ptemp = p1;
				p1 = p1->next;
			}
			else if (p1->data == p->data)
			{
				ptemp->next = p1->next;
				free(p1);
				p1 = ptemp->next;
				pcomm->next = p->next;
				free(p);
				p = pcomm->next;
			}
			else   //即p1->data>p->data
			{
				pcomm->next = p->next;
				free(p);
				p = pcomm->next;
			}
		}
	}
	return pA;
}
void outpu(LinkList pD)
{
	int i = 0;
	LinkList p;
	p = pD->next;
	if (p == NULL)
	{
		printf("该单链表为空表！");
	}
	printf("处理后：\n");
	while (p != NULL)
	{
		printf("数据元素[%d]：%d\n\n", i + 1, p->data);
		p = p->next;
		i++;
	}
}
