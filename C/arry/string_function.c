#include <stdio.h>
#include <string.h>
#define N 50

char *mystrcat(char *dest, const char *src);
char *mystrcpy(char *dest, const char *src);

int main()
{
	char buf[N];
	char *src_1 = "hello";
	char *src_2 = "world";
	mystrcpy(buf,src_1);
	puts(buf);
	mystrcat(buf,src_2);
	puts(buf);
	return 0;
}
char *mystrcat(char *dest, const char *src)
{
	char *p = dest;
	while(*dest++);
	dest--;
	while(*src)
		*dest++ = *src++;
	*dest = 0;
	return p;
}
char *mystrcpy(char *dest, const char *src)
{
	char *p = dest;
	while(*src)
		*dest++ = *src++;
	*dest = 0;
	return p;
}
