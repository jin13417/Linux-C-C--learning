#include <stdio.h>
#include <stdlib.h>
#include "linkqueue.h"
int main()
{
 int i ;
 linkqueue *lq;
 lq = Createlinkqueue();
 for(i=1;i<=27; i++)
 {
	 Enlinkqueue(lq,i);
 }
#if 0
 for(i=0;i<27;i++)
	 printf("%d ",Delinkqueue(lq));
 puts("");
#endif
 return 0;
}
