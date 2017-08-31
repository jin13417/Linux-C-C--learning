#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
//具有超时限制的READ调用
#define MAXLINE 4096

static void sig_alarm(int);

int main()
{
	int n;
	char line[MAXLINE];

	alarm(1);//设置闹钟

	if(signal(SIGALRM,sig_alarm) == SIG_ERR)//接收闹钟时间到的信号；
	{
		perror("signal");
			exit(-1);
	}

	if ( (n = read(STDIN_FILENO,line ,sizeof(line))) < 0)//标准输入
		//到标准输出的读写；
	{
		perror("fail to read");
		exit(-1);
	}
		write(STDOUT_FILENO,line,n);
	return 0;
}

void sig_alarm(int signal)
{
	printf("alarm is here~~~~~~~~~");
	exit(0);
}
