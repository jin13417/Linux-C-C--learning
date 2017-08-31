#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define  N  64

void do_list(int connfd)
{
	DIR *mydir;
	struct dirent *ep;
	//char buf[N];

	mydir = opendir(".");
	while ((ep = readdir(mydir)) != NULL)
	{
		if (ep->d_name[0] == '.') continue;
		send(connfd, ep->d_name, N, 0);
	}
	closedir(mydir);

	return;
}

void do_get(int connfd, char *fname)
{
	int fd, nbyte;
	char buf[N];

	if ((fd = open(fname, O_RDONLY)) < 0)
	{
		perror("fail to open");
		buf[0] = 'N';
		send(connfd, buf, N, 0);
		return;
	}

	buf[0] = 'Y';
	send(connfd, buf, N, 0);
	while ((nbyte = read(fd, buf, N)) > 0)
	{
		send(connfd, buf, nbyte, 0);
	}
	close(fd);

	return;
}

void do_put()
{
	return;
}

int main(int argc, char *argv[])
{
	int listenfd, connfd;
	char command[N];
	struct sockaddr_in myaddr;

	//int socket(int domain, int type, int protocol);
	if ((listenfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}

	//int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
	bzero(&myaddr, sizeof(myaddr));
	myaddr.sin_family = PF_INET;
	myaddr.sin_port = htons(atoi(argv[2]));
	myaddr.sin_addr.s_addr = inet_addr(argv[1]);
	if (bind(listenfd, (SA *)&myaddr, sizeof(myaddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}

	listen(listenfd, 10);

	while ( 1 )
	{
		if ((connfd = accept(listenfd, NULL, NULL)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		recv(connfd, command, N, 0);  // recv command from client
		switch ( command[0] )
		{
		case 'L':
			printf("do_list\n");
			do_list(connfd);
			break;
		case 'G':
			printf("do_get\n");
			do_get(connfd, command+1);
			break;
		case 'P':
			do_put();
			break;
		}
		close(connfd);
	}

	return 0;
}
