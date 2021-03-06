#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

int value1,value2;
pthread_mutex_t mutex;
void *function(void *arg);
unsigned int count=0;

int main()
{
	pthread_t a_thread;
	void *thread_result;
	if(pthread_mutex_init(&mutex,NULL)<0)
	{
		perror("fail to pthread_mutex_init");
        exit(-1);
	}

	if(pthread_create(&a_thread,NULL,function,NULL) < 0)
	{
		perror("fail to pthread_create");
		exit(-1);
	}
	while(1)
	{
		count++;
#ifdef _LOCK_
	pthread_mutex_lock(&mutex);
#endif
	value1 = count;
	value2 = count;
#ifdef _LOCK_
	pthread_mutex_unlock(&mutex);
#endif
	}
	return 0;
}
void *function(void *arg)
{
	while(1)
	{
#ifdef _LOCK_
		pthread_mutex_lock(&mutex);
#endif
		if(value1 != value2)
		{
			printf("count = %d,value1 = %d. value2 = %d\n",count,value1,value2);
			usleep(100000);
		}
#ifdef _LOCK_
		pthread_mutex_unlock(&mutex);
#endif
	}
	return NULL;
}

