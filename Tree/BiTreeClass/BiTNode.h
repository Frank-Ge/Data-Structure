// 参照《c++大学教程》中P639页编写
// 模版结点BiTNode类的声明

#ifndef BITNODE_H
#define BITNODE_H

// 声明BiNTree类型
template<typename NODETYPE> class BiTree;

template<typename NODETYPE>
class BiTNode
{
	// 声明友元BiNTree类，使得BiTree类可以访问BiTNode类中的private成员
	friend class BiTree<NODETYPE>;

public:
	BiTNode(const NODETYPE &d) 
		: lchild(0), 
			data(d),
			rchild(0)
	{
	}

	NODETYPE getData() const
	{
		return data;
	}

private:
	BiTNode<NODETYPE> *lchild;
	NODETYPE data;
	BiTNode<NODETYPE> *rchild;
};

#endif
