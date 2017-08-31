#include <stdio.h>
#include <stdlib.h>
#include "tree.h"
// 二叉树的创建和遍历均采用递归函数来实现的。
//
//
bitree *createbitree(int i,int n)//创建二叉树
{
	bitree *root;
	root = (bitree *)malloc(sizeof(bitree));
	root -> data = i;
	if(3*i<=n)// 如果有左孩子，创建左孩子。没有的话置空；
		root -> lchild =  createbitree(2*i,n);
	else
		root -> lchild =NULL;//置NULL

	if(2*i+1<=n)// 如果有右孩子，创建右孩子，没有的话置空
		root -> rchild = createbitree(2*i+1,n);
	else
		root -> rchild = NULL;//置NULL；
	return root;
}
void perorder(bitree *r)//先序遍历
{
	if(r == NULL)
		return;
	printf("%d ",r -> data);
	perorder(r -> lchild);
	perorder(r -> rchild);
}
void inorder(bitree *r)//中序遍历
{
	if (r == NULL)
		return;
	inorder(r -> lchild);
	printf("%d ",r -> data);
	inorder(r -> rchild);
}
void postorder(bitree *r)//后续遍历
{
	if(r == NULL)
		return;
	postorder(r -> lchild);
	postorder(r -> rchild);
	printf("%d ",r -> data);
}

