#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BUFFER 100

typedef struct LinkNode *PtrToNode;
struct LinkNode {
	char Addr[6];
	int Data;
	char NextAddr[6];
	PtrToNode Next;
	int tag;
};
typedef PtrToNode RList;

RList ReadRList(int *N, int *K);
void ReverseKth(int K, int N, RList RL);
void PrintRList(RList RL);
PtrToNode FindKth(int K, RList RL, PtrToNode *minusK);
void reverseList(RList RL);

RList ReadRList(int *pN, int *pK)
{
	int  N, K, i, j;
	RList RL, rear;
	RL = (RList)malloc(sizeof(struct LinkNode));
	RL->Next = NULL;
	RL->Addr[0] = 'S';
	RL->Addr[1] = '\0';
	rear = RL;
	scanf("%s", rear->NextAddr);
	scanf("%d", &N);
	scanf("%d", &K);
	PtrToNode Nodes;
	Nodes = (PtrToNode)malloc(sizeof(struct LinkNode)*N);

	for (i = 0; i < N; i++)
	{
		Nodes[i].tag = 0;
		scanf("%s", Nodes[i].Addr);
		scanf("%d", &Nodes[i].Data);
		scanf("%s", Nodes[i].NextAddr);
	}
	int count = 0;
	while (count!=N)
	{
		for (i = 0; i < N; i++)
		{			
			if (Nodes[i].tag == 0 && !strcmp(Nodes[i].Addr,rear->NextAddr))
			{
				count++;
				rear->Next = &Nodes[i];
				Nodes[i].Next = NULL;
				Nodes[i].tag = 1;
				rear = &Nodes[i];
			}			
		}
	}
	rear->Next = NULL;
	*pN = N;
	*pK = K;
	return RL;
}

void ReverseKth(int K, int N ,RList RL)
{
	if (K == 1)
		return;
	if (K == N)
	{
		reverseList(RL);
		return;
	}
	int sections = N / K;
	int i, j;
	RList tRL = RL->Next;
	RList *heads, *tails, *lists, tmp;
	heads = (RList*)malloc(sizeof(RList)*sections + 1);
	tails = (RList*)malloc(sizeof(RList)*sections + 1);
	lists = (RList*)malloc(sizeof(RList)*(sections + 1));
	for (i = 0; i < sections; i++)
	{
		heads[i] = FindKth(K*i + 1, tRL, &tmp);
		tails[i] = FindKth(K*(i+1), tRL, &tmp);
		lists[i] = (RList)malloc(sizeof(struct LinkNode));
		lists[i]->Next = heads[i];
	}
	if (N%K != 0)
	{
		heads[sections] = FindKth(K*sections + 1, tRL, &tmp);
		tails[sections] = FindKth(N, tRL, &tmp);
		lists[sections] = (RList)malloc(sizeof(struct LinkNode));
		lists[sections]->Next = heads[sections];
	}
	PtrToNode rear = RL;
	for (i = 0; i < sections; i++)
	{
		tails[i]->Next = NULL;
		reverseList(lists[i]);
		rear->Next = lists[i]->Next;
		strcpy(rear->NextAddr, lists[i]->Next->Addr);
		rear = FindKth(K, lists[i]->Next, &tmp);
	}
	
	rear->Next = lists[sections]->Next;
	strcpy(rear->NextAddr, lists[sections]->Next->Addr);
	PtrToNode last = FindKth(N+1, RL, &tmp);
	last->NextAddr[0] = '-';
	last->NextAddr[1] = '1';
	last->NextAddr[2] = '\0';
}

void reverseList(RList RL)
{
	PtrToNode node1, node2;
	node1 = RL->Next;
	RL->Next = NULL;
	RL->NextAddr[0] = '-';
	RL->NextAddr[1] = '1';
	RL->NextAddr[2] = '\0';
	node2 = node1->Next;
	while (node1)
	{
		node2 = node1->Next;
		node1->Next = RL->Next;
		strcpy(node1->NextAddr,RL->NextAddr);
		RL->Next = node1;
		strcpy(RL->NextAddr ,node1->Addr);
		node1 = node2;
	}
	//PrintRList(RL);
}

PtrToNode FindKth(int K, RList RL, PtrToNode *minusK)
{
	if (!RL)
		return NULL;
	if (K == 0) {
		*minusK = NULL;
		return NULL;
	}
	int count = 1;
	PtrToNode Kth;
	Kth = RL;
	(*minusK) = NULL;
	while (Kth)
	{
		if (count == K)
			break;
		else
		{
			(*minusK) = Kth;
			Kth = Kth->Next;
			count++;
		}
	}
	return Kth;
}

void PrintRList(RList RL)
{
	RList tRL;
	
	tRL = RL->Next;
	int count = 0;
	while (tRL)
	{
		printf("%s %d %s\n", tRL->Addr, tRL->Data, tRL->NextAddr);
		tRL = tRL->Next;
		count++;
	}
}

int main(void)
{
	RList RL;
	int N, K;
	RL = ReadRList(&N, &K);
	ReverseKth(K, N, RL);
	PrintRList(RL);
	system("pause");
	return 0;
}