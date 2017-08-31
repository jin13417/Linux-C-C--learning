#include <stdio.h>
#include <stdlib.h>
#include "qiu.h"
#define N1 4
#define N5 11
#define N60 11

int isorder(linkqueue *lq)
{
	linklist p = lq -> front -> next;
	while(p -> next != NULL)
	{
		if(p -> data > p -> next -> data)
			return 0;
		p = p -> next;
	}
	return 1;
}

		
int main()
{
	int i,sum=0;
	linkqueue *lq;
	seqstack *s1,*s5,*s60;
	lq = Createlinkqueue();
	for(i=1;i<=27;i++)
	{
		Enlinkqueue(lq,i);
	}
	s1 = Create();
	s5 = Create();
	s60 = Create();
	while(1)
	{
		sum++;
		i = Delinkqueue(lq);
		if(s1 -> top != N1-1)
		{
			pushseqstack(s1,i);
			continue;
		}
		while(!Emptyseqstack)
		{
			Enlinkqueue(lq,popstack(s1));
		}
		if(s5 -> top != N5-1)
		{
			pushseqstack(s5,i);
			continue;
		}
		while(!Emptyseqstack)
		{
			Enlinkqueue(lq,popstack(s5));
		}
		if(s60 -> top != N60-1)
		{
			pushseqstack(s60,i);
			continue;
		}
		while(!Emptyseqstack)
		{
			Enlinkqueue(lq,popstack(s60));
		}
		Enlinkqueue(lq,i);
		if(isorder(lq))
			break;
	}
	printf("%d\n",sum);





		return 0;
	}

