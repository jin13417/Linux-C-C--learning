#include <stdio.h>

int main()
{
	int buf[20];
	FILE *fp =fopen("./hello.c","r"),
		 *fp1 = fopen("./b.txt","a+");
		fread(buf,sizeof(buf),2,fp);
		fwrite(buf,sizeof(buf),1,fp1);
		return 0;
}
