#pragma warning( disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#define MAX 1000
typedef int ElementType;
typedef struct TreeNode *BSTree;
struct TreeNode
{
	ElementType data;
	BSTree left;
	BSTree right;
};

BSTree* buildCTree(int N);
BSTree reform2BST(BSTree* CTnodes, int N);
void levelorderTraversal(BSTree* CTnodes, int N);
void inorderTraversal(BSTree BT, int arr[]);
void sort(ElementType arr[], int N);

int main()
{
	int N;
	BSTree BT, *CTnodes;
	scanf("%d", &N);
	CTnodes = buildCTree(N);
	BT = reform2BST(CTnodes, N);
	levelorderTraversal(CTnodes, N);

	system("PAUSE");
	return 0;
}

BSTree* buildCTree(int N)
{
	ElementType *arr;
	arr = (ElementType*)malloc(sizeof(ElementType)*N);
	int i;
	for (i = 0; i < N; i++)
	{
		arr[i] = i;
	}
	BSTree *CTnodes;
	
	if (N)
	{
		CTnodes = (BSTree*)malloc(sizeof(BSTree)*N);
		for (i = 0; i < N; i++)
		{
			CTnodes[i] = (BSTree)malloc(sizeof(struct TreeNode));
			CTnodes[i]->data = arr[i];
			CTnodes[i]->left = CTnodes[i]->right = NULL;
		}
		for (i = 1; i <= N / 2; i++)
		{
			if ((2 * i-1) < N)
				CTnodes[i-1]->left = CTnodes[2 * i-1];
			if ((2 * i) < N)
				CTnodes[i-1]->right = CTnodes[2 * i];
		}
		return CTnodes;
	}
	else
		return NULL;
}

BSTree reform2BST(BSTree* CTnodes, int N)
{
	ElementType *arr;
	arr = (ElementType*)malloc(sizeof(ElementType)*N);
	int i;
	for (i = 0; i < N; i++)
	{
		scanf("%d", &arr[i]);
	}
	sort(arr, N);
	int* inorder;
	inorder = (int*)malloc(sizeof(int)*N);
	inorderTraversal(CTnodes[0], inorder);
	int j;
	for (i = 0; i < N; i++)
	{
		CTnodes[inorder[i]]->data = arr[i];
	}
	BSTree BT;
	BT = CTnodes[0];
	return BT;
}

void inorderTraversal(BSTree BT, int arr[])
{
	static int i = 0;;
	if (!BT)
		return;
	inorderTraversal(BT->left, arr);
	arr[i] = BT->data;
	i++;
	//printf("%d ", BT->data);
	inorderTraversal(BT->right, arr);
}

void levelorderTraversal(BSTree* CTnodes, int N)
{
	int i;
	for (i = 0; i < N; i++)
	{
		if (i == 0)
			printf("%d", CTnodes[i]->data);
		else
			printf(" %d", CTnodes[i]->data);
	}
}

void sort(ElementType arr[], int N)
{
	int i, j;
	for (i = 0; i < N-1; i++)
	{
		for (j = i; j < N; j++)
		{
			if (arr[i] > arr[j]) {
				ElementType tmp;
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
			}
		}
	}
}