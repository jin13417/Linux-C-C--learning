#include <stdio.h>
int add(int x,int y)
{
	return x + y;
}
int main()
{
	void *p;
	p = add;
	int i;
	i = ((int(*)(int,int))p)(10,20);
	printf("%d\n",i);
}

