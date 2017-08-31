#include <unistd.h>
#include <stdio.h>

int main()
{
	alarm(5);
	pause();

	puts("");
	return 0;
}
