#include <stdio.h>
#include <time.h>

void init_daemon();

int main()
{
	FILE *fp;
	time_t t;
	init_daemon();
	while(1)
	{
		sleep(2);
		if((fp = fopen("test.txt","a")) != NULL)
		{
			t= time(0);
			fprintf(fp,"i an here at %s\n",asctime(localtime(&t)));
			fclose(fp);
		}
	}
	return 0;
}
