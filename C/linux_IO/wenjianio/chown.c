#include <stdio.h>

int main(int argc,char *argv[])
{
	if(chown(argv[1],1021,1011)<0)
		printf("error\n");
	return 0;
}

	
