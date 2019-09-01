#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100000

typedef struct result *Res;
struct result {
	int MaxSum;
	int first;
	int last;
};

Res CalMaxSum(int L[], int N);
/*
int main()
{
	Res res;
	int i, N;
	int L[MAXSIZE];
	scanf_s("%d", &N);
	for (i = 1; i <= N; i++)
	{
		scanf_s("%d", &L[i - 1]);
	}
	res = CalMaxSum(L, N);
	printf("%d %d %d", res->MaxSum, res->first, res->last);
	system("pause");
	return 0;
}
*/
Res CalMaxSum(int L[], int N)
{
	Res res;
	res = (Res)malloc(sizeof(struct result));
	int ThisSum, MaxSum;
	int firstindex, lastindex;
	ThisSum = MaxSum = 0;
	firstindex = 0;
	lastindex = N - 1;
	int i;
	int count = 0;
	int count1 = 0;
	int count0 = 0;

	for (i = 0; i < N; i++)
	{
		ThisSum += L[i];
		count++;
		if (ThisSum > MaxSum) {
			MaxSum = ThisSum;
			firstindex = i - count + 1;
			lastindex = i;
		}
		else if (ThisSum < 0) {
			ThisSum = 0;
			count = 0;
		}
		//处理负数和0
		if (L[i] > 0) {
			count1++;
		}
		if (L[i] == 0) {
			count0++;
		}
	}

	res->MaxSum = MaxSum;
	res->first = L[firstindex];
	res->last = L[lastindex];

	if (count1 == 0 && count0 != 0) {
		res->first = 0;
		res->last = 0;
	}

	return res;
}