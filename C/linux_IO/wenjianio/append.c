#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
int main()
{
//	int fd = open ("a.txt",O_RDWR);
	int fd = open ("a.txt",O_RDWR | O_APPEND);
	if( -1 == fd)
		perror("read ");
	int buf[20];
    int len = write(fd,"my name is jsh ",17);
	if(-1 ==len || len !=17)
		perror("write ");
	int le = read(fd,buf,15);
		if(le !=15)
			perror("read");
	return 0;
}

