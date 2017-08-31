#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<string.h>
#include <signal.h>
#include <errno.h>

#define BUFFER_SIZE 1024

void signal_handler(int s);

int main(int argc,char *argv[])
{
	int fd[2];

	if(argc < 3)
	{
		fprintf(stdout, "usage: %s <filename>\n:",argv[0]);
		exit(-1);
	}

	signal(SIGPIPE,signal_handler);//当收到管道破裂是，打印相应的信息；

	if((fd[0] = open(argv[2],O_WRONLY)) < 0)//以只读方式打开管道
	{
		perror("fail to open");
		exit(-1);
	}

	if((fd[1] = open(argv[1],O_RDONLY)) < 0)//以只读方式打开文件
	{
		perror("fail to open");
		exit(-1);
	}
//成功的话，打印读管道成功；
	fprintf(stdout,"open fifo %s for writing successed. \n",argv[0]);

	char buffer[BUFFER_SIZE];
	ssize_t n;
	int len;
//读文件，当未到末尾时进行循环；读完退出循环
	while((len = read(fd[1],buffer,sizeof(buffer))) > 0)//读文件，
	{
again:
		if((n = write(fd[0],buffer,len)) < 0)//将读到的文件写进管道里
		{
			if(errno == EINTR )
			{
				goto again;
			}
			else
			{
				perror("fail to write");
				break;
			}
		}
	}
	return 0;
}


void signal_handler(int signo)
{
	fprintf(stdout,"CAUGHT signal %d\n",signo);
}

