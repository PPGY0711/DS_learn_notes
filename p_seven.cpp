#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX 100
#define MaxTree 10
#define ElementType char
#define Tree int
#define Null -1

struct TreeNode
{
	ElementType Element;
	Tree Left;
	Tree Right;
}T1[MaxTree], T2[MaxTree];

Tree BuildTree(struct TreeNode T[], int *pN);
int Isomorphic(Tree R1, Tree R2);
void printLeaves(Tree R1, int N);

int main()
{
	int N;
	Tree R1, R2;
	R1 = BuildTree(T1, &N);

	//R2 = BuildTree(T2);
	/*
	if (Isomorphic(R1, R2))
		printf("Yes\n");
	else
		printf("No\n");
	*/
	printLeaves(R1, N);
	system("pause");
	return 0;
}

Tree BuildTree(struct TreeNode T[], int *pN)
{
	Tree Root = Null;
	int N,i;
	int check[MaxTree];
	char cl[2], cr[2];
	scanf("%d", &N);
	//getchar();
	if (N)
	{
		for (i = 0; i < N; i++)
			check[i] = 0;
		for (i = 0; i < N; i++)
		{
			T[i].Element = i;
			scanf("%s %s",&cl, &cr);
			//getchar();
			if (cl[0] != '-') {
				T[i].Left = cl[0] - '0';
				check[T[i].Left] = 1;
			}
			else
				T[i].Left = -1;
			if (cr[0] != '-') {
				T[i].Right = cr[0] - '0';
				check[T[i].Right] = 1;
			}
			else
				T[i].Right = -1;
		}
		for (i = 0; i < N; i++)
		{
			if (!check[i])
				break;
		}
		Root = i;
	}
	*pN = N;
	return Root;
}

void printLeaves(Tree R1, int N)
{
	if (R1 == -1)
		return;
	Tree Queue[MAX];
	int i;
	Tree leaves[MaxTree];
	int count = 0;
	int cc = 0;
	int count1 = 0;
	Queue[0] = R1;
	i = 0;
	while (count1 != N)
	{
		int flag1, flag2;
		flag1 = flag2 = 0;
		int position = i / 2;
		if (Queue[position] == -1) {
			i = i + 2;
			cc++;
			continue;
		}
		//printf("i/2 = %d, element = %d ,left = %d, right = %d\n", position, T1[Queue[position]].Element, T1[Queue[position]].Left, T1[Queue[position]].Right);
		if (T1[Queue[position]].Left != -1) {
			i++;
			Queue[i-cc*2] = T1[Queue[position]].Left;
			flag1 = 1;
		}
		else
		{
			i++;
			Queue[i - cc * 2] = -1;
		}
		if (T1[Queue[position]].Right != -1) {
			i++;
			Queue[i - cc * 2] = T1[Queue[position]].Right;
			flag2 = 1;
		}
		else
		{
			i++;
			Queue[i - cc * 2] = -1;
		}
		count1++;
		
		if (!flag1 && !flag2) {
			leaves[count++] =  T1[Queue[position]].Element;
		}
	}
	
	
	for (i = 0; i < count; i++)
	{
		if (i == 0)
			printf("%d", leaves[i]);
		else
			printf(" %d", leaves[i]);
	}
}

