#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void my_func(int sign_no)
{
	if(sign_no == SIGINT)
		printf(" i have got SIGINT \n");
	else if(sign_no == SIGQUIT)
		printf("i have got SIGQUIT\n");
}

int main()
{
	printf("waiting for signal SIGINT or SIGQUIT\n");
		signal(SIGINT,my_func);
		signal(SIGQUIT,my_func);
	while(1)
	{
		pause();
	}
	exit(0);
}
