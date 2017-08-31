#include <stdio.h>

int main(int argc,char*argv[])
{
	chmod(argv[1],0777);
	return 0;
}
