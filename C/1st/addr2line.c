#include <stdio.h>

int a;
static int b;
static int c =99;
void foo()
{
	printf("the addrss of foo() is %p\n",foo);
}
int main()
{
	int d = 99;
	foo();
	printf("the addrss of main() is %p\n",main);
	return 0;
}



