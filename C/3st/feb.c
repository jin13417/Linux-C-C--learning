#include <stdio.h>
#define N 20
int main()
{
	int a[N] = {1,1};
	int i;
	for(i = 0; i < N - 2; i ++)
		a[i+2] = a[i] + a[i+1];
	for(i = N -1; i >= 0; i --)
	{
		printf("%d\t",a[i]);
		if(!(i % 5))
			puts("");
	}
	return 0;
}
