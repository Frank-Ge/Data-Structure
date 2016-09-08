typedef int ElemType;

#ifndef BISEARCHTREE_H
#define BISEARCHTREE_H

typedef struct TreeNode
{
	ElemType data;
	TreeNode *lchild, *rchild;
} TreeNode, *SearchTree, *Position;

SearchTree MakeEmpty(SearchTree T);
Position Find(ElemType x, SearchTree T);
Position FindMin(SearchTree T);
Position FindMax(SearchTree T);
SearchTree Insert(ElemType x, SearchTree T);
SearchTree Delete(ElemType x, SearchTree T);
ElemType Retrieve(Position P);

void PreOrderTraverse(SearchTree T);
void visit(Position P);

#endif
