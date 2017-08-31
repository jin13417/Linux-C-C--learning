#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>
#define N 2
#define BUFSIZE 2046

union semun{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
	struct seminfo *_buf;
};
int main()
{
	key_t key;
	char *str;
	int shmid,semid;
	union semun un;
	struct sembuf buf[N];

	

	while((key = ftok(".",'b'))== -1);

	if((shmid = shmget(key,BUFSIZE,IPC_CREAT | 0666)) < 0)
	{
	     perror("fail to shmget");
	     exit(-1);
	}
	if((str = shmat(shmid,NULL,0)) < (char *)0)
     {
		 perror("fail to shmat");
		 exit(-1);
	 }

	if((semid = semget(key,N,IPC_CREAT | IPC_EXCL | 0666)) < 0)
	{
		if(EEXIST == errno)
		{
			semid = semget(key,N,0666);
		}
		else
		{
			perror("fail to semget");
			exit(-1);
		}
	}
	else//定义 a[0] 为写信号灯，a[1]为读信号灯
	{
		un.val = 1;
		if(semctl(semid,0,SETVAL,un) < 0)
		{
			perror("fail to semctl");
				exit(-1);
		}
		un.val = 0;
		if(semctl(semid,1,SETVAL,un) < 0)
		{
			perror("fail to semctl");
				exit(-1);
		}
	}
	while(1)
	{
		//写着p操作；
		buf[1].sem_num = 0;
		buf[1].sem_op = -1;
		buf[1].sem_flg = 0;
		semop(semid,buf,1);
		fgets(str,BUFSIZE,stdin);
		//读者v操作；
         buf[0].sem_num = 1;
		 buf[0].sem_op = 1;
		 buf[0].sem_flg = 0;
		 semop(semid,buf,1);
		 if(strcmp(str,"quit\n") == 0)
			 break;
	}
	return 0;
}







