#include<stdio.h>
#include<sys/types.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include<stdlib.h>

#include"led.h"


int main(void)
{
	int fd, i;
	fd = open("/dev/led", O_RDWR);
	if(fd < 0)
	{
		perror("open");
		exit(0);
	}
	while(1)
	{
		for(i = 0;i < 4;i++)
		{
			ioctl(fd, LED_ON, 1);
			usleep(30000);
			ioctl(fd, LED_ON, 2);
			usleep(30000);
			ioctl(fd, LED_ON, 3);
			usleep(30000);
			ioctl(fd, LED_ON, 0);
			usleep(30000);
			ioctl(fd, LED_OFF, 1);
			usleep(30000);
			ioctl(fd, LED_OFF, 2);
			usleep(30000);
			ioctl(fd, LED_OFF, 3);
			usleep(30000);
			ioctl(fd, LED_OFF, 0);
			usleep(30000);
		}
	}
	return 0;
}
