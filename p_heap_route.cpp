#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAXN 1001 //堆从数组下标为1的位置开始存
#define MINH -10001

int H[MAXN], size;

//建立空堆
void Create()
{
	size = 0;
	H[0] = MINH; //设置岗哨
}

void Insert(int X)
{
	//堆已满
	if (size == MAXN-1)
		return;
	int i;
	for (i = ++size; H[i / 2] > X; i /= 2)
		H[i] = H[i / 2];
	H[i] = X;
}

int main()
{
	int N, M, i, x, index;
	scanf("%d %d", &N, &M);
	Create();
	for (i = 0; i < N; i++)
	{
		scanf("%d", &x);
		Insert(x);
	}
	for (i = 0; i < M; i++)
	{
		scanf("%d", &index);
		printf("%d", H[index]);
		while (index > 1)
		{
			index /= 2;
			printf(" %d", H[index]);
		}
		printf("\n");
	}
	system("pause");
	return 0;
}