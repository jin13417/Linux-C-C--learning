#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

#define N 18

typedef int datatyde;
typedef struct {
	bitree *data[N];
	int front,rear;
}sequeue;

sequeue *Createsequeue();
int Emptysequeue(sequeue *sq);
int Fullsequeue(sequeue *sq);
void Clearsequeue(sequeue *sq);
void Ensequeue(sequeue *sq,bitree *x);
bitree *Desequeue(sequeue *sq);


sequeue *Createsequeue()
{
	sequeue *sq;
	sq=(sequeue *)malloc(sizeof(sequeue));
	sq ->	front = sq -> rear=0;
	return sq;
}

int Emptysequeue(sequeue *sq)
{
	return (sq -> front == sq -> rear);
}
int Fullsequeue(sequeue *sq)
{
	return ((sq -> rear+1)%N == sq -> front);
}
void Clearsequeue(sequeue *sq)
{
	sq -> front = sq -> rear;
	return;
}
void Ensequeue(sequeue *sq,bitree *x)
{
	sq -> rear = (sq -> rear+1) % N;
	sq -> data[sq -> rear] = x;
}

bitree *Desequeue(sequeue *sq)
{
	sq -> front = (sq -> front + 1) % N;
	return (sq -> data[sq -> front]);
}



void noorder(bitree *root)
{
	sequeue *lq;

	lq = Createsequeue();
	Ensequeue(lq,root);
	while(!Emptysequeue(lq))
	{
		root = Desequeue(lq);
		printf("%d ", root->data);
		if(root -> lchild != NULL)
			Ensequeue(lq,root -> lchild);
		if(root -> rchild != NULL)
			Ensequeue(lq,root -> rchild);
	}
}

int main()
{
	bitree *root;
	root = createbitree(1,10);
	noorder(root);
	return 0;
}





