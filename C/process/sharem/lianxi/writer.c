#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>

void hander(int sinal);
#define BUFSIZE 2048
typedef struct
{
	pid_t pid;
	char mess[BUFSIZE];
}shm;
void hander(int sinal)
{
	return;
}
//创建一个共享内存，写着写数据，读者读数据，
int  main()
{
	int shmid;
	pid_t pid;
	char *shmadd;
	key_t key;
	shm *p;
	signal(SIGUSR1,hander);
	key = ftok(".",'a');
	if((shmid = shmget(key,sizeof(shm),IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		if(EEXIST == errno)//判断是否存在；存在直接打开；
		{
			shmid = shmget(key,sizeof(shm),0666);
			if((p = (shm *)shmat(shmid,NULL,0)) < (shm *)0)
			{
				perror("fail to shmat");
				exit(-1);
			}
			pid = p -> pid;
			p -> pid = getpid();
			kill(pid,SIGUSR1);
		}
		else
		{
			perror("fail to shmget");//其他出错；退出；
			exit(0);
		}
	}
	else
	{
		if((p = (shm *)shmat(shmid,NULL,0)) < (shm *)0)
		{
			perror("fail to shmat");
			exit(-1);
		}
		p -> pid = getpid();
		pause();
		pid = p -> pid;
	}
	while(1)
	{
		printf("write mesage:");
		fgets(p -> mess,BUFSIZE,stdin);
		kill(pid,SIGUSR1);
		if(strcmp(p->mess,"quit\n")==0)
		{
			shmdt(p);
			break;
		}
		pause();
	}
	return 0;
}




