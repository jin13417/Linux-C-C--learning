#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <fcntl.h>
//#include <sys/exits.h>

int global = 22;
char buf[] = "the test content!\n";

int main()
{
	int test = 0 ,stat;
	pid_t pid;
	if (write(STDOUT_FILENO,buf,sizeof(buf)) !=sizeof(buf))
	{
		perror("write error\n");
	}
	printf("fock test!\n");
	pid = fork();
	if(pid == -1)
		exit(0);
	else if (pid == 0)
	{
		int i = 1;
		while (i);
		global++;
		test++;
		printf("global=%d test = %d child,my pid is %d,ppid=%d\n",global,test,getpid(),getppid());
	}
	else
	{
	global+=2;
	test +=2;
	printf("global=%d test = %d parent,my pid is %d,ppid = %d\n",global,test,getpid(),getppid());
	}
	return 0;
}
