#include <stdio.h>
#include <signal.h>
#include <stdlib.h>

void dirver(int sign_no);
void seller(int sign_no);
int pid;
void seller(int sign_no)
{
	switch(sign_no)
	{
	case SIGINT:
		kill(getppid(),SIGUSR1);
		break;
	case SIGQUIT:
		kill(getppid(),SIGUSR2);
		break;
	case SIGUSR1:
		printf("all get off the bus");
		kill(getppid(),SIGKILL);
		exit(0);
		break;
	default:
		break;

	}
}
void dirver(int sign_no)
{
	switch(sign_no)
	{
	case SIGUSR1:
		printf("GO GO GO\n");
		break;
	case SIGUSR2:
		printf("stop the bus\n");
		break;
	case SIGTSTP:
		kill(pid,SIGUSR1);
		break;
	default:
		break;
	}
}

int main()
{
	int pid;

	while((pid = fork()) == -1);
	if(pid > 0)// 父进程；
	{
		signal(SIGTSTP,dirver);
		signal(SIGINT,SIG_IGN);
		signal(SIGQUIT,SIG_IGN);
		signal(SIGUSR1,dirver);
		signal(SIGUSR2,dirver);
		while(1)
		{
			pause();
		}
	}
	else//子进程
	{
		signal(SIGTSTP,SIG_IGN);
		signal(SIGUSR2,SIG_IGN);
		signal(SIGINT,seller);
		signal(SIGQUIT,seller);
		signal(SIGUSR1,seller);
		while(1)
		{
			pause();
		}
	}
	return 0;
}


