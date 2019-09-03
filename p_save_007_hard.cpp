#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#define DIAMITER 15 
#define BANK 50
#define MAXN 100
#define INF 1e5
#define ERROR -1e5
typedef struct Vertex *Coor;
struct Vertex
{
	int x;
	int y;
};

typedef struct Stack *Route;
struct Stack
{
	int Route[MAXN];
	//int size;
	int top;
};

Coor Graph[MAXN + 1];
Route Escape;

void BuildGraph(int N)
{
	Graph[0] = (Coor)malloc(sizeof(struct Vertex));
	Graph[0]->x = 0;
	Graph[0]->y = 0;
	int i, x, y;
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

int isSafe(Coor pos, int D)
{
	if (((BANK - abs(pos->x) <= D)) || ((BANK - abs(pos->y) <= D)))
		return 1;
	else
		return 0;
}

int FirstJump(Coor c, int D)
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

int FindMinDist(int dist[], int jumped[], int N)
{
	int MinV, V;
	int MinDist = INF;
	for (V = 1; V <= N; V++)
	{
		if (jumped[V] == 0 && dist[V] < MinDist)
		{
			MinDist = dist[V];
			MinV = V;
		}
	}
	if (MinDist < INF)
		return MinV;
	else
		return ERROR;
}

void WriteToRoute(int dist[], int path[], int N,int D, int *safe)
{
	if (*safe == INF)
		return;
	int i;
	int last = 0;
	dist[last] = INF;
	int flag = 0;
	Route tmp = (Route)malloc(sizeof(struct Stack));
	tmp->top = -1;
	memset(tmp->Route, -1, sizeof(int)*(MAXN));
	while (*safe != -1)
	{
		tmp->Route[++(tmp->top)] = *safe;
		*safe = path[*safe];
	}
	if ((Escape->top == -1) || tmp->top < Escape->top)
		Escape = tmp;
}

void Dijkstra(int start, int D, int N, int jumped[], int dist[], int path[], int *safe)
{
	jumped[start] = 1;
	*safe = INF;
	int V, W;
	//int last = start;
	while (1)
	{
		V = FindMinDist(dist, jumped, N);
		int flag = 0;
		if (V == ERROR)
			break;
		jumped[V] = 1;
		for (W = 1; W <= N; W++)
		{
			if ((jumped[W] == 0) && (Jump(Graph[V], Graph[W],D)) && flag == 0)
			{
				if (dist[V] + 1 < dist[W])
				{
					dist[W] = dist[V] + 1;
					path[W] = V;
					if (isSafe(Graph[W], D)) {
						//printf("Here: start with point(%d,%d), traverse point(%d,%d)\n", Graph[V]->x, Graph[V]->y,Graph[W]->x,Graph[W]->y);
						*safe = W;
						flag = 1;
					}
				}
			}
		}
		if (flag == 1)
			break;
	}
}

void FindRoute(int start, int D, int N, int *jumped)
{
	int *dist;
	int *path;
	dist = (int*)malloc(sizeof(int)*(N + 1));
	
	path = (int*)malloc(sizeof(int)*(N + 1));
	memset(path, -1, sizeof(int)*(N + 1));

	int i;

	for (i = 1; i <= N; i++)
	{
		if (Jump(Graph[start], Graph[i], D))
		{
			dist[i] = 2;
			path[i] = start;
		}
		else
			dist[i] = INF;
	}
	dist[start] = 1;
	path[start] = -1;
	int safeNode;
	Dijkstra(start, D, N, jumped, dist, path, &safeNode);
	WriteToRoute(dist, path, N, D, &safeNode);
}

void PrintRoute(int flag, int safe)
{
	if (!flag) {
		if (Escape->top == -1)
			printf("0\n");
		else
			printf("%d\n", Escape->top + 2);
		int i;
		while (Escape->top != -1)
		{
			printf("%d %d\n", Graph[Escape->Route[Escape->top]]->x, Graph[Escape->Route[Escape->top]]->y);
			Escape->top--;
		}
	}
	else
	{
		printf("1\n");
		printf("%d %d\n", Graph[safe]->x, Graph[safe]->y);
	}
}


void Save_007(int N, int D)
{
	int *firstStep;
	firstStep = (int*)malloc(sizeof(int)*N);
	int i, j = 0;
	for (i = 1; i <= N; i++)
	{
		if (FirstJump(Graph[i], D))
			firstStep[j++] = i;
	}
	int *jumped;
	jumped = (int*)malloc(sizeof(int)*(N + 1));
	for (i = 1; i <= N; i++)
		jumped[i] = 0;
	if (!j)
		return;
	for (i = 0; i < j; i++)
	{
		if (isSafe(Graph[firstStep[i]], D))
		{
			PrintRoute(1, firstStep[i]);
			return;
		}
		jumped[firstStep[i]] = 1;
		FindRoute(firstStep[i], D, N, jumped);
		memset(jumped, 0, sizeof(int) + (N + 1));
	}
}


int main()
{
	int N, D;
	scanf("%d %d", &N, &D);
	BuildGraph(N);
	//Escape->size = 0;
	Escape = (Route)malloc(sizeof(struct Stack));
	Escape->top = -1;
	Save_007(N, D);
	PrintRoute(0,0);

	system("pause");
	return 0;
}
