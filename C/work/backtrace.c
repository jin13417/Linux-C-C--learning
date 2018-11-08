/*************************************************************************
 > File Name: backtrace.c
 > Author:  jinshaohui
 > Mail:    jinshaohui789@163.com
 > Time:    18-10-07
 > Desc:    
 ************************************************************************/
#include<stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <execinfo.h>
#include <signal.h>
#include <assert.h>

#define myassert(flg)\
do{\
	int pid = getpid();\
	if(!flg)\
	{\
		printf("\r\n file:%s,Line:%d,fuc:%s\r\n",__FILE__,__LINE__,__FUNCTION__);\
	    kill(pid,SIGUSR1);\
	}\
}while(0)
void dump(int signo)
{
	void *buffer[30] = {0};
	size_t size = 0;
	size_t i = 0;
	char ** strings = NULL;

	size = backtrace(buffer,30);

	strings = backtrace_symbols(buffer,size);
	if(strings == NULL)
	{
		return;
	}

	for (i = 0 ; i< size; i++)
	{
		printf("%s\n",strings[i]);	
	}

	free(strings);

	//exit(0);
}

void trace_3()
{
	int * p = NULL;
	myassert((p != NULL));
	
}

void trace_2()
{
	trace_3();
}

void trace_1()
{
	trace_2();
}

int main()
{
    char c = 0;
	/*用户捕捉myassert 信号*/
	signal(SIGUSR1,dump);

	/*捕捉assert 异常信号*/
	signal(SIGABRT,dump);

	trace_1();
    c = getchar();
    assert(0);

	return;
}

