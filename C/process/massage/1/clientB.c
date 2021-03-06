#include <stdio.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/ipc.h>
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
	
	if((key = ftok(".",'a')) < 0)
	{
		perror("fail to ftok");
		exit(-1);
	}

	if((msqid = msgget(key,IPC_CREAT|0666)) < 0)
	{
		perror("fail to mesgget");
		exit(-1);
	}
	while(1)
	{
		msgrcv(msqid,&p,LEN,TYPEB,0);
		printf("clientB message is :%s",p.mtext);
		puts("clientB input the message:");
		fgets(p.mtext,BUFSZ,stdin);
		p.mytape = TYPEA;
		msgsnd(msqid,&p,LEN,0);
	}
	return 0;
}




