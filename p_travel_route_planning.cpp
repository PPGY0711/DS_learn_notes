#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 500
#define INF 1e5
#define ERROR -1e5

typedef int City;
typedef struct Graph *MGraph;
struct Graph
{
	int Nv;
	int Ne;
	City matrix[MAXN][MAXN];
}*Distance,*Cost;

/*
typedef struct Route *R;
struct Route
{
	int totalLen;
	int totalCost;
	int cities[MAXN];
};
*/

void BuildGraphs(int Vnum, int Enum)
{
	int i, j;
	Distance = (MGraph)malloc(sizeof(struct Graph));
	Cost = (MGraph)malloc(sizeof(struct Graph));
	Distance->Nv = Cost->Nv = Vnum;
	Distance->Ne = Cost->Ne = Enum;
	Cost->Nv = Cost->Nv = Vnum;
	Cost->Ne = Cost->Ne = Enum;

	for (i = 0; i < Vnum; i++)
	{
		for (j = 0; j < Vnum; j++)
		{
			Distance->matrix[i][j] = INF;
			Cost->matrix[i][j] = INF;
		}
	}
	int C1,C2,D,Toll;
	for (i = 0; i < Enum; i++)
	{
		scanf("%d %d %d %d", &C1, &C2, &D, &Toll);
		Distance->matrix[C1][C2] = Distance->matrix[C2][C1] = D;
		Cost->matrix[C1][C2] = Cost->matrix[C2][C1] = Toll;
	}
}

int FindMinDist(int dist[], int collected[])
{
	int minV, V;
	int MinDist = INF;
	for (V = 0; V < Distance->Nv; V++)
	{
		if (collected[V] == 0 && dist[V] < MinDist)
		{
			MinDist = dist[V];
			minV = V;
		}
	}
	if (MinDist < INF)
		return minV;
	else
		return ERROR;
}

void Dijkstra(int start, int fee[], int dist[],int path[],int collected[])
{
	int V, W;
	collected[start] = 1;
	while (1)
	{
		V = FindMinDist(dist, collected);
		if (V == ERROR)
			break;
		collected[V] = 1;
		for (W = 0; W < Distance->Nv; W++)
		{
			if (collected[W] == 0 && Distance->matrix[V][W] < INF)
			{
				if (dist[V] + Distance->matrix[V][W] < dist[W])
				{
					fee[W] = fee[V] + Cost->matrix[V][W];
					dist[W] = dist[V] + Distance->matrix[V][W];
					path[W] = V;
				}
				else if (dist[V] + Distance->matrix[V][W] == dist[W])
				{
					if (fee[V] + Cost->matrix[V][W] < fee[W])
					{
						fee[W] = fee[V] + Cost->matrix[V][W];
						dist[W] = dist[V] + Distance->matrix[V][W];
						path[W] = V;
					}
				}
			}
		}
	}
}

void PrintRoute(int start, int dest, int fee[], int dist[], int path[])
{
	printf("%d %d\n", dist[dest], fee[dest]);
}

void GenerateRoute(int start, int dest, int Enum, int Vnum)
{
	int *fee,*dist,*path,*collected;
	fee = (int*)malloc(sizeof(int)*Vnum);
	//memset(fee, INF, sizeof(int)*Vnum);
	dist = (int*)malloc(sizeof(int)*Vnum);
	//memset(dist, INF, sizeof(int)*Vnum);
	path = (int*)malloc(sizeof(int)*Vnum);
	//memset(path, -1, sizeof(int)*Vnum);
	collected = (int*)malloc(sizeof(int)*Vnum);
	memset(collected, 0, sizeof(int)*Vnum);

	int i, j;
	for (i = 0; i < Vnum; i++)
	{
		if (Distance->matrix[start][i] != INF)
		{
			fee[i] = Cost->matrix[start][i];
			dist[i] = Distance->matrix[start][i];
			path[i] = start;
		}
		else{
			fee[i] = INF;
			dist[i] = INF;
			path[i] = -1;
		}
	}

	Dijkstra(start, fee, dist, path, collected);
	PrintRoute(start, dest, fee, dist, path);
}

int main()
{
	int Nv, Ne;
	int start, dest;
	scanf("%d %d %d %d", &Nv, &Ne, &start, &dest);
	BuildGraphs(Nv,Ne);
	GenerateRoute(start,dest,Ne,Nv);
	system("pause");
	return 0;
}