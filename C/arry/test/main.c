#include <stdio.h>
int fun_a(void);
int fun_b(void);
static int (*p)(void);
int main()
{
	printf("fun_b = %p\n",fun_b);
	p = fun_b;
	printf("p = %p\n",p);
	fun_a();
	return 0;
}

int fun_b(void)
{
	puts("hello i am static fun_b !");
	return 0;
}
