#include <stdio.h>
#include <errno.h>
//出错处理；
int main()
{
	FILE *fq = fopen("../hello","r");//打开一个不存在的文件
	if(NULL == fq)
	{
		printf("%d\n",errno);
		printf("errno str = %s\n",strerror(errno));//strerror函数返回值是char *，传参是int
		perror("open the FILE:");//perror函数直接打印出错信息；
	}
	fq = fopen("../hello.c","r");//打开一个存在的文件，
	if(NULL != fq)
	{
		printf("%d\n",errno);//errno，会保留上次信息；
		perror("open the FILE:");//perror函数直接打印出错信息；
	}
	return 0;
}

