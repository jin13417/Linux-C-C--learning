#include <stdio.h>
#include <fcntl.h>
#define  N 20
int main()
{
	char s[N];
	int fd = open("a.txt",O_WRONLY);
	int len = read(fd,s,N-1);
	if(len != N)
		perror("read");
	return 0;
}
