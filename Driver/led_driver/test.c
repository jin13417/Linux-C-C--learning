#include <stdio.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include "led.h"

int main()
{
	int fd,j;
	unsigned long i;
	if(fd = open("/dev/led",O_RDWR) < 0)
	{
		perror("fail to open");
		exit(-1);
	}
while(1)
{
	/*
	for(i = 1;i < 4; i++)
	{
		ioctl(fd,LED_ON,i);
		usleep(30000);
		ioctl(fd,LED_OFF,i);
	}*/
	ioctl(fd,LED_ON,0);
	usleep(30000);
	ioctl(fd,LED_OFF,0);
}
	close(fd);


	return 0;
}





