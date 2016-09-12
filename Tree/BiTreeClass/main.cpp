#include <iostream>
#include "BiTree.h"
using namespace std;

int main()
{
	int i;
	BiTree<char> T;
	char e1;
	
	//StrAssign(str,"ABDH#K###E##CFI###G#J##");

	T.CreateBiTree();

	printf("构造空二叉树后,树空否？%d(1:是 0:否) 树的深度: %d\n",T.BiTreeEmpty(), T.BiTreeDepthNonRecursion());
	e1 = T.Root();
	printf("二叉树的根为: %c\n",e1);

	printf("\n前序遍历二叉树:\n");
	//T.PreOrderTraverse();
	T.PreOrderNonRecursion();

	printf("\n中序遍历二叉树:\n");
	T.InOrderTraverse();
	//T.InOrderNonRecursion();

	printf("\n后序遍历二叉树:\n");
	//T.PostOrderTraverse();
	T.PostOrderNonRecursion();

	printf("\n层次遍历二叉树:\n");
	T.LevelOrderTraverse();

	printf("\n每行二叉树的最右边的结点为:\n");
	T.PrintLast();

	printf("\n按层次输出每行的结点:\n");
	T.PrintByDepth();

	T.DestroyBiTree();
	printf("\n清除二叉树后,树空否？%d(1:是 0:否) 树的深度=%d\n",T.BiTreeEmpty(),T.BiTreeDepth());
	i = T.Root();
	if(!i)
		printf("树空，无根\n");

	getchar();
	getchar();
	return 0;
}

