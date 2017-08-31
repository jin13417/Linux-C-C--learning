#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

int main()
{
	int fd = open("1.txt",O_PDWR | O_CREAT | O_EXCL, 0777);
	printf("%d\n",umask(0111));

	 fd = open("2.txt",O_PDWR | O_CREAT | O_EXCL, 0777);
	printf("%d\n",umask(0111));

	 fd = open("3.txt",O_PDWR | O_CREAT | O_EXCL, 0777);
	printf("%d\n",umask(0111));

	fd = open("4.txt",O_PDWR | O_CREAT | O_EXCL, 0777);
	printf("%d\n",umask(0111));
