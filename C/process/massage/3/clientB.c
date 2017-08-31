#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <string.h>
#include <signal.h>
#define BUFSZ 512
#define TYPEA 100
#define TYPEB 200
#define LEN (sizeof(msg)-sizeof(long))
typedef struct 
{
	long mytape;
	char mtext[BUFSZ];
}msg; 

int main()
{
	key_t key;
	int msqid;
	msg p;
	int pid;

	if((key = ftok(".",'a')) < 0)
	{
		perror("fail to ftok");
		exit(-1);
	}

	if((msqid = msgget(key,IPC_CREAT | 0666)) < 0)
	{
		perror("fail to mesgget");
		exit(-1);
	}
	if((pid = fork()) < 0)
	{
		perror("fail to fork");
		exit(-1);
	}
	else
		if(pid==0)//子进程接收消息
		{
			while(1)
			{
				msgrcv(msqid,&p,LEN,TYPEB,0);
				if(strcmp(p.mtext,"quit\n") == 0)
				{
					kill(getppid(),SIGUSR1);
					msgctl(msqid,IPC_RMID,NULL);
					exit(0);
				}
				printf("clientA message is :%s\n",p.mtext);
			}
		}
		else
		{//父进程写发消息

				p.mytape = TYPEA;
			while(1)
			{
				puts("clientA input the message:");
				fgets(p.mtext,BUFSZ,stdin);
				msgsnd(msqid,&p,LEN,0);
				if(strcmp(p.mtext,"quit\n") == 0)
					break;
			}
					kill(pid,SIGKILL);
					exit(0);
		}
	return 0;
}




