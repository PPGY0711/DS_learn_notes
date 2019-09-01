//判断是否是同一棵搜索树
#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode *Tree;
struct TreeNode
{
	int v;
	Tree Left;
	Tree Right;
	int flag; //判断节点是否被访问过
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
	 * 对每组数据
	 * ·读入N和L
	 * ·根据第一行序列建树T
	 * ·根据树T分别判别后面的L个序列是否能与T形成同一搜索树并输出结果
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
			ResetT(T); //清除T中的标记flag
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
	//判断序列是否一致：在树中按顺序搜索序列3 2 4 1中的每个数
	//如果每次搜索所经过的结点在前面均出现过，则一致；反之有未被遇到过的结点，则不一致。
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
	//查找过程当中判断是否一致
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