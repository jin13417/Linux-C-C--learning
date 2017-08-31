#include <stdio.h>
#include <errno.h>
#include <string.h>
#define NAMESIZE 16
struct
{
	short count;
	long tatal;
	char name[NAMESIZE];
}item;
int main(int argc,char *argv[])
{
	FILE *fp = fopen("a.txt","a+");
	if(NULL == fp)
	{
		perror("fopen");
		return -1;
	}

	memset(&item,0,sizeof(item));
	item.count = 9;
	item.tatal = 74;
	strncpy(item.name,"rishard,stallman",NAMESIZE);
	if(fwrite(&item,sizeof(item),1,fp) !=1)
		perror("fwrite ");
	fclose(fp);
	return 0;
}
	
