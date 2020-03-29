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
    printf("�����뵥����A:\n");
    pa=input();
    printf("�����뵥����B:\n");
    pb=input();
    printf("�����뵥����C:\n");
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
	printf("�����뵥�����еĽ�������_");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		p = (LinkList)malloc(sizeof(Node));
		q->next = p;
		printf("����Ԫ��[%d]��", i + 1);
		scanf("%d", &p->data);
		if (q != pa && p->data < q->data)
		{
			printf("ERROR,���ǰ��������룬����������\n\n");
			exit(0);
		}
		q = q->next;

	}
	q->next = NULL;
	printf("�������ѽ��ɣ�\n\n");
	return pa;
}
LinkList delete_comm(LinkList pA, LinkList pB, LinkList pC)
{
	int i = 0;
	LinkList p = NULL, p1, p2, p3, pcomm, pcomm_temp, ptemp;     //p1,p2,p3�ֱ���pA,pB,pC�ϵ�ָ�룬pcomm �Ǵ��B,C�����������ͷָ�룬p��pcomm�ϵ�ָ��
	pcomm = (LinkList)malloc(sizeof(Node));   //���B��C��ͬԪ��
	if (pA->next == NULL || pB->next == NULL || pC->next == NULL)    //ֻҪ��һ������Ϊ��������A�в�����B��C�Ľ����������δpA
		return pA;
	else
	{                //�ҵ�B,C�Ľ����������䰴��������pcomm������
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
				i++;                                //�൱�ڼ������������жϸ�else �Ӿ��Ƿ�ִ�У���û��ִ�У�����pcomm Ϊ������
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
			pcomm->next = NULL; //����β�ڵ�
			return pA;  //B��Cû�й���Ԫ��,ֱ�ӷ���pA
		}
	}
	ptemp = pA;
	p1 = pA->next;    //����������֪�����������е��˴�����pA,pB,pC�ж�֪���ٺ���һ���ڵ�
	if (p1->data > p->data)
		return pA;   // pA�еĵ�һ����㣨����С������Ԫ�أ�����pcomm�����һ���ڵ������Ԫ�ػ�����Ȼ��A��û��B��C����
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
			else   //��p1->data>p->data
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
		printf("�õ�����Ϊ�ձ�");
	}
	printf("�����\n");
	while (p != NULL)
	{
		printf("����Ԫ��[%d]��%d\n\n", i + 1, p->data);
		p = p->next;
		i++;
	}
}
