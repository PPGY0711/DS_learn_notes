/*
 ����ʽ����������
 1.��̬����
 2.����
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

	//1.�������ʽ1
	P1 = ReadPoly();
	//2.�������ʽ2
	P2 = ReadPoly();
	//3.�˷����㲢���
	Pmul = Mult(P1, P2);
	PrintPoly(Pmul);
	//4.�ӷ����㲢���
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
	//����ȴ����Ŀս�����Ҫɾ���������������ʹ�����
	P->link = NULL;
	rear = P;
	scanf_s("%d", &N);
	while (N--)
	{
		scanf_s("%d %d", &c, &e);
		Attach(c, e, &rear); // ��ָ�뱣֤��Attach�������ܱ��ı�
	}
	t = P;
	P = P->link;
	free(t);
	//ʹ���ص�����ͷ���ǲ�Ϊ�յĽ��
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
	//����P1�ĵ�һ�����P2��ÿһ��õ�һ����ʼ�������(ʼ�ձ���ָ���ݽ�˳��),������ת��Ϊһ���µ�����β��������
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
	//��front��¼�������ʽ����ͷ���
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