#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	pid_t pid;

	pid = fork();

	if(pid <0){
		perror("fork error");
		exit(1);
	}
	else
		if(pid == 0)
		{
			printf("hello wi aididaidi");
				exit(1);//刷新缓存区，会将缓存区内容打印出来；然后结束子程序。
			printf("adad ad a");
		}
	else
	{

		printf("adadadadad\n");
			printf("adada ad");
			_exit(1);//不刷新缓存区，直接结束；
	}
	return 0;
}
