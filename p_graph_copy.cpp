#pragma warning( disable : 4996)
#include<stdio.h>
#include<stdlib.h>

#define MAXN 15
int visited[MAXN] = { 0 };

//建立邻接矩阵 //Create Graph
int G[MAXN][MAXN] = { 0 }, NV, NE;

void BuildGraph()
{
	//freopen("test1.txt","r",stdin); 
	int i, j, v1, v2;

	scanf("%d%d", &NV, &NE);

	for (i = 0; i<NE; i++)
	{
		scanf("%d%d", &v1, &v2);
		//InsertEdge
		G[v1][v2] = 1;
		G[v2][v1] = 1;
	}
}
//DFS
void DFS(int v)
{
	visited[v] = 1;
	printf("%d ", v);//输出这个点 
	for (int i = 0; i<NV; i++)
	{
		if (G[v][i] && !visited[i])//如果联通这个点且没有访问过 
		{
			DFS(i);
		}
	}
}

void ListComponentsDFS()
{
	int i;
	for (i = 0; i<NV; i++)
	{
		if (!visited[i])
		{
			printf("{ ");
			DFS(i);
			printf("}\n");
		}
	}
}
//初始化visited
void isvisited()
{
	for (int i = 0; i<MAXN; i++)
	{
		visited[i] = 0;
	}
}

//BFS
void BFS(int v)
{
	//队列
	const int MAXSIZE = 100;
	int quene[MAXSIZE];
	int first = -1, rear = -1;
	quene[++rear] = v;//入队 
	visited[v] = 1;

	while (first < rear)//队列不为空
	{
		int de = quene[++first];//出队
		printf("%d ", de);
		for (int i = 0; i<NV; i++)
		{
			if (!visited[i] && G[de][i])
			{
				visited[i] = 1;
				quene[++rear] = i;
			}
		}
	}

}


void ListComponentsBFS()
{
	int i;
	for (i = 0; i<NV; i++)
	{
		if (!visited[i])
		{
			printf("{ ");
			BFS(i);
			printf("}\n");
		}
	}
}

int main()
{

	//建图
	BuildGraph();
	//DFS遍历连通集
	ListComponentsDFS();
	isvisited();
	//BFS遍历连通集 
	ListComponentsBFS();
	system("pause");
	return 0;
}
