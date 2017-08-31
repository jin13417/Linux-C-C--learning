
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
	int fd,i,j;
	struct led_buf{
		int no;
		int led_no;
	};
	struct led_buf *p;

	if(fd = open("/dev/led",O_RDWR) < 0)
	{
		perror("fail to open");
		exit(-1);
	}
	printf("\n/dev/led opened fd = %d \n",fd);

while(1)
{
  for(i=0;i<4;i++)
  {
	p -> no = 1;
	p -> led_no = i;
	if (write(fd,p,sizeof(p)) < 0)
		perror ("fail to write");
	else
		printf("led(%d) is ON\n",i);
	sleep(1);
	p -> no = 0;
	if (write(fd,p,sizeof(p)) < 0)
		perror ("fail to write");
	else
		printf("led(%d) is ON\n",i);
     sleep(1);
  }
}
	close(fd);


	return 0;
}





