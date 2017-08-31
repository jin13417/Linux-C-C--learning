#include <stdio.h>
#include <string.h>
#define N 50

int main()
{

	char str[5] = {1,2,3,4,5};
	char (*p)[5] = &str;
	printf("p + 1 = %p\n",p ++);
	
	return 0;


#if 0
	int *arry[5];
	int a = 1,b = 2,c = 3,d = 4,e = 5;
	arry[0] = &a;
	arry[1] = &b;
	arry[2] = &c;
	arry[3] = &d;
	arry[4] = &e;

	printf("a = %d\n",*arry[0]);
#endif

	return 0;
}
