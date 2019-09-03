#pragma warning( disable : 4996)
#include<stdio.h>
#include<stdlib.h>

#define MAXN 15
int visited[MAXN] = { 0 };

//�����ڽӾ��� //Create Graph
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
	printf("%d ", v);//�������� 
	for (int i = 0; i<NV; i++)
	{
		if (G[v][i] && !visited[i])//�����ͨ�������û�з��ʹ� 
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
//��ʼ��visited
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
	//����
	const int MAXSIZE = 100;
	int quene[MAXSIZE];
	int first = -1, rear = -1;
	quene[++rear] = v;//��� 
	visited[v] = 1;

	while (first < rear)//���в�Ϊ��
	{
		int de = quene[++first];//����
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

	//��ͼ
	BuildGraph();
	//DFS������ͨ��
	ListComponentsDFS();
	isvisited();
	//BFS������ͨ�� 
	ListComponentsBFS();
	system("pause");
	return 0;
}
