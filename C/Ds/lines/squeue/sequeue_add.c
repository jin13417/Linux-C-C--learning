#include "sequeue.h"
#include <stdio.h>



int main()
{
	int i;
	sequeue *sq;
	sq = Createsequeue();
	for( i=1; i<10;i++)
	{
		if(Fullsequeue(sq))
			printf("sq is full\n");
		else
			Ensequeue(sq,i);
	}
	while(!Emptysequeue(sq))
	{
		printf("%d ",Desequeue(sq));
				}
puts("");
	return 0;
}




