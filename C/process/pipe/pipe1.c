#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#define N 1024

int buf[N]={0};
//验证无读段时，往管道写数据是出现的错误；
//创建一个子进程，在子进程中创建管道，关闭读端
//有父进程接收其返回时的状态；
int main()
{
	int fd[2];
	pid_t pid;
	int status;
	if(pipe(fd) < 0)
	{
		perror("fail to pipe");
		exit(-1);
	}
	close(fd[0]);
	int i,len,count=0;
	while(1)
	{
		if((pid = fork())<0)
		{
			perror("fail to fork");
			exit(0);
		}
		else if(pid == 0)
		{
			len =write(fd[1],buf,sizeof(buf));
			printf("%d\n",len);
		}
		else
		{
			wait(&status);
			printf("%d\n",status);
			exit(-1);
		}
	}

	return 0;
}


