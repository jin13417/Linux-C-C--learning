
#include <stdio.h>
#include <stdlib.h>

typedef int datatype;

typedef struct node{
	datatype data;
	struct node *next;
}linknode,*linkstack;

linkstack createlinkstact()//创建链式栈；
{
	linkstack num;
	num = (linkstack)malloc(sizeof(linknode));
	num -> next = NULL;
	return num;
}
void pushstack(linkstack s,datatype x)//元素进栈；
{
	linkstack p;
	p = (linkstack)malloc(sizeof(linknode));
	p -> next = s -> next;
	s -> next = p;
}
datatype popstack(linkstack s)//元素出栈，并返回栈顶元素的数值；
{
	datatype x;
	linkstack p;
	if( s -> next ==NULL)
	{
		printf("the stack is empty!");
		break;
	}

	p = s -> next;
	x = p -> data;
	s -> next = p -> next;
	free(p)
}
datatype gettopstack(linkstack s)//获得栈顶元素的数值；
{
   return s -> next -> data;
}


