#include <stdio.h>
#include <stdlib.h>
#include "linkqueue.h"


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

