#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define N 60


int buff[N];
int main(int argc,char *argv[])
{
	int fd1,fd2;
	if(argc != 3)
	{
		printf("commend error!!");
		return 0;
	}
	fd1 = open(argv[1],O_RDONLY);
	if(fd1 < 0)
	{
		fprintf(stderr,"open %s error %s\n ",argv[1],strerror(errno));
		return -1;
	}

	fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC);
	if(fd2 < 0)
	{
		fprintf(stderr,"open %s error %s\n ",argv[2],strerror(errno));
		return -1;
	}
	int len;
	len=lseek(fd1,0,SEEK_END)/2;
		lseek(fd1,0,SEEK_SET);
	pid_t pid;
	pid = fork();
	if(pid <0)
	{
		perror("fork");
		return -1;
	}
	else if(pid == 0)
	{
		close(fd1);
		close(fd2);
		fd1 = open(argv[1],O_RDONLY);
		fd2 = open(argv[2],O_WRONLY | O_CREAT | O_TRUNC);
		int len2;
		lseek(fd1,len,SEEK_SET);
		lseek(fd2,len,SEEK_SET);
		while((len2 = read(fd1,buff,sizeof(buff))) > 0)
		{
			write(fd2,buff,len2);
			exit(1);
		}
		close(fd1);
		close(fd2);
	}
	else 
	{
		int le1;
		while(len > 0)
		{

			le1 = read(fd1,buff,sizeof(buff));
			len -= le1;
			write(fd2,buff,le1);
		}
	}
	close(fd1);
	close(fd2);
	return 0;
}








