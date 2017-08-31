#include <stdio.h>
#define MAXLINE 20

int main()
{
	char line[MAXLINE];
	while(fgets(line,MAXLINE,stdin) != NULL && line[0] != '\n')
	{
		fputs("result: ",stdout);
		fputs(line,stdout);
	}
	return 0;
}

