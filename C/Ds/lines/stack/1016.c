#include <stdio.h>
#include <stdlib.h>
#define N 20
typedef int datatype;
typedef struct stack{
datatype data[N];
int top;
}sqstack;

int main()
{
	int n;
	scanf("%d",&n);
	sqstack *s;
	s = (sqstack *)malloc(sizeof(sqstack));
	s -> top =-1;
	while(n>0)
	{
		s -> data[++s->top]=n%16;
		n= n/16;
	}
	while(-1 !=s->top)
	{
	  if(s -> data[s ->top] > 9)
		  printf("%c",s -> data[s -> top]-10 + 'a');
	  else
		  printf("%d",s-> data[s -> top]);
	 s -> top --;
	}
	puts("");
	return 0;
}
