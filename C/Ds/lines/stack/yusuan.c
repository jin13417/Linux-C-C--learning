
#include <stdio.h>
#include <stdlib.h>
#define N 80
typedef int datatype;
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
int emptylinkstack(linkstack *hb)
{
	return (hb-> next == NULL);
}

void pushlinkstack(linkstack *ha,int x)
{
	linkstack *p;
	p = (linkstack *)malloc(sizeof(linkstack));
	p-> data = x;
	p -> next = ha -> next;
	ha -> next = p;
}
datatype gettoplinkstact(linkstack *s)
{
	return (s -> next -> data);
}
int Pri( int x)
{
	switch ((char)x)
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

int Coputer(int a,int b,int c)
{
	switch ((char)c)
	{
	case '+':
		return b+a;
	case '-':
		return b-a;
	case '*':
		return b*a;
	case '/':
		return b/a;
	}
	return 0;
}



int main()
{
	char str[N],*p = str;
	int sum = 0;
	int a,b,z,c;
	fgets(str,N,stdin);
	linkstack *ha,*hb;
	ha = createlinkstack();
	hb = createlinkstack();
	while (*p)
	{
		if(*p >= '0'&& *p <= '9')
		{
			while(*p >= '0' && *p <= '9')
			{
				sum = sum*10 + *p - '0';
				p++;
			}
			pushlinkstack(ha,sum);
			sum = 0;
		}
		else
		{
			while(!emptylinkstack(hb) && Pri(*p) <= Pri(gettoplinkstact(hb)))
			{
				a = poplinkstack(ha);
				b = poplinkstack(ha);
				c = poplinkstack(hb);
				z = Coputer(a,b,c);
				pushlinkstack(ha,z);
			}
				pushlinkstack(hb,*p);
			p++;
		}
	}

	while(!emptylinkstack(hb))
	{
		a = poplinkstack(ha);
		b = poplinkstack(ha);
		c = poplinkstack(hb);
		z = Coputer(a,b,c);
		pushlinkstack(ha,z);
	}

	printf("%d \n",poplinkstack(ha));

	return 0;
}


