#include <stdio.h>
#include <unistd.h>

int main()
{
	char* a[]={"ps", "-ef" ,NULL};
	if(execvp("ps",a) == -1)
		perror("execvp");
	return 0;
}

