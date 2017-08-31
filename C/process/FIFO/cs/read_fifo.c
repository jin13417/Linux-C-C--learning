#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <errno.h>

#define BUFFER_SIZE 1024
//读管道，并讲读的信息写到文件中
int main(int argc,char *argv[])
{
	int fd[2];


	if(argc < 3)//判断，命令行是否输入完整；
	{
		fprintf(stdout, "usage: %s <filename><fifoname>\n:",argv[0]);
		exit(-1);
	}

	if((fd[0] = open(argv[2],O_RDONLY)) < 0)//打开管道，失败打印相应的信息
	{
		perror("fail to open");
		exit(-1);
	}
	if((fd[1] = open(argv[1],O_WRONLY | O_CREAT | O_TRUNC,0644)) < 0)//打开文件
		//若文件不存在创建，存在置空；
	{
		perror("fail to open");
		exit(-1);
	}

//打印打开广岛成功信息：
	fprintf(stdout,"open fifo %s for reading successed.\n",argv[0]);
	char buffer[BUFFER_SIZE];
	ssize_t n;
	while(1)
	{
again:

		if((n = read(fd[0],buffer,BUFFER_SIZE)) < 0)//将管道内的信息读到缓存中，
			//如果没有信息，将阻塞；
		{
			if(errno == EINTR)
			{
				goto again;
			}
			else
			{
				perror("fail to read ");
				exit(-1);
			}
		}
		else if(n == 0)
		{
			fprintf(stderr,"peer closed fifo.\n");
			break;
		}
		else
		{
			write(fd[1],buffer,n);//将缓存的信息写如文件内；
		}
	}
	return 0;
}
