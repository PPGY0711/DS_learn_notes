#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXSIZE 10
#define ERROR -1
typedef int Vertex;
typedef struct AdjVNode *AdjV;
struct AdjVNode
{
	Vertex V;
	AdjV NextV;
};

typedef struct LGraphNode *LGraph;
struct LGraphNode
{
	Vertex V;
	AdjV FirstEdge;
}*Graph[MAXSIZE];


typedef struct QueueNode *Queue;
struct QueueNode
{
	Vertex Vs[MAXSIZE];
	int front;
	int rear;
	int capacity;
};

Queue CreateQueue(int size)
{
	Queue Q;
	Q = (Queue)malloc(sizeof(struct QueueNode));
	memset(Q->Vs, 0, sizeof(int)*MAXSIZE);
	Q->capacity = size;
	Q->front = -1;
	Q->rear = 0;
	return Q;
}

void AddQ(Queue Q, Vertex V)
{
	if (Q->rear == MAXSIZE)
		return;
	Q->Vs[(Q->rear)++] = V;
}

Vertex DeleteQ(Queue Q)
{
	if (Q->rear == Q->front)
		return ERROR;
	return Q->Vs[++(Q->front)];
}

void Visit(Vertex V)
{
	printf("%d ", V);
}

void DFS(LGraph *Graph, Vertex V, int* visited)
{
	AdjV W;
	Visit(V);
	visited[V] = 1;
	for (W = Graph[V]->FirstEdge; W; W = W->NextV)
	{
		if (!visited[W->V])
			DFS(Graph, W->V, visited);
	}
}

void BFS(LGraph *Graph, Vertex S, int* visited)
{
	Queue Q;
	AdjV W;
	Vertex V;
	Q = CreateQueue(MAXSIZE);
	Visit(S);
	visited[S] = 1;
	AddQ(Q, S);
	while (Q->rear != Q->front)
	{
		V = DeleteQ(Q);
		for (W = Graph[V]->FirstEdge; W != NULL; W = W->NextV)
		{
			if (!visited[W->V])
			{
				Visit(W->V);
				visited[W->V] = 1;
				AddQ(Q, W->V);
			}
		}
	}

}

void ListComponents(LGraph *Graph, int *visited, int Nv)
{
	int i;
	//DFS
	for (i = 0; i < Nv; i++)
	{
		if (!visited[i])
		{
			printf("{ ");
			DFS(Graph, i, visited);
			printf("}\n");
		}
	}

	//refresh visited
	for (i = 0; i < Nv; i++)
	{
		visited[i] = 0;
	}

	//BFS
	for (i = 0; i < Nv; i++)
	{
		if (!visited[i])
		{
			printf("{ ");
			BFS(Graph, i, visited);
			printf("}\n");
		}
	}
}

void sortEdges(Vertex V)
{
	int len = 0;
	AdjV tmp = Graph[V]->FirstEdge;
	while (tmp)
	{
		len++;
		tmp = tmp->NextV;
	}
	if (len == 0 || len == 1)
		return;
	AdjV start, pos, ppos;
	start = Graph[V]->FirstEdge;
	while (start)
	{
		pos = start;
		ppos = pos->NextV;
		while (pos && ppos)
		{
			if (pos->V > ppos->V)
			{
				Vertex v = pos->V;
				pos->V = ppos->V;
				ppos->V = v;
			}
			pos = ppos;
			ppos = pos->NextV;
		}
		start = start->NextV;
	}
}

int main()
{
	int Nv, Ne, i;
	scanf("%d", &Nv);
	scanf("%d", &Ne);
	int visited[MAXSIZE];
	memset(visited, 0, sizeof(int)*MAXSIZE);

	for (i = 0; i < Nv; i++)
	{
		Graph[i] = (LGraph)malloc(sizeof(struct LGraphNode));
		Graph[i]->V = i;
		Graph[i]->FirstEdge = NULL;
	}

	for (i = 0; i < Ne; i++)
	{
		Vertex V1, V2;
		scanf("%d %d", &V1, &V2);
		AdjV node1 = (AdjV)malloc(sizeof(struct AdjVNode));
		node1->V = V2;
		node1->NextV = NULL;
		if (Graph[V1]->FirstEdge == NULL)
		{
			Graph[V1]->FirstEdge = node1;
		}
		else
		{
			node1->NextV = Graph[V1]->FirstEdge;
			Graph[V1]->FirstEdge = node1;
		}

		AdjV node2 = (AdjV)malloc(sizeof(struct AdjVNode));
		node2->V = V1;
		node2->NextV = NULL;
		if (Graph[V2]->FirstEdge == NULL)
		{
			Graph[V2]->FirstEdge = node2;
		}
		else
		{
			node2->NextV = Graph[V2]->FirstEdge;
			Graph[V2]->FirstEdge = node2;
		}
	}
	
	for (i = 0; i < Nv; i++)
	{
		sortEdges(i);
	}

	ListComponents(Graph, visited, Nv);

	system("pause");
	return 0;
}