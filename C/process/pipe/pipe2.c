#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_DATA_LEN 256
#define DELAY_TIME  1
//创建父子进程，父进程进行写操作，子进程进行读操作，并打印出结果；
int main()
{
	pid_t pid;
	int pipe_fd[2];
	char buf[MAX_DATA_LEN];
	const char data[] = "Pipe Test Program";
	int real_read,real_write;

	memset((void *)buf,0,sizeof(buf));//初始化BUF

	if(pipe(pipe_fd) < 0)
	{
		perror("fail to Pipe ");
		exit(0);
	}

	if((pid =fork()) == 0)//创建子进程，子进程中进行读缓存；
	{
		close(pipe_fd[1]);//关闭管道的写端
		sleep(DELAY_TIME*3);

		if((real_read = read(pipe_fd[0],buf,MAX_DATA_LEN)) > 0)
		{
			printf("%d bytes read form the pipe is %s\n",real_read,buf);
		}
		close(pipe_fd[0]);//关闭管道读端
				exit(0);
	}
	else 
		if(pid > 0)//父进程进行写操作；
  {
	  close(pipe_fd[0]);//关闭管道的读端；
	  sleep(DELAY_TIME);
	  if((real_write = write(pipe_fd[1],data,strlen(data))) != -1)
	  {
		  printf("parent write %d bytes : %s \n",real_write,data);
	  }
	  close(pipe_fd[1]);//关闭管道的写端；
	  waitpid(pid,NULL,0);
	  exit(0);
  }
}


