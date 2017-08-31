#include <stdio.h>
#include <string.h>
#include <errno.h>
#define N 0
int main(int argc,char *argv[])
{

	FILE *fp;
   if(argc < 2)
   {
	   fprintf(stdout,"usage:%s filename\n",argv[0]);
	   return -1;
   }
   if((fp = fopen(argv[1],"r+")) == NULL)
   {
	   perror("fopen");
	   return -1;
   }
   printf("before freopen\n");
   freopen(argv[1],"w",stdout);//将 "after freopen"重定向到argv[1]所指向的文件中；
   printf("after freopen\n");//这句不会在屏幕上输出；
   freopen("/dev/tty","w",stdout);//将23行的输出到屏幕上；
   printf("end main\n");

#if N
	if(fp = fopen("./hello","r+") == NULL)
	{
		fprintf(stderr,"fopen()adadadadad %s\n",strerror(errno));
		return -1;
	}

	fclose(fp);
#endif
	return 0;
}

