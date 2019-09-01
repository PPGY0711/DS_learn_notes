#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 30
typedef struct Stack *stack;
typedef int ElementType;
struct Stack
{
	ElementType Data[MAXSIZE];
	int top;
	int capacity;
};

typedef struct TreeNode *BinTree;
struct TreeNode
{
	ElementType Data;
	BinTree Left;
	BinTree Right;
};

stack createStack();
int isEmpty(stack s);
int isFull(stack s);
void Push(stack s, ElementType e);
ElementType Pop(stack s);

void getInorderTraversal(int *pN, ElementType *prearr, ElementType *inarr, stack s);
BinTree BuildTree(ElementType* inarr, ElementType* prearr, int N);
void PostOrderTraversal(BinTree BT, int N);

stack createStack()
{
	stack s;
	s = (stack)malloc(sizeof(struct Stack));
	s->top = -1;
	s->capacity = MAXSIZE;
	return s;
}

int isEmpty(stack s)
{
	return (s->top == -1);
}

int isFull(stack s)
{
	return (s->top == s->capacity - 1);
}

void Push(stack s, ElementType e)
{
	if (!isFull(s))
	{
		s->Data[++(s->top)] = e;
	}
}

ElementType Pop(stack s)
{
	if (!isEmpty(s))
	{
		return s->Data[(s->top)--];
	}
	else
		return NULL;
}

void getInorderTraversal(int *pN, ElementType *prearr, ElementType *inarr, stack s)
{
	int i, j, k, N;
	char cmd[5];
	ElementType e;
	scanf("%d\n", &N);
	(*pN) = N;
	j = k = 0;
	for (i = 0; i < 2*N; i++)
	{
		scanf("%s", cmd);
		if (!strcmp(cmd, "Push"))
		{
			scanf("%d", &e);
			prearr[j++] = e;
			Push(s, e);
		}
		else
		{
			inarr[k++] = Pop(s);
		}
	}
}

BinTree BuildTree(ElementType* inarr, ElementType* prearr, int N)
{
	if (!N)
		return NULL;
	BinTree root;
	root = (BinTree)malloc(sizeof(struct TreeNode));
	root->Left = NULL;
	root->Right = NULL;
	root->Data = prearr[0];
	if (N == 1)
		return root;
	int llen, rlen;
	llen = rlen = 0;
	int i, j;
	while (inarr[llen] != prearr[0])
	{
		llen++;
	}

	rlen = N - 1 - llen;
	if (llen > 0)
	{
		ElementType *linarr, *lprearr;
		linarr = (ElementType*)malloc(sizeof(ElementType)*llen);
		memset(linarr, 0, sizeof(ElementType)*llen);
		lprearr = (ElementType*)malloc(sizeof(ElementType)*llen);
		memset(lprearr, 0, sizeof(ElementType)*llen);
		for (j = 0; j < llen; j++)
		{
			linarr[j] = inarr[j];
			lprearr[j] = prearr[1 + j];
		}
		root->Left = BuildTree(linarr, lprearr, llen);
	}
	if (rlen > 0)
	{
		ElementType *rinarr, *rprearr;
		rinarr = (ElementType*)malloc(sizeof(ElementType)*rlen);
		memset(rinarr, 0, sizeof(ElementType)*rlen);
		rprearr = (ElementType*)malloc(sizeof(ElementType)*rlen);
		memset(rprearr, 0, sizeof(ElementType)*rlen);
		for (j = 1; j <= rlen; j++)
		{
			rinarr[j-1] = inarr[j + llen];
			rprearr[j-1] = prearr[j + llen];
		}
		root->Right = BuildTree(rinarr, rprearr, rlen);
	}
	return root;
}

void PostOrderTraversal(BinTree BT, int N)
{
	static int count = 0;
	if (BT)
	{
		PostOrderTraversal(BT->Left, N);
		PostOrderTraversal(BT->Right, N);
		count++;
		if (count == 1)
			printf("%d", BT->Data);
		else
			printf(" %d", BT->Data);
	}
}

int main()
{
	stack s;
	s = createStack();
	int N;
	int prearr[MAXSIZE], inarr[MAXSIZE];
	getInorderTraversal(&N, prearr, inarr, s);
	int i;
	
	BinTree BT;
	BT = BuildTree(inarr, prearr, N);
	PostOrderTraversal(BT, N);

	system("PAUSE");
	return 0;
}