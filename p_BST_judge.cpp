//�ж��Ƿ���ͬһ��������
#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
	int v;
	Tree Left;
	Tree Right;
	int flag; //�жϽڵ��Ƿ񱻷��ʹ�
};

Tree MakeTree(int N);
Tree NewNode(int v);
Tree Insert(Tree T, int v);
int Judge(Tree T, int N);
int check(Tree T, int v);
void ResetT(Tree T);
void FreeTree(Tree T);

int main()
{
	/*
	 * ��ÿ������
	 * ������N��L
	 * �����ݵ�һ�����н���T
	 * ��������T�ֱ��б�����L�������Ƿ�����T�γ�ͬһ��������������
	 */
	int N, L, i;
	Tree T;

	scanf("%d", &N);
	while (N)
	{
		scanf("%d", &L);
		T = MakeTree(N);
		for (i = 0; i < L; i++)
		{
			if (Judge(T, N))
				printf("Yes\n");
			else
				printf("No\n");
			ResetT(T); //���T�еı��flag
		}
		FreeTree(T);
		scanf("%d", &N);
	}

	return 0;
	system("PAUSE");
	return 0;
}

Tree MakeTree(int N)
{
	Tree T;
	int i, v;
	scanf("%d", &v);
	T = NewNode(v);
	for (i = 1; i < N; i++)
	{
		scanf("%d", &v);
		T = Insert(T, v);
	}
	return T;
}

Tree NewNode(int v)
{
	Tree T = (Tree)malloc(sizeof(struct TreeNode));
	T->v = v;
	T->Left = NULL;
	T->Right = NULL;
	T->flag = 0;
	return T;
}

Tree Insert(Tree T, int v)
{
	if (!T)
	{
		T = NewNode(v);
	}
	else
	{
		if (T->v > v)
			T->Left = Insert(T->Left, v);
		else
			T->Right = Insert(T->Right, v);
	}
	return T;
}

int Judge(Tree T, int N)
{
	//�ж������Ƿ�һ�£������а�˳����������3 2 4 1�е�ÿ����
	//���ÿ�������������Ľ����ǰ������ֹ�����һ�£���֮��δ���������Ľ�㣬��һ�¡�
	int i, v, flag = 0;
	scanf("%d", &v);
	if (v != T->v)
		flag = 1;
	else
		T->flag = 1;
	for (i = 1; i < N; i++)
	{
		scanf("%d", &v);
		if ((!flag) && !check(T, v))
			flag = 1;
	}
	if (!flag)
		return 1;
	else
		return 0;
}

int check(Tree T, int v)
{
	//���ҹ��̵����ж��Ƿ�һ��
	if (T->flag)
	{
		if (v < T->v)
			return check(T->Left, v);
		else if (v > T->v)
			return check(T->Right, v);
		else return 0;
	}
	else
	{
		if (v == T->v)
		{
			T->flag = 1;
			return 1;
		}
		else
			return 0;
	}
}

void ResetT(Tree T)
{
	if (!T)
		return;
	T->flag = 0;
	ResetT(T->Left);
	ResetT(T->Right);
}

void FreeTree(Tree T)
{
	if (!T)
		return;
	FreeTree(T->Left);
	FreeTree(T->Right);
	free(T);
}