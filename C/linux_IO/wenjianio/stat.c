#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc,char *argv[])
{
	struct stat buff;
	if(stat(argv[1],&buff) < 0)
	{
		perror("stat");
		return -1;
	}
	printf("st_mode = %d\n",buff.st_mode);
	if(S_ISREG(buff.st_mode))
	{
		printf("regular file\n");
	}
	if(S_ISDIR(buff.st_mode))
	{
		printf("directory file\n");
	}
	if(S_ISCHR(buff.st_mode))
	{
		printf("charater device file\n");
	}
	if(S_ISBLK(buff.st_mode))
	{
		printf("block device file\n");
	}
	if(S_ISDIR(buff.st_mode))
	{
		printf("directory file\n");
	}
	if(S_ISFIFO(buff.st_mode))
	{
		printf("fifo file\n");
	}
	if(S_ISLNK(buff.st_mode))
	{
		printf("symbolic file\n");
	}
	if(S_ISSOCK(buff.st_mode))
	{
		printf("cocket file\n");
	}
	if(buff.st_mode & S_IXOTH) 
	{
		printf("other user have executable permissons\n");
	}
	if(buff.st_mode & S_IWOTH) 
	{
		printf("other user have writable permissons\n");
	}
	if(buff.st_mode & S_IROTH) 
	{
		printf("other user have readable permissons\n");
	}
	if(buff.st_mode & S_IRWXO) 
	{
		printf("other user have execut permissons\n");
	}
	if(buff.st_mode & S_IXGRP) 
	{
		printf("group user have executable permissons\n");
	}
	if(buff.st_mode & S_IWOTH) 
	{
		printf("group user have writable permissons\n");
	}
	if(buff.st_mode & S_IROTH) 
	{
		printf("group user have readable permissons\n");
	}
	if(buff.st_mode & S_IXOTH) 
	{
		printf("other user have executable permissons\n");
	}
	printf("st_nlink = %d\n",buff.st_nlink);
	printf("st_uid = %d\n",buff.st_uid);
	printf("st_gid = %d\n",buff.st_gid);
	printf("st_rdev = %d\n",buff.st_rdev);
	printf("st_size = %d\n",buff.st_size);
	printf("st_blksize = %d\n",buff.st_blksize);
	printf("st_blocks = %d\n",buff.st_blocks);
	printf("st_atime = %s\n",ctime(&buff.st_atime));
	printf("st_mtime = %s\n",ctime(&buff.st_mtime));
	printf("st_ctime = %s\n",ctime(&buff.st_ctime));
	printf("%d\n",buff.st_dev);
	return 0;
}


