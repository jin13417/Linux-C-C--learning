#include "sequeue.h"
#include <stdio.h>
#include <stdlib.h>



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
void Ensequeue(sequeue *sq,datatyde x)
{
	sq -> rear = (sq -> rear+1) % N;
	sq -> data[sq -> rear]=x;
}

datatyde Desequeue(sequeue *sq)
{
  sq -> front = (sq -> front + 1) % N;
 return (sq ->data[sq -> front]);
}

