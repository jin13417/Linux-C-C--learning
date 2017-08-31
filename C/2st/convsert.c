
#include <stdio.h>
#define DEBUG 0
int main()
{
	char ch = '#';
	while( '#' != (ch = getchar()))
	{
		if((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z') )
		{
			ch = ch > 'Z' ? (ch -= ' '): (ch += ' ');
			putchar(ch);
			puts("");
		}
	
		else
			puts("invaild !");
		getchar();
	}

	return 0;
}
