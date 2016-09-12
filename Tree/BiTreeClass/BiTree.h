// 链表二叉树类模版的定义

#ifndef BITREE_H
#define BITREE_H

#include <iostream>
#include <iomanip>
#include "BiTNode.h"
#include <queue>
#include <stack>
using namespace std;

typedef int Status;

#define OK	1
#define ERROR	0
#define TRUE	1
#define FALSE	0

template<typename NODETYPE>
class BiTree
{
public:
	//typedef BiTNode<NODETYPE> *BiTree;
	BiTree();

	void CreateBiTree();
	void DestroyBiTree();
	Status BiTreeEmpty();
	NODETYPE Root();

	int BiTreeDepth();
	int BiTreeDepthNonRecursion();
	//int BiTreeDepthNonRecursion2();

	void PreOrderTraverse();
	void PreOrderNonRecursion();
	void InOrderTraverse();
	void InOrderNonRecursion();
	void PostOrderTraverse();
	void PostOrderNonRecursion();
	void LevelOrderTraverse();

	void PrintLast();
	void PrintByDepth();

private:
	BiTNode<NODETYPE> *rootPtr;

	// utility function
	void visit(BiTNode<NODETYPE> *p);
	void CreateBiTreeHelper(BiTNode<NODETYPE> **T);
	void DestroyBiTreeHelper(BiTNode<NODETYPE> **T);
	int BiTreeDepthHelper(BiTNode<NODETYPE> *T);

	// 用helper函数的原因是对二叉树进行遍历要传入参数
	void PreOrderTraverseHelper(BiTNode<NODETYPE> *T);
	void InOrderTraverseHelper(BiTNode<NODETYPE> *T);
	void PostOrderTraverseHelper(BiTNode<NODETYPE> *T);
};

template<typename NODETYPE>
BiTree<NODETYPE>::BiTree()
{
	rootPtr = 0;
}

template<typename NODETYPE>
Status BiTree<NODETYPE>::BiTreeEmpty()
{
	if (rootPtr)
		return FALSE;
	else
		return TRUE;
}

template<typename NODETYPE>
void BiTree<NODETYPE>::CreateBiTree()
{
	CreateBiTreeHelper(&rootPtr);
}

// 按前序输入二叉树中结点的值（一个字符）
// #表示空树，构造二叉链表表示二叉树T。
template<typename NODETYPE>
void BiTree<NODETYPE>::CreateBiTreeHelper(BiTNode<NODETYPE> **T)
{
	NODETYPE val;

	cin >> val;

	if (val == '#')
		*T = NULL;
	else
	{
		*T = new BiTNode<NODETYPE>(val);
		CreateBiTreeHelper(&(*T)->lchild);
		CreateBiTreeHelper(&(*T)->rchild);
	}
}

template<typename NODETYPE>
void BiTree<NODETYPE>::DestroyBiTree()
{
	DestroyBiTreeHelper(&rootPtr);
}

template<typename NODETYPE>
void BiTree<NODETYPE>::DestroyBiTreeHelper(BiTNode<NODETYPE> **T)
{
	if (*T)
	{
		if ((*T)->lchild)
			DestroyBiTreeHelper(&(*T)->lchild);
		if ((*T)->rchild)
			DestroyBiTreeHelper(&(*T)->rchild);
		//free(*T);
		//*T = NULL;
		delete (*T);
		*T = NULL;
	}
}

template<typename NODETYPE>
int BiTree<NODETYPE>::BiTreeDepth()
{
	return BiTreeDepthHelper(rootPtr);
}

template<typename NODETYPE>
int BiTree<NODETYPE>::BiTreeDepthHelper(BiTNode<NODETYPE> *T)
{
	int i, j;

	if (!T)
		return 0;

	if (T->lchild)
		i = BiTreeDepthHelper(T->lchild);
	else 
		i = 0;
	if (T->rchild)
		j = BiTreeDepthHelper(T->rchild);
	else
		j = 0;

	return i > j ? i+1 : j+1;
}

template<typename NODETYPE>
NODETYPE BiTree<NODETYPE>::Root()
{
	if (!rootPtr)
		return ' ';
	else
		return rootPtr->data;
}

// 借用层次遍历的思想，实现非递归形式求出二叉树深度
template<typename NODETYPE>
int BiTree<NODETYPE>::BiTreeDepthNonRecursion()
{
	if (!rootPtr)
		return 0;

	BiTNode<NODETYPE> *p; // 工作指针，每次记录从队列队首弹出的结点
	BiTNode<NODETYPE> *back; // 记录每层二叉树的最右边的结点。此结点在每次遍历一层之后的队列队尾
	int level = 0; // 层数，初始值为0
	queue<BiTNode<NODETYPE> *> Q;

	Q.push(rootPtr);
	back = Q.back();
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();

		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);

		if (p == back) // 如果p == 每层的最右边的结点，则层数+1，同时重新赋值队尾结点
		{
			level++;
			if (!Q.empty()) // 如果队列为空，则下一步的操作出错。主要用于防止最后一个结点弹出队列之后的那次操作
				back = Q.back();
		}
	}

	return level;
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PreOrderTraverse()
{
	PreOrderTraverseHelper(rootPtr);
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PreOrderTraverseHelper(BiTNode<NODETYPE> *T)
{
	if (!T)
		return;

	visit(T);
	PreOrderTraverseHelper(T->lchild);
	PreOrderTraverseHelper(T->rchild);
}

// 前序遍历非递归形式
template<typename NODETYPE>
void BiTree<NODETYPE>::PreOrderNonRecursion()
{
	if (!rootPtr)
		return;

	BiTNode<NODETYPE> *p;
	stack<BiTNode<NODETYPE> *> S; // 借助栈实现非递归的前序遍历

	p = rootPtr;
	while (p || !S.empty())
	{
		while (p) 
		{
			visit(p); // 在每次入栈之前进行访问
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

template<typename NODETYPE>
void BiTree<NODETYPE>::InOrderTraverse()
{
	InOrderTraverseHelper(rootPtr);
}

template<typename NODETYPE>
void BiTree<NODETYPE>::InOrderTraverseHelper(BiTNode<NODETYPE> *T)
{
	if (!T)
		return;

	InOrderTraverseHelper(T->lchild);
	visit(T);
	InOrderTraverseHelper(T->rchild);
}

template<typename NODETYPE>
void BiTree<NODETYPE>::InOrderNonRecursion()
{
	if (!rootPtr)
		return;

	BiTNode<NODETYPE> *p;
	stack<BiTNode<NODETYPE> *> S;

	p = rootPtr;
	while (p || !S.empty())
	{
		while (p)
		{
			S.push(p);
			p = p->lchild;
		}
		if (!S.empty())
		{
			p = S.top();
			S.pop();
			visit(p); // 在每次出栈之时进行访问
			p = p->rchild;
		}
	}
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PostOrderTraverse()
{
	PostOrderTraverseHelper(rootPtr);
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PostOrderTraverseHelper(BiTNode<NODETYPE> *T)
{
	if (!T)
		return;

	PostOrderTraverseHelper(T->lchild);
	PostOrderTraverseHelper(T->rchild);
	visit(T);
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PostOrderNonRecursion()
{
	if (!rootPtr)
		return;

	BiTNode<NODETYPE> *p;
	BiTNode<NODETYPE> *r; // 用于记录栈中弹出的结点的右子树是否访问过
	stack<BiTNode<NODETYPE> *> S;

	p = rootPtr;
	r = NULL;
	while (p || !S.empty())
	{
		while (p)
		{
			S.push(p);
			p = p->lchild;
		}
		if (!S.empty())
		{
			p = S.top();
			if (p->rchild && p->rchild != r) // 此结点的右子树尚未入栈
			{
				p = p->rchild;
				S.push(p);
				p = p->lchild;
			}
			else
			{
				S.pop();
				visit(p); // 每次出栈时访问结点
				r = p;
				p = NULL;
			}
		}
	}

}

template<typename NODETYPE>
void BiTree<NODETYPE>::LevelOrderTraverse()
{
	if (!rootPtr)
		return;

	BiTNode<NODETYPE> *p;
	BiTNode<NODETYPE> *back; // 操作中记录队列尾部的指针
	queue<BiTNode<NODETYPE> *> Q; // 使用辅助队列

	Q.push(rootPtr);
	back = Q.back();
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		visit(p);

		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);
	}
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PrintLast()
{
	if (!rootPtr)
		return;

	BiTNode<NODETYPE> *p;
	BiTNode<NODETYPE> *back; // 操作中记录队列尾部的指针
	queue<BiTNode<NODETYPE> *> Q; // 使用辅助队列

	Q.push(rootPtr);
	back = Q.back();
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();

		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);

		if (p == back)
		{
			visit(p);
			if (!Q.empty())
				back = Q.back(); // 更新back指针的位置
		}
	}
}

template<typename NODETYPE>
void BiTree<NODETYPE>::PrintByDepth()
{
	if (!rootPtr)
		return;

	BiTNode<NODETYPE> *p;
	BiTNode<NODETYPE> *back; // 操作中记录队列尾部的指针
	queue<BiTNode<NODETYPE> *> Q; // 使用辅助队列

	Q.push(rootPtr);
	back = Q.back();
	while (!Q.empty())
	{
		p = Q.front();
		Q.pop();
		visit(p);

		if (p->lchild)
			Q.push(p->lchild);
		if (p->rchild)
			Q.push(p->rchild);

		if (p == back)
		{
			cout << endl;
			if (!Q.empty())
				back = Q.back(); // 更新back指针的位置
		}
	}
}

template<typename NODETYPE>
void BiTree<NODETYPE>::visit(BiTNode<NODETYPE> *p)
{
	cout << left << setw(5) << p->data;
}

#endif

