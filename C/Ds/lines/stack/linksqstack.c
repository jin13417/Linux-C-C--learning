#include <stdio.h>
#include <stdlib.h>

typedef char datatype;
typedef struct node{
	datatype data;
	struct node *next;
}linkstack;

linkstack *createlinkstack()
{
	linkstack *s;
	s=(linkstack *)malloc(sizeof(linkstack));
	s -> next =NULL;
	return s;
}
int emptylinkstack(linkstack *s)
{
	return (s -> next == NULL);
}
void pushlinkstack(linkstack *s,datatype x)
{
	linkstack *p;
	p = (linkstack *)malloc(sizeof(linkstack));
	p -> data = x;
	p  -> next = s -> next;
	p = s -> next;
}
datatype poplinkstack(linkstack *s)
{
	linkstack *p;
	datatype x;
	p = s -> next;
	s -> next = p -> next;
	x = p ->data;
	free(p);
	return x;
}
datatype gettoplinkstact(linkstack *s)
{
	return (s -> next -> data);
}
void clearlinkstact(linkstack *s)
{
	s -> next = NULL;
}
char parter(char ch)
{
	switch (ch)
	{
	case '}':
		return '{';
	case ')':
		return '(';
	case ']':
		return '[';
	}
	return 0;
}

int main()
{
	int i=0;char str[100],*q=str;

	fgets(str,100,stdin);

	linkstack *p;
	p= createlinkstack();
	while(*q)
	{
		switch (*q)
      {
	  case '{':
	  case '(':
	  case '[':
	     pushlinkstack(p,*q);
		 break;
	  }

		if(emptylinkstack(p)|| poplinkstack(p)==parter(*q))
		{
           i=1;
		   break;
		}
		else
			break;

		q++;
	}
	if(i==1&&!emptylinkstack(p))
		printf("the break are match!! \n");
	else
		printf("the break are unmatch!! \n");

}




