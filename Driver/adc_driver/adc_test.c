#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>



int main()
{
	int fd;
	fd = open("/dev/adc", O_RDWR, S_IRUSR | S_IWUSR);
	if(fd < 0)
	{
		perror("open");
		exit(1);
	}
	int key;
	while(1){
	read(fd, (char *)&key, sizeof(key));
	printf("V = %dmv\n", key);
	sleep(1);
	}
	close(fd);


}
