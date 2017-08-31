#include <stdio.h>
#include <time.h>
#include <unistd.h>
int main()
{
	char buf[256];
	int linecount = 0;


	FILE *fp = fopen("test.txt","a+");

	while(fgets(buf,sizeof(buf),fp) != NULL)
	{
		linecount++;
	}
	while(1)
	{
		time_t t = time(NULL);
		struct tm *time = localtime(&t) ;
		time -> tm_year += 1900;
		time -> tm_mon += 1;
		fprintf(fp,"%d, %d-%d-%d %d:%d:%d\n",linecount++,time -> tm_year,time -> tm_mon\
				,time -> tm_mday,time -> tm_hour,time -> tm_min,time -> tm_sec);
		fflush(fp);
		printf("%d, %d-%d-%d %d:%d:%d\n",linecount,time -> tm_year,time -> tm_mon\
				,time -> tm_mday,time -> tm_hour,time -> tm_min,time -> tm_sec);
		sleep(1);
	}
	fclose(fp);
	return 0;
}



