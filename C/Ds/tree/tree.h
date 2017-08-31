typedef int datatype;
typedef struct node{
	datatype data;
	struct node *lchild,*rchild;
}bitree;

bitree *createbitree(int,int);

