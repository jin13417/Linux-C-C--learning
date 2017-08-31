
#include <stdio.h>
#include <stdlib.h>
#define N 30
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
	p -> data = x;
	p -> next = s -> next;
	s -> next = p;
}
datatype popstack(linkstack s)//元素出栈，并返回栈顶元素的数值；
{
	datatype x;
	linkstack p;
	p = s -> next;
	x = p -> data;
	s -> next = p -> next;
	free(p);
	return x;
}
datatype gettopstack(linkstack s)//获得栈顶元素的数值；
{
	return s -> next -> data;
}

int compare(int x)
{
	switch (x)
	{
	case '*':
	case '/':
		return 2;
	case '+':
	case '-':
		return 1;
	}
	return 0;
}

int compute(left,right,sign)
{
	switch (sign)
	{
	case '+':
		return left + right;
	case '-':
		return left - right;
	case '*':
		return left * right;
	case '/':
		return left / right;
	}
	return 0;
}
int main()
{
	char str[N], *p=str;
	int sum=0;
	int left,right,sign;
	linkstack num,sym;
	num = createlinkstact();
	sym = createlinkstact();
	scanf("%s",str);
	getchar();

	while(*p)
	{
		if(('0' <= *p) && (*p <= '9'))
		{
			while(('0' <= *p && *p <= '9'))
			{
				sum = sum * 10 + *p - '0';
				*p++;
			}
			pushstack(num,sum);
			sum=0;
		}
		else
		{
			if((sym -> next != NULL) && compare(*p) <=compare(gettopstack(sym)))
			{
				right = popstack(num);
				left =  popstack(num);
				sign = popstack(sym);
				pushstack(num,compute(left,right,sign));
			}
			pushstack(sym,*p);
			p++;
		}
	}
	while( sym-> next != NULL)
	{
		right = popstack(num);
		left =  popstack(num);
		sign = popstack(sym);
		pushstack(num,compute(left,right,sign));
	}
	printf("%s = %d\n",str,gettopstack(num));
	return 0;
}








