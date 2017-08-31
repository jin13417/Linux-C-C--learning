#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<pthread.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/syscall.h>
//创建一个线程，并接收其返回值：
char message[32] = "hello world";
void * thread_function(void *arg);

pid_t gettid()
{
	return syscall(SYS_gettid);
}
void * thread_function(void *arg)//线程执行函数
{
	printf(" tid = %d\n",gettid());
	printf("thread_function is runing,argument is %s\n",(char *)arg);//打印传参；
	strcpy(message,"marked by thread");//更改字符串
	pthread_exit("thank you for the cpu time ");//线程退出，并返回一句话；

}


int main()
{
	pthread_t a_thread;
	void  *thread_result;
	if(pthread_create(&a_thread,NULL,thread_function,(void *)message) < 0)//创建一个线程，
	{
		perror("fail to pthread_create");//并判断是否创建成功，未成功设置verrno，并退出；
		exit(-1);
	}
	printf("waiting for thread finish\n");
	printf("pid = %d \n",getpid());
	sleep(1);
	if(pthread_create(&a_thread,NULL,thread_function,(void *)message) < 0)//创建一个线程，
	{
		perror("fail to pthread_create");//并判断是否创建成功，未成功设置verrno，并退出；
		exit(-1);
	}
	printf("pid = %d \n",getpid());
	if(pthread_join(a_thread,&thread_result) < 0)//接收线程的返回值：
	{
		perror("fail to pthread_join");
		exit(-1);
	}
	printf("message is %s , result is %s\n",message,(char *)thread_result);//打印；
	return 0;
}

