#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

static int fd,oflags;

void intput_handler (int signo)
{
	int key;
	read(fd,(char *)&key,sizeof(key));
	printf("key %d is fall down!\n",key);
}
int main()
{
	if((fd = open ("/dev/irq",O_RDWR)) < 0)
	{
		perror("fail to open");
		exit(-1);
	}
   //设置异步通知模式
	signal(SIGIO,intput_handler);
	fcntl (STDIN_FILENO,F_SETOWN,getpid());
	oflags = fcntl(STDIN_FILENO,F_GETFL);
	fcntl (STDIN_FILENO,F_SETFL,oflags | FASYNC);
	pause();
	return 0;
}

