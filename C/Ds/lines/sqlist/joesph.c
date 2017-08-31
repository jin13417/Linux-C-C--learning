#include <stdio.h>
#include <stdlib.h>
#define M 8
#define N 3

typedef int datatype;
typedef struct node{
	datatype data;
	struct node *next;
}linknide,*linklist;

int main()
{
  linklist h,p;
 int i;
  h = (linklist)malloc(sizeof(linknide));
  h -> next = h;
   h -> data =1;
  for(i=2;i<=M;i++)
  {
  p = (linklist)malloc(sizeof(linknide));
   p -> data =i;
  p -> next = h -> next;
  h -> next = p;
  h = h -> next;
  }
  h = h -> next;
 visitlinklist(h) ;
 visitlinklist1(h) ;

	return 0;
}
int visitlinklist(linklist h)
{
	int i;
	for (i=0;i<M;i++)
	{
		printf("%d ",h -> data);
		h = h -> next;
	}
	puts("");
	return 0;
}
int visitlinklist1(linklist h)
{
	linklist p;
	int i;
	for(i = 1;i<N;i++)
		h =h -> next;
	while(h != h -> next)
	{
	 
		for(i=0;i<2;i++)
			h = h ->next;
		    p = h -> next;
			h -> next = p -> next;
			printf("%d ",p -> data);
			free(p);
			h = h -> next;
	}
	printf("%d\n",h ->data);
	free(h);
	return 0;
}
			




