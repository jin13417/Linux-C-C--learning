#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
int main()
{
	int fq = open("hole.tet",O_RDWR | O_CREAT | O_EXCL,0644);
	if(-1 == fq)
		perror("open");
	int len = write(fq,"hello",5);
	lseek(fq,12,SEEK_CUR);
	len = write(fq,"world",5);
}

