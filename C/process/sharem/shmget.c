#include <stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <errno.h>
#include <stdlib.h>

#define BUFSIZE 2048

int  main()
{
	int shmid;
	char *shmadd;
	key_t key;
key = ftok(".",'a');
	if((shmid = shmget(key,BUFSIZE,IPC_CREAT | IPC_EXCL | 0666)) < 0)
//	if((shmid = shmget(IPC_PRIVATE,BUFSIZE, 0666)) < 0)
	{
		if(EEXIST == errno)//判断是否存在；存在直接打开；
		{
			shmid = shmget(key,BUFSIZE,0666);
		}
		else
		{
			perror("fail to shmget");//其他出错；退出；
			exit(0);
		}
	}
	printf("created shared-memory : %d\n",shmid);
	system("ipcs -m");//查看信息
	if((shmadd = (char *)shmat(shmid,NULL,0)) < (char *)0)//
	{// 创建映射
		perror("fail to shmat");
		exit(-1);
	}

	printf("attached shared-memory\n");
	system("ipcs -m");

	if((shmdt(shmadd)) < 0)//删除映射
	{
		perror("fail to shmdt");
		exit(-1);
	}
	printf("detach shared-memory\n");
	system("ipcs -m");

	shmctl(shmid,IPC_RMID,NULL);//删除IPC对象
	system("ipcs  -m");

	return 0;
}



