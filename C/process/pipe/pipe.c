#include <unistd.h>
#include <stdio.h>
#define N 100
int pid1,pid2;

int main()
{
	int fd[2];
	char outpipe[N],inpipe[N];
	pipe(fd);
	while((pid1 = fork()) == -1);
	if(pid1 == 0)
	{
		lockf(fd[1],1,0);
		sprintf(outpipe,"child 1 process is sending message!");
		write(fd[1],outpipe,50);
		sleep(1);
		lockf(fd[1],0,0);
		_exit(0);
	}
	else
	{
		while((pid2 = fork()) == -1);
		if(pid2 == 0)
		{
			lockf(fd[1],1,0);
			sprintf(outpipe,"child 2 process is sending message!");
			write(fd[1],outpipe,50);
			sleep(1);
			lockf(fd[1],0,0);
			_exit(0);
		}
		else
		{
			wait(NULL);
			read(fd[0],inpipe,50);
			printf("%s\n",inpipe);
			wait(NULL);
			read(fd[0],inpipe,50);
			printf("%s\n",inpipe);
			_exit(0);
		}
	}
}


