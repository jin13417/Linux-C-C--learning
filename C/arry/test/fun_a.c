extern int(*p)(void);
int fun_a(void)
{
	printf("p = %p\n",p);
	puts("hello i am fun_b of extern !");
	p();
	return 0;
}
