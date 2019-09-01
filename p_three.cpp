/*
 多项式的相加与相乘
 1.动态数组
 2.链表
 */
#include <stdio.h>
#include <stdlib.h>

//link list definition
typedef struct PolyNode* Polynomial;
struct PolyNode {
	int coef;
	int expon;
	Polynomial link;
};

Polynomial ReadPoly();
Polynomial Mult(Polynomial P1, Polynomial P2);
Polynomial Sum(Polynomial P1, Polynomial P2);
void PrintPoly(Polynomial P);
static void Attach(int c, int e, Polynomial *Prear);
int Compare(int a, int b);

/*
int main()
{
	Polynomial P1, P2, Psum, Pmul;

	//1.读入多项式1
	P1 = ReadPoly();
	//2.读入多项式2
	P2 = ReadPoly();
	//3.乘法运算并输出
	Pmul = Mult(P1, P2);
	PrintPoly(Pmul);
	//4.加法运算并输出
	Psum = Sum(P1, P2);
	PrintPoly(Psum);
	system("pause");
	return 0;
}
*/

int Compare(int a, int b)
{
	if (a > b)
		return 1;
	else if (a < b)
		return -1;
	else return 0;
}

Polynomial ReadPoly()
{
	int N,c,e;
	Polynomial P,rear,t;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	//这个先创建的空结点最后要删除，这里申请可以使程序简单
	P->link = NULL;
	rear = P;
	scanf_s("%d", &N);
	while (N--)
	{
		scanf_s("%d %d", &c, &e);
		Attach(c, e, &rear); // 传指针保证在Attach函数中能被改变
	}
	t = P;
	P = P->link;
	free(t);
	//使返回的链表开头就是不为空的结点
	return P;
}

static void Attach(int c, int e, Polynomial *Prear)
{
	Polynomial newNode;
	newNode = (Polynomial)malloc(sizeof(struct PolyNode));
	newNode->coef = c;
	newNode->expon = e;
	newNode->link = NULL;
	(*Prear)->link = newNode;
	*Prear = newNode;
}

Polynomial Mult(Polynomial P1, Polynomial P2)
{
	Polynomial P, rear, t1, t2, t;
	int c, e;
	if (!P1 || !P2) return NULL;
	
	t1 = P1;
	t2 = P2;
	P = (Polynomial)malloc(sizeof(struct PolyNode));
	P->link = NULL;
	rear = P;
	//先用P1的第一项乘以P2的每一项得到一个初始结果链表(始终保持指数递降顺序),将问题转变为一个新的项如何插入的问题
	while (t2)
	{
		Attach(t1->coef*t2->coef, t1->expon + t2->expon, &rear);
		t2 = t2->link;
	}
	t1 = t1->link;
	while (t1)
	{
		t2 = P2;
		rear = P;
		while (t2)
		{
			e = t1->expon + t2->expon;
			c = t1->coef* t2->coef;
			while (rear->link && rear->link->expon > e)
				rear = rear->link;
			if (rear->link && rear->link->expon == e)
			{
				if (rear->link->coef + c)
					rear->link->coef += c;
				else {
					t = rear->link;
					rear->link = t->link;
					free(t);
				}
			}
			else
			{
				t = (Polynomial)malloc(sizeof(struct PolyNode));
				t->coef = c;
				t->expon = e;
				t->link = rear->link;
				rear->link = t;
				rear = rear->link;
			}
			t2 = t2->link;
		}
		t1 = t1->link;
	}
	t2 = P;
	P = P->link;
	free(t2);
	return P;
}

Polynomial Sum(Polynomial P1, Polynomial P2)
{
	Polynomial front, rear, temp;
	int sum;
	rear = (Polynomial)malloc(sizeof(struct PolyNode));
	//由front记录结果多项式链表头结点
	front = rear;
	while (P1&&P2)
	{
		switch (Compare(P1->expon, P2->expon))
		{
		case 1:
			Attach(P1->coef, P1->expon, &rear);
			P1 = P1->link;
			break;
		case -1:
			Attach(P2->coef, P2->expon, &rear);
			P2 = P2->link;
			break;
		case 0:
			sum = P1->coef + P2->coef;
			//printf_s("sum = %d\n", sum);
			if(sum)
				Attach(sum, P1->expon, &rear);
			P1 = P1->link;
			P2 = P2->link;
			break;
		}
	}

	for (; P1; P1 = P1->link)
		Attach(P1->coef, P1->expon, &rear);
	for (; P2; P2 = P2->link)
		Attach(P2->coef, P2->expon, &rear);
	rear->link = NULL;
	temp = front;
	front = front->link;
	free(temp);
	return front;
}

void PrintPoly(Polynomial P)
{
	int flag = 0;
	if (!P)
	{
		printf("0 0\n");
		return;
	}
	while (P)
	{
		if (!flag)
			flag = 1;
		else
			printf_s(" ");
		printf_s("%d %d", P->coef, P->expon);
		P = P->link;
	}
	printf_s("\n");
}