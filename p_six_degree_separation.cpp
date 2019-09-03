#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 1000
#define INF 1e5
//用邻接矩阵建图
//思路是用深度优先搜索，在计算层数方面添加控制变量。

typedef int Vertex;
typedef struct Graph *MGraph;
struct Graph
{
	int Nv;
	int Ne;
	Vertex People[MAXSIZE][MAXSIZE];
};

MGraph CreateGraph(int VertexNum)
{
	MGraph G;
	G = (MGraph)malloc(sizeof(struct Graph));
	G->Nv = VertexNum;
	G->Ne = 0;

	int V, W;
	for (V = 0; V < VertexNum; V++)
	{
		for (W = 0; W < VertexNum; W++)
		{
			G->People[V][W] = INF;
		}
	}
	return G;
}

void FillEdge(MGraph G, int EdgeNum)
{
	int i;
	Vertex V1, V2;

	for (i = 0; i < EdgeNum; i++)
	{
		scanf("%d %d", &V1, &V2);
		G->People[V1-1][V2-1] = 1;
		G->People[V2-1][V1-1] = 1;
	}
}

int BFS(MGraph G, Vertex X, int visited[])
{
	visited[X] = 1;
	int count = 1;
	int level = 0, last = X;
	int tail;
	int Queue[MAXSIZE];
	memset(Queue, 0, sizeof(int)*MAXSIZE);
	int front, rear;
	front = -1;
	rear = 0;

	Queue[rear++] = X;
	while (front != rear-1)
	{
		X = Queue[++front];
		int i, j;
		for (i = 0; i < G->Nv; i++)
		{
			if ((visited[i] == 0) && G->People[X][i] == 1)
			{
				visited[i] = 1;
				Queue[rear++] = i;
				tail = i;
				count++;
			}
		}
		if (X == last)
		{
			level++;
			last = tail;
		}
		if (level == 6)
			break;
	}
	return count;
}

void SDS(MGraph G)
{
	Vertex S = 0;
	int i,j, count;
	int *visited;
	visited = (int*)malloc(sizeof(int)*(G->Nv));
	for (i = 0; i < G->Nv; i++)
		visited[i] = 0;
	for (i = 0; i < G->Nv; i++)
	{
		count = BFS(G,i,visited);
		printf("%d: %.2f%%\n", i+1, 100*((double)count / (G->Nv)));
		for (j = 0; j < G->Nv; j++)
			visited[j] = 0;
	}
}

int main()
{
	int Nv, Ne;
	scanf("%d %d", &Nv, &Ne);
	MGraph G = CreateGraph(Nv);
	FillEdge(G, Ne);
	SDS(G);

	system("pause");
	return 0;
}