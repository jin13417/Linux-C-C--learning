#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#define maxsize 5

int main(int argc,char *argv[])
{
	FILE *fp1,*fp2;
	char ch[maxsize];
	if(argc != 3)
	{
		printf("command error!\n");
		return -1;
	}
	if((fp1 = fopen(argv[1], "r")) == NULL)
	{
		printf("file %s cannot open ",argv[1]);
		return -1;
	}
	if((fp2 =  fopen(argv[2],"wb+"))== NULL)
	{
		printf("cannot create file %s",argv[1]);
		return -1;
	}
	while (fgets(ch,maxsize,fp1)!=NULL)
	{
		fputs(ch,fp2);
	}
	fclose(fp1);
	fclose(fp2);
	return 0;
}
