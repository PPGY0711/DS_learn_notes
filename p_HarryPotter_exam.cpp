#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 101
#define INF 1e5
#define ERROR -1e5
#define TAG 1e8
typedef int Vertex;
typedef struct Graph *MGraph;
struct Graph
{
	int Nv;
	int Ne;
	Vertex Edges[MAXSIZE][MAXSIZE];
};

MGraph CreateGraph(int Nv)
{
	int i, j;
	MGraph G = (MGraph)malloc(sizeof(struct Graph));
	G->Nv = Nv;
	G->Ne = 0;
	for (i = 1; i <= Nv; i++)
		for (j = 1; j <= Nv; j++)
		{
			if (i != j)
				G->Edges[i][j] = INF;
			else
				G->Edges[i][j] = 0;
		}

	return G;
}

void FillWeight(MGraph G, int Ne)
{
	G->Ne = Ne;
	Vertex V1, V2;
	int i, spell;
	for (i = 0; i < Ne; i++)
	{
		scanf("%d %d %d", &V1, &V2, &spell);
		G->Edges[V1][V2] = spell;
		G->Edges[V2][V1] = spell;
	}
}

Vertex FindMinDist(MGraph G, int dist[], int collected[])
{
	Vertex MinV, V;
	int MinDist = INF;

	for (V = 1; V <= G->Nv; V++)
	{
		if (collected[V] == 0 && dist[V] < MinDist)
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

int FindMaxPath(MGraph G,int dist[])
{
	int maxlen, i;
	maxlen = 0;
	for (i = 1; i <= G->Nv; i++)
	{
		if (maxlen < dist[i])
			maxlen = dist[i];
	}
	return maxlen;
}

int Dijkstra(MGraph G, int dist[], int path[], Vertex Start)
{
	int *collected = (int*)malloc(sizeof(int)*((G->Nv)+1));
	memset(collected, 0, sizeof(int)*(G->Nv+1));

	Vertex V, W;

	collected[Start] = 1;

	while (1)
	{
		V = FindMinDist(G, dist, collected);
		if (V == ERROR)
			break;
		collected[V] = 1;
		for (W = 1; W <= G->Nv; W++)
		{
			if (collected[W] == 0 && G->Edges[V][W] < INF)
			{
				if (G->Edges[V][W] < 0)
					return ERROR;
				if (dist[V] + G->Edges[V][W] < dist[W])
				{
					dist[W] = dist[V] + G->Edges[V][W];
					path[W] = V;
				}
			}
		}
	}
	return FindMaxPath(G, dist);
}

int FindMinSpell(MGraph G, Vertex Start)
{
	
	int *dist, *path, shortest;
	dist = (int*)malloc(sizeof(int)*(G->Nv+1));
	path = (int*)malloc(sizeof(int)*(G->Nv+1));
	memset(path, -1, sizeof(int)*(G->Nv+1));
	int i;
	for (i = 1; i <= G->Nv; i++)
	{
			dist[i] = G->Edges[Start][i];
	}
	
	shortest = Dijkstra(G, dist, path, Start);
	//printf("Vertex: %d, shortest PAth: %d\n", Start, shortest);
	return shortest;
}

void FindMinCostAnimal(MGraph G, Vertex *Min, int *SS)
{
	int i;

	Vertex Start = 1;
	(*Min) = Start;
	(*SS) = TAG;
	for (i = Start; i <= G->Nv; i++)
	{
		int tmp = FindMinSpell(G, i);
		if ( tmp > 0 &&  tmp < (*SS))
		{
			(*Min) = i;
			(*SS) = tmp;
		}
	}
}

int main()
{
	int VertexNum, EdgeNum;
	MGraph G;
	scanf("%d %d", &VertexNum, &EdgeNum);
	G = CreateGraph(VertexNum);
	FillWeight(G, EdgeNum);
	int len;
	Vertex v;
	FindMinCostAnimal(G, &v, &len);
	if (len == INF)
		printf("0\n");
	else
		printf("%d %d\n", v, len);

	system("pause");
	return 0;
}