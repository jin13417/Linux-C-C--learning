#include <stdio.h>
#include <stdlib.h>
#define M 8
#define N 4
#define K 3

typedef int datatype;
typedef struct node{
	datatype data;
	struct node *next;
}linknode,*linglist;

linglist createlinklist()
{
	linglist l;
	l=(linglist)malloc(sizeof(linknode));
	l -> next =l;
	l -> data =1;
	return l;
}

int main()
{
	int i;
	linglist p,l,q;
	p= createlinklist();
	for(i=2;i<=M;i++)
       {
		   l = (linglist)malloc(sizeof(linknode));
		   l -> data =i;
		   l -> next = p -> next;
		   p ->next = l;
		   p = p -> next;
	   }
	p = p -> next;
    for(i=1;i<K;i++)
		p = p -> next;
     while(p -> next != p)
	 {
		 for(i=1;i<N-1;i++)
			 p = p -> next;
      q = p -> next;
	  printf("%d ",q -> data);
	  p -> next = q -> next;
	  free(q);
	  p = p -> next;
	 }
	 printf("%d\n", p -> data);
			 free(p);
	return 0;
}
