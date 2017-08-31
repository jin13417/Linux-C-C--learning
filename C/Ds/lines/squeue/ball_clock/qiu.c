#include <stdio.h>
#include <stdlib.h>
#include "qiu.h"


linkqueue *Createlinkqueue()
{
	linkqueue *lq;
	linklist l;
    l = (linklist)malloc(sizeof(linknode));
	lq = (linkqueue *)malloc(sizeof(linkqueue));
lq -> front = lq -> rear = l;
lq -> front -> next = NULL;
return lq;
}
	
int Emptylinkqueue(linkqueue *lq)
{
	return (lq -> front == lq -> rear);
}

void Clearlinkqueue(linkqueue *lq)
{
	linklist q;
   while(	lq -> front != lq -> rear)
   {
	q = lq -> front;
	lq -> front = q -> next;
	free(q);
   }
}
void Enlinkqueue(linkqueue *lq,datatype x)
{
	lq -> rear -> next = (linklist)malloc(sizeof(linknode));
	lq -> rear = lq -> rear -> next;
	lq -> rear -> data = x;
	lq ->rear -> next = NULL;
	return;
}
	
datatype Delinkqueue(linkqueue *lq)
{
	datatype x;
	linklist q;
	q = lq -> front;
	lq -> front = q -> next;
	free(q);
	return lq -> front -> data;
}

seqstack *Create()
{
	seqstack *s;
	s = (seqstack *)malloc(sizeof(seqstack));
	s -> top = -1;
}

int Emptyseqstack(seqstack *s)
{
	return -1 == s -> top;
}

void pushseqstack(seqstack *s,datatype x)
{
	s -> data[++s -> top] = x;
}

datatype popstack(seqstack *s)
{
	datatype x;
    x =	s -> data[s -> top];
	s -> top--;
	return x;
}

datatype gettopseqstack(seqstack *s)
{
	return s ->data[s ->top];
}

void Clearseqstack(seqstack *s)
{
    s->top = -1;
}
