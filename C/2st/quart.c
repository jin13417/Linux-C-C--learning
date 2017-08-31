#include <stdio.h>
#define  MASS	3.0E-23
#define QUART	950
int main()
{
	float num;
	float ret;
	puts("input number of quart:");
	scanf("%f",&num);
	ret = num * QUART / MASS;
	printf("ret  = %e\n",ret);
	return 0;

}
