#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXN 10000


void Union(int f1, int f2, int *files);
int check(int f1, int f2, int *files);
int find(int f, int *files);

int main()
{
	int N, i;
	scanf("%d", &N);
	int *files;
	files = (int*)malloc(sizeof(int)*(N+1));
	for (i = 1; i <= N; i++)
	{
		files[i]= -1;
	}

	char cmd[2];
	scanf("%s", cmd);
	while (cmd[0] != 'S')
	{
		int f1, f2;
		scanf("%d %d", &f1, &f2);
		if (cmd[0] == 'C')
		{
			if (check(f1, f2, files))
				printf("yes\n");
			else
				printf("no\n");
		}
		else
		{
			Union(f1, f2, files);
		}
		scanf("%s", cmd);
	}
	int count = 0;
	for (i = 1; i <= N; i++)
	{
		if (files[i] < 0)
			count++;
	}
	if (count == 1)
		printf("The network is connected.\n");
	else
		printf("There are %d components.\n", count);

	system("pause");
	return 0;
}

void Union(int f1, int f2, int *files)
{
	int root1,root2;
	root1 = find(f1, files);
	root2 = find(f2, files);
	if (root1 != root2)
	{
		if (files[root1] < files[root2])
		{
			files[root1] += files[root2];
			files[root2] = root1;
		}
		else
		{
			files[root2] += files[root1];
			files[root1] = root2;
		}
	}
	else
		return;
}

int check(int f1, int f2, int *files)
{
	return (find(f1, files) == find(f2, files));
}

int find(int f, int *files)
{
	int root = files[f];
	while (root > 0)
	{
		f = root;
		root = files[f];	
	}
	return f;
}
