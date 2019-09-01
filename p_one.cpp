#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void PrintN1(int N)
{
	int i;
	for (i = 1; i <= N; i++)
	{
		printf_s("%d\n", i);
	}
	return;
}

void PrintN2(int N)
{
	if (N)
	{
		PrintN2(N - 1);
		printf_s("%d\n", N);
	}
	return;
}

double f1(int n, double a[], double x)
{
	int i;
	double p = a[0];
	for (i = 1; i <= n; i++)
		p += (a[i] * pow(x, i));
	return p;
}

//�ؾ����㷨
double f2(int n, double a[], double x)
{
	int i;
	double p = a[n];
	for (i = n; i > 0; i--)
	{
		p = a[i - 1] + x*p;
	}
	return p;
}

/*
int main(void)
{
	int N;
	scanf_s("%d", &N);
	PrintN1(N);
	printf_s("-----------------------------------\n");
	PrintN2(N); //10000���ܲ�����
	system("PAUSE");
	return 0;
}
*/

//��clock������ģ��
/*
clock_t start, stop;
// clock_t ��clock()�������صı�������
double duration;
// ��¼���⺯������ʱ�䣬����Ϊ��λ
int main() {
// ���ڲ��Է�Χ�ڵ�׼������д��clock()����֮ǰ
	start = clock();
	MyFunction();
	stop = clock();
	duration = ((double)(start - stop))/CLK_TCK;

	//�������ڲ��Է�Χ�ڵĴ���д�ں��棬�������duration��ֵ
	return 0;
}
*/

/*
clock_t start, stop;
double duration;
#define MAXN 10 //����ʽ���������������ʽ����+1
#define MAXK 100000 //���⺯������ظ����ô���
int main() {
	int i;
	double a[MAXN];
	for (i = 0; i < MAXN; i++)
	{
		a[i] = double(i);
	}
	// ����f(x)=��i��x^i
	start = clock();
	for(i=0;i<MAXK;i++)
		f1(MAXN-1,a,1);
	stop = clock();
	duration = ((double)(start - stop))/CLK_TCK/MAXK;
	printf_s("ticks1 = %f\n", (double)(stop - start));
	printf_s("duration1 = %6.2e\n", duration);

	start = clock();
	for (i = 0; i<MAXK; i++)
		f2(MAXN - 1, a, 1);
	stop = clock();
	duration = ((double)(start - stop)) / CLK_TCK/MAXK;
	printf_s("ticks2 = %f\n", (double)(stop - start));
	printf_s("duration2 = %6.2e\n", duration);
	
	system("PAUSE");
	return 0;
}
*/

