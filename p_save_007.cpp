#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define DIAMITER 15 //Ö±¾¶
#define BANK 50
#define MAXN 100
typedef struct Vertex *Coor;
struct Vertex
{
	int x;
	int y;
};

Coor Graph[MAXN+1];

void BuildGraph(int N)
{
	Graph[0] = (Coor)malloc(sizeof(struct Vertex));
	Graph[0]->x = 0;
	Graph[0]->y = 0;
	int i,x,y;
	for (i = 1; i <= N; i++)
	{
		scanf("%d %d", &x, &y);
		Graph[i] = (Coor)malloc(sizeof(struct Vertex));
		Graph[i]->x = x;
		Graph[i]->y = y;
	}
}

double Distance(Coor c1, Coor c2)
{
	return sqrt((c1->x - c2->x)*(c1->x - c2->x) + (c1->y - c2->y)*(c1->y - c2->y));
}

int isSafe(Coor pos,int D)
{
	if (((BANK - abs(pos->x) <= D)) || ((BANK - abs(pos->y) <= D)))
		return 1;
	else
		return 0;
}

int FirstJump(Coor c,int D)
{
	if (Distance(c, Graph[0]) - (DIAMITER / 2.0) <= D)
		return 1;
	else
		return 0;
}

int Jump(Coor c1, Coor c2, int D)
{
	if (Distance(c1, c2) <= D)
		return 1;
	else
		return 0;
}

int DFS(int id, int D, int N, int *jumped)
{
	int answer = 0;
	if (isSafe(Graph[id],D))
		return 1;
	int i;
	jumped[id] = 1;
	//printf("x: %d, y: %d \n", Graph[id]->x, Graph[id]->y);
	for (i = 1; i <= N; i++)
	{
		if (jumped[i] == 0 && Jump(Graph[i], Graph[id], D)) {
			//printf("x: %d, y: %d \n", Graph[i]->x, Graph[i]->y);
			answer = DFS(i, D, N, jumped);
			if (answer)
				return 1;
		}
	}
	return 0;
}

int Save_007(int N,int D)
{
	int *firstStep;
	firstStep = (int*)malloc(sizeof(int)*N);
	int i,j = 0;
	for (i = 1; i <= N; i++)
	{
		if (FirstJump(Graph[i],D))
			firstStep[j++] = i;
	}
	int *jumped;
	jumped = (int*)malloc(sizeof(int)*(MAXN+1));
	for (i = 1; i <= MAXN; i++)
		jumped[i] = 0;
	if (!j)
		return 0;
	for (i = 0; i < j; i++)
	{
		jumped[firstStep[i]] = 1;
		if (DFS(firstStep[i], D, N, jumped))
			return 1;
		//printf("\n");
	}
	return 0;
}

int main()
{
	int N, D;
	scanf("%d %d", &N, &D);
	BuildGraph(N);
	if (Save_007(N,D))
		printf("Yes\n");
	else
		printf("No\n");

	system("pause");
	return 0;
}
