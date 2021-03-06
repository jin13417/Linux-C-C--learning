#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#define N 20
int main(int argc, char *argv[])
{
	int fd1, fd2, len, buff[N];

	if (argc != 3) {
		printf("error!");
		return -1;
	}

	if ((fd1 = open(argv[1], O_RDONLY)) < 0) {
		perror("open");
		return -1;
	}

	if ((fd2 =
	     open(argv[2], O_WRONLY | O_CREAT | O_EXCL | O_APPEND,
		  0644)) < 0) {
		perror("create ");
		return -1;
	}

	while ((len = read(fd1, buff, sizeof(buff))) > 0) {
		write(fd2, buff, len);
	}

	close(fd1);
	close(fd2);

	return 0;
}
