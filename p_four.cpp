#include <stdio.h>
#include <stdlib.h>

typedef int ElementType;
typedef struct Node *PtrToNode;
struct Node {
	ElementType Data;
	PtrToNode   Next;
};
typedef PtrToNode List;
List Read();
List Merge(List L1, List L2);
void Print(List L);
/*
int main()
{
	List L1, L2, L;
	L1 = Read();
	L2 = Read();
	L = Merge(L1, L2);
	Print(L);
	Print(L1);
	Print(L2);
	system("pause");
	return 0;
}
*/
void attach(int d, List *Prear)
{
	List newNode;
	newNode = (List)malloc(sizeof(struct Node));
	newNode->Data = d;
	newNode->Next = NULL;
	(*Prear)->Next = newNode;
	*Prear = newNode;
}

List copy(List L)
{
	List CL, rear, t;
	CL = (List)malloc(sizeof(struct Node));
	CL->Next = NULL;
	rear = CL;
	while (L->Next)
	{
		attach(L->Next->Data, &rear);
		t = L;
		L = L->Next;
		t->Next = NULL;
	}
	return CL;
}

List Merge(List L1, List L2)
{
	List L, temp, rear;
	L = (List)malloc(sizeof(struct Node));
	L->Next = NULL;
	rear = L;
	if (!(L1->Next) && !(L2->Next))
		return L;
	if (!(L1->Next) || !(L2->Next))
	{
		if (!(L1->Next))
			return copy(L2);
		else
			return copy(L1);
	}
	while (L1->Next&&L2->Next)
	{
		if (L1->Next->Data <= L2->Next->Data)
		{
			attach(L1->Next->Data, &rear);
			temp = L1;
			L1 = L1->Next;
			temp->Next = NULL;
		}
		else
		{
			attach(L2->Next->Data, &rear);
			temp = L2;
			L2 = L2->Next;
			temp->Next = NULL;
		}
	}
	while (L1->Next)
	{
		attach(L1->Next->Data, &rear);
		temp = L1;
		L1 = L1->Next;
		temp->Next = NULL;
	}
	while (L2->Next)
	{
		attach(L2->Next->Data, &rear);
		temp = L2;
		L2 = L2->Next;
		temp->Next = NULL;
	}
	return L;
}

List Read()
{
	int N, d;
	List P, rear, t;
	P = (List)malloc(sizeof(struct Node));
	//这个先创建的空结点最后要删除，这里申请可以使程序简单
	P->Next = NULL;
	rear = P;
	scanf_s("%d", &N);
	while (N--)
	{
		scanf_s("%d", &d);
		List newNode;
		newNode = (List)malloc(sizeof(struct Node));
		newNode->Data = d;
		newNode->Next = NULL;
		rear->Next = newNode;
		rear = newNode;
	}
	return P;
}

void Print(List P)
{
	int flag = 0;
	if (!(P->Next))
	{
		printf("NULL\n");
		return;
	}
	while (P->Next)
	{
		if (!flag)
			flag = 1;
		else
			printf_s(" ");
		printf_s("%d", P->Next->Data);
		P = P->Next;
	}
	printf_s("\n");
}