#include <semaphore.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>

//线程同步示例
char buf[60];
sem_t sem_r,
	  sem_w;
void *function(void *arg);
pid_t gettid();

pid_t gettid()
{
	return syscall(SYS_gettid);
}
int main()
{
	pthread_t a_thread;//定义一个线程
	void * thread_result;
	if(sem_init(&sem_r,0,0) < 0)
	{
		perror("fail to sem_init");
		exit(-1);
	}
	if(sem_init(&sem_w,0,1) < 0)
	{
		perror("fail to sem_init");
		exit(-1);
	}

	if(pthread_create(&a_thread,NULL,function,NULL) < 0)
	{
		perror("fail to pthread_creste");
		exit(-1);
	}

	printf("input 'quit' to exit\n");
	do{
		if(sem_wait(&sem_w) == 0)
			fgets(buf,sizeof(buf),stdin);
		else
			continue;
		sem_post(&sem_r);
	}while(strncmp(buf,"quit",4)!= 0);

	//	}while((sem_wait(&sem_w)==0)&&(strncmp(buf,"quit",4)!= 0));

return 0;
}
void *function(void *arg)
{
	while(1)
	{
		if(sem_wait(&sem_r) == 0)
		{
			sem_post(&sem_w);
			printf("you enter %d character tid = %d\n",strlen(buf)-1,gettid());
			pthread_exit(NULL);
		}
		else
			return;
	}
}

