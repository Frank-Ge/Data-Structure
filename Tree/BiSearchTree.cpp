#include "BiSearchTree.h"
#include <stdlib.h>
#include "math.h" 
#include <stack>
using namespace std;

SearchTree MakeEmpty(SearchTree T)
{
	if (T)
	{
		MakeEmpty(T->lchild);
		MakeEmpty(T->rchild);
		free(T);
	}
	return NULL;
}

// 查找二叉查找树T中x的位置，否则返回NULL
Position Find(ElemType x, SearchTree T)
{
	if (!T)
		return NULL;

	if (x < T->data)
		return Find(x, T->lchild);
	else if (x > T->data)
		return Find(x, T->rchild);
	else
		return T;
}

// 在二叉查找树中插入结点x。
// 如果存在，则不操作
SearchTree Insert(ElemType x, SearchTree T)
{
	if (!T)
	{
		T = (SearchTree)malloc(sizeof(TreeNode));
		if (!T)
			exit(OVERFLOW);
		T->data = x;
		T->lchild = NULL;
		T->rchild = NULL;
	}

	if (x < T->data)
		T->lchild = Insert(x, T->lchild);
	else if (x > T->data)
		T->rchild = Insert(x, T->rchild);

	return T;
}

// 找到二叉查找树中最小的结点，返回结点的指针
Position FindMin(SearchTree T)
{
	if (!T)
		return NULL;

	while (T->lchild)
		T = T->lchild;
	return T;
}

// 找到二叉查找树最大的结点，返回结点指针
Position FindMax(SearchTree T)
{
	if (!T)
		return NULL;

	while (T->rchild)
		T = T->rchild;
	return T;
}

// 初始条件：查找二叉树存在
// 操作结果：删除data阈值为x的结点
SearchTree Delete(ElemType x, SearchTree T)
{
	if (!T) // T为空，返回NULL
		return NULL;

	if (x < T->data) 
		T->lchild = Delete(x, T->lchild);
	else if (x > T->data)
		T->rchild = Delete(x, T->rchild);
	// 如果待删除的结点左、右孩子均存在，则将此结点的右孩子中最小值替换为此结点的值，
	// 同时递归删除此结点的右孩子中的最小值
	else if (T->lchild && T->rchild) 
	{
		Position temp;
		temp = FindMin(T->rchild);
		T->data = temp->data;
		T->rchild = Delete(T->data, T->rchild);
	}
	// 如果待删除结点为叶子结点，则直接删除。若只有一个孩子结点，则将孩子结点的值替换到此结点
	else
	{
		Position temp;
		temp = T;
		if (T->lchild)
			T = T->lchild;
		else if (T->rchild)
			T = T->rchild;
		else
			T = NULL;
		free(temp);
	}

	return T;
}

// 前序遍历，非递归形式
void PreOrderTraverse(SearchTree T)
{
	if (!T)
		return;

	TreeNode *p;
	stack<TreeNode *> S;
	
	p = T;
	while (p || !S.empty())
	{
		while (p)
		{
			visit(p);
			S.push(p);
			p = p->lchild;
		}
		if (!S.empty())
		{
			p = S.top();
			S.pop();
			p = p->rchild;
		}
	}
}

ElemType Retrieve(Position P)
{
	return P->data;
}

void visit(Position P)
{
	printf("%d ", P->data);
}
