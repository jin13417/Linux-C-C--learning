#include <stdio.h>
#include <string.h>

#define N 20
int main()
{
	char *p  = "helloworld";
	printf("sizeof(\"helloworld\") = %d\n",sizeof("helloworld"));
	printf("sizeof(\"helloworld\") = %d\n",sizeof(p));
	printf("strlen(\"helloworld\") = %d\n",strlen(p));
	printf("strlen(\"helloworld\") = %d\n",strlen("helloworld"));
	return 0;
}
