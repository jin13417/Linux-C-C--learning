#include <stdio.h>
int main()
{
	int i = 10;
#if 1
	while(i < 10)
		i ++;


#else
	do
	i ++;
	while(i < 10);
#endif
	printf("i = %d\n",i);
	return 0;
}
