#include <stdio.h>
int main()
{
	int i;
	char str[10] ;
	for(i = 0; i < 10; i ++)
	{
		str[i] = getchar();
		if(str[i] == '#')
		{
			str[i] = 0;
			break;
		}
	}
	puts(str);
	puts("--------------------------");
	for(i = 0; i < 10; i ++)
		printf("%d\t",str[i]);

	return 0;
}
