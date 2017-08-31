#include <stdio.h>

#include <unistd.h>

#include <string.h>

#include <errno.h>



int main(int argc,char *argv[],char *envp[])

{

	char *arg[]={"ls","-a",NULL};
	if(fork()==0)
	{
		printf("execl...........\n");
		if(execl("/bin/ls","ls","-a",NULL)<0)

		{

			fprintf(stderr,"execl failed:%s",strerror(errno));

			return -1;

		}
	}
	if(fork()==0)
	{
		printf("execv...........\n");
		if(execv("/bin/ls",arg)<0)
		{
			fprintf(stderr,"execl failed:%s\n",strerror(errno));
			return -1;
		}
	}
	if(fork()==0)
	{
		printf("execve...........\n");

		if(execve("/bin/ls",arg,envp)<0)
		{
			fprintf(stderr,"execl failed:%s\n",strerror(errno));
			return -1;
		}
	}
	return 0;
}



