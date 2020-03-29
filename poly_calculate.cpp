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
			printf("\n\n之前输入的多项式:\n");
			output_poly(pa);
			goto_menu();

		}
		else if (control == 3)
		{
			system("cls");
			pa = input_poly();
			printf("\n逆置后的多项式:\n");
			reverse_poly(pa);
			goto_menu();
		}
		else if (control == 4)
		{
			system("cls");
			pa = input_poly();
			printf("\n求导后的多项式:\n");
			deriva_poly(pa);
			goto_menu();
		}
		else if (control == 5)
		{
			system("cls");
			printf("被加式：");
			pa = input_poly();
			printf("\n加式：");
			pb = input_poly();
			printf("\n求和后的多项式:\n");
			add_polies(pa, pb);
			goto_menu();
		}
		else
		{
			system("cls");
			printf("无效的指令，请重新输入！");
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
	printf("[1]升序输入多项式\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[2]输出一元多项式\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[3]就地逆置并降序输出一元多项式\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[4]求一元多项式导数\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("[5]求两个一元多项式的和\n\n\n\n");
	for (i = 0; i < 50; i++)
		printf(" ");
	printf("请输入操作指令:_");

}
void goto_menu()
{
	int goback = 1;
	printf("\n\n请输入数字0以返回主菜单_");
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
	printf("请问待输入的多项式有几项？  _");
	scanf("%d", &n);
	for (i = 0; i < n; i++)
	{
		px = (poly)malloc(sizeof(Node));
		ph->next = px;
		printf("\n第%d项：系数：", i + 1);
		scanf("%d", &px->coef);
		printf("       指数：", i + 1);
		scanf("%d", &px->exp);
		if (px->exp < ph->exp && ph != pa)
		{
			printf("ERROR,并非按升序输入，请重新输入");
			Sleep(3000);
			exit(0);
		}
		ph = ph->next;
	}
	ph->next = NULL;
	printf("\n一元多项式输入完成！");
	Sleep(500);
	return pa;
}
void output_poly(poly pb)
{
	int i = 0;
	poly pn;
	for (pn = pb->next; pn != NULL; pn = pn->next)
	{
		printf("\n第%d项：系数：%d", i + 1, pn->coef);
		printf("\n       指数：%d", pn->exp);
		i++;
	}

}
void reverse_poly(poly pc)
{
	poly pm, pn;
	if (pc->next == NULL)
	{
		printf("该多项式表达式为0，无需逆置\n");
	}
	if ((pc->next)->next == NULL)
	{
		printf("该多项式只有一项，无需逆置\n");
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
	while (pm != NULL)   //删除系数为0的结点空间
	{
		if (pm->coef == 0)
		{
			pn->next = pm->next;
			free(pm);
			pm = pn->next;
		}
		else
		{
			printf("求导后，第%d项的系数为_%d\n", i + 1, pm->coef);
			printf("求导后，第%d项的指数为_%d\n", i + 1, pm->exp);
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
		p = pe;   //记录p1的前驱节点
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


