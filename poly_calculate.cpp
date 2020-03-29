#include <stdio.h>
#include<windows.h>
#include<stdlib.h>

typedef struct node
{
	int coef, exp;
	struct node* next;
}*poly, Node;

void menu();
poly input_poly();
poly input_polies();
void output_poly(poly pb);
void reverse_poly(poly pc);
void deriva_poly(poly pd);
poly add_polies(poly pe, poly pf);
void goto_menu();

int main()
{
	int i, control, goback = 1;
	poly pa, pb;
	menu();
	while (1)
	{
		scanf("%d", &control);
		if (control == 1)
		{
			system("cls");
			pa = input_poly();
			goto_menu();

		}
		else if (control == 2)
		{
			system("cls");
			pa = input_poly();
			printf("\n\n֮ǰ����Ķ���ʽ:\n");
			output_poly(pa);
			goto_menu();

		}
		else if (control == 3)
		{
			system("cls");
			pa = input_poly();
			printf("\n���ú�Ķ���ʽ:\n");
			reverse_poly(pa);
			goto_menu();
		}
		else if (control == 4)
		{
			system("cls");
			pa = input_poly();
			printf("\n�󵼺�Ķ���ʽ:\n");
			deriva_poly(pa);
			goto_menu();
		}
		else if (control == 5)
		{
			system("cls");
			printf("����ʽ��");
			pa = input_poly();
			printf("\n��ʽ��");
			pb = input_poly();
			printf("\n��ͺ�Ķ���ʽ:\n");
			add_polies(pa, pb);
			goto_menu();
		}
		else
		{
			system("cls");
			printf("��Ч��ָ����������룡");
			goto_menu();
		}
	}
	return 0;
}


void menu()
{
	int i, j;

	for (i = 0; i < 2; i++)
		printf("\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[1]�����������ʽ\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[2]���һԪ����ʽ\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[3]�͵����ò��������һԪ����ʽ\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[4]��һԪ����ʽ����\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[5]������һԪ����ʽ�ĺ�\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("���������ָ��:_");

}
void goto_menu()
{
	int goback = 1;
	printf("\n\n����������0�Է������˵�_");
	scanf("%d", &goback);
	if (!goback)
	{
		system("cls");
		menu();
	}
}
poly input_poly()
{
	int i, n;
	poly px, ph, pa;
	pa = (poly)malloc(sizeof(Node));
	ph = pa;
	printf("���ʴ�����Ķ���ʽ�м��  _");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		px = (poly)malloc(sizeof(Node));
		ph->next = px;
		printf("\n��%d�ϵ����", i + 1);
		scanf("%d", &px->coef);
		printf("       ָ����", i + 1);
		scanf("%d", &px->exp);
		if (px->exp < ph->exp && ph != pa)
		{
			printf("ERROR,���ǰ��������룬����������");
			Sleep(3000);
			exit(0);
		}
		ph = ph->next;
	}
	ph->next = NULL;
	printf("\nһԪ����ʽ������ɣ�");
	Sleep(500);
	return pa;
}
void output_poly(poly pb)
{
	int i = 0;
	poly pn;
	for (pn = pb->next; pn != NULL; pn = pn->next)
	{
		printf("\n��%d�ϵ����%d", i + 1, pn->coef);
		printf("\n       ָ����%d", pn->exp);
		i++;
	}

}
void reverse_poly(poly pc)
{
	poly pm, pn;
	if (pc->next == NULL)
	{
		printf("�ö���ʽ���ʽΪ0����������\n");
	}
	if ((pc->next)->next == NULL)
	{
		printf("�ö���ʽֻ��һ���������\n");
	}
	pm = (pc->next)->next;
	(pc->next)->next = NULL;
	while (pm != NULL)
	{
		pn = pm;
		pm = pm->next;
		pn->next = pc->next;
		pc->next = pn;
	}
	output_poly(pc);
}
void deriva_poly(poly pd)
{
	int i = 0;
	poly pm, pn;
	for (pm = pd->next; pm != NULL; pm = pm->next)
	{
		pm->coef *= pm->exp;
		(pm->exp)--;
	}
	pn = pd;
	pm = pd->next;
	while (pm != NULL)   //ɾ��ϵ��Ϊ0�Ľ��ռ�
	{
		if (pm->coef == 0)
		{
			pn->next = pm->next;
			free(pm);
			pm = pn->next;
		}
		else
		{
			printf("�󵼺󣬵�%d���ϵ��Ϊ_%d\n", i + 1, pm->coef);
			printf("�󵼺󣬵�%d���ָ��Ϊ_%d\n", i + 1, pm->exp);
			pn = pm;
			pm = pm->next;
			i++;
		}
	}
}
poly add_polies(poly pe, poly pf)
{
	poly p1, p=NULL, p2=NULL;
	if (pe->next == NULL)
		pe = pf;
	else if (pf->next == NULL)
	{

	}
	else
	{
		p = pe;   //��¼p1��ǰ���ڵ�
		p1 = pe->next;
		p2 = pf->next;
		while (p1 && p2)
		{

			if (p1->exp < p2->exp)
			{
				p = p1;
				p1 = p1->next;
			}
			else if (p1->exp == p2->exp)
			{
				p1->coef += p2->coef;
				if (p1->coef == 0)
				{
					p->next = p1->next;
					free(p1);
					p1 = p->next;
				}
				else
				{
					p = p1;
					p1 = p1->next;
				}
				pf->next = p2->next;
				free(p2);
				p2 = pf->next;
			}
			else
			{
				pf->next = p2->next;
				p->next = p2;
				p2->next = p1;
				p = p2;
				p2 = pf->next;
			}

		}
	}
	if (p2 != NULL)
		p->next = p2;
	output_poly(pe);
	return pe;
}


