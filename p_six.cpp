#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 1000
int verify(int arr[], int M, int N);

int main()
{
	int N, M, K;
	scanf("%d", &M);
	scanf("%d", &N);
	scanf("%d", &K);
	int arr[MAXSIZE];
	int i,j;
	for (i = 0; i < K; i++)
	{
		for (j = 0; j < N; j++)
		{
			scanf("%d", &arr[j]);
		}
		if (verify(arr, M, N))
			printf("YES\n");
		else
			printf("NO\n");
	}
	system("pause");
	return 0;
}

int verify(int arr[], int M, int N)
{
	//1.�������ԣ����ܳ�������M�����ǴӴ�С���У�
	//2.�����һ���������棬����˳�����е�С�����������
	int versec = 0;
	int maxver = 0;
	int i, j;
	for (i = 0; i < N-1; i++)
	{
		if (arr[i] > arr[i+1]) {
			versec++;
		}
		else
			versec = 0;
		if (versec > maxver)
			maxver = versec;
		
		//printf("maxver = %d\n", maxver);
	}
	if (maxver >= M)
		return 0;
	else
	{
		for (i = 0; i < N - 2; i++)
		{
			for (j = i+1; j < N - 1; j++)
			{
				if (arr[j] < arr[i] && arr[j + 1] < arr[i] && arr[j] < arr[j + 1])
					return 0;
			}
		}
	}
	return 1;
}