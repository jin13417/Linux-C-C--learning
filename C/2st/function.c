#include <stdio.h>
#define EXPR(a,b,c) (b*b - 4 *a*c)
#include <math.h>
int main()
{
	float a,
		  b,
		  c,
		  mysqrt,
		  root1,
		  root2;

	puts("input a b c:");
	scanf("%f%f%f",&a,&b,&c);
	if(EXPR(a,b,c) < 0)
	{
		puts("invalid data");
		return -1;
	}
	mysqrt= sqrt(EXPR(a,b,c) );
	root1 = (-b + mysqrt)/(2 * a);
	root2 = (-b - mysqrt)/(2 * a);
	printf("root1 = %.2f\nroot2 = %.2f\n",root1,root2);
	return 0;
}
