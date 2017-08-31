#include <stdio.h>
#include <stdlib.h>

typedef int datatype;
typedef struct node
{
	datatype data;
	struct node *lchild,*rchild;
}bitree;

bitree *createtree(int i,int n)
{
	bitree *root;
root = (root)malloc(sizeof(bitree));
root -> data =i;
if(2*i <= n)
	root -> lchild = createtree(2*i,n);
else
	root -> lchild = NULL;
if(2*i+1 <= n)
	root -> rchild = createtree(2*i+1,n);
else
	root -> rchild = NULL;
return root;
}
void preorder(bitree *root)
{
	if(NULL == root)
		return;
	printf("%d ",root -> data);
			preorde(root -> lchild);
			preorde(root -> rchild);

}

int main()
{
	int i=0,n;
	bitree *root;
	scanf("%d",&n);
root =  createtree(i,n);
preorder(root);
}
