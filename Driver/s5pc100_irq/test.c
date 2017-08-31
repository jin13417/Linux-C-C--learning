#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>


int fd, oflags;

void input_handler(int signum)
{
	int key;
	read(fd, (char *)&key, sizeof(key));
	printf("key = %d\n", key);
}

int main()
{
	fd = open("/dev/irq", O_RDWR, S_IRUSR | S_IWUSR);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}

	signal(SIGIO, input_handler); 
	fcntl(fd, F_SETOWN, getpid());
	oflags = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, oflags | FASYNC);

	while(1)
	{
		sleep(100);
	}
}
