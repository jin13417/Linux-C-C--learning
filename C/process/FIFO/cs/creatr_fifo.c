#include <stdio.h>
#include<stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		fprintf(stdout, "usage: %s <filename>\n:",argv[0]);
		exit(-1);
	}

	if(mkfifo(argv[1],0644) < 0)
	{
		perror("mkfifo() fail");
      exit(-1);
	}

	return 0;
}
