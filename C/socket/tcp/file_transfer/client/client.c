#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

typedef struct sockaddr SA;

#define  N  64

void do_help()
{
	printf("      help : display help info\n");
	printf("      quit : exit\n");
	printf("      list : get file list from server\n");
	printf("get <file> : download <file> from server\n");
	printf("put <file> : upload <file> to server\n");

	return;
}

void do_list(struct sockaddr_in servaddr)
{
	int sockfd;
	char buf[N];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}

	buf[0] = 'L';
	send(sockfd, buf, N, 0);  // send command to server
	while (recv(sockfd, buf, N, 0) > 0)
	{
		printf(" %s\n", buf);
	}
	close(sockfd);

	return;
}

void do_get(struct sockaddr_in servaddr, char *fname)
{
	int sockfd, nbyte, fd;
	char buf[N];

	if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	
	if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("fail to connect");
		exit(-1);
	}

	sprintf(buf, "G%s", fname);
	send(sockfd, buf, N, 0);
	recv(sockfd, buf, N, 0);  // recv reply from server
	if (buf[0] == 'N') 
	{
		printf("can't open %s on server", fname);
		close(sockfd);
		return;
	}
	if ((fd = open(fname, O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)
	{
		perror("fail to open");
		close(sockfd);
		return;
	}
	while ((nbyte = recv(sockfd, buf, N, 0)) > 0)
	{
		write(fd, buf, nbyte);
	}
	close(fd);
	close(sockfd);

	return;
}

void do_put()
{
	return;
}

int main(int argc, char *argv[])
{
	struct sockaddr_in servaddr;
	char command[N];

	if (argc < 3)
	{
		printf("Usage : %s <ip> <port>\n", argv[0]);
		return -1;
	}

/*
	//int socket(int domain, int type, int protocol);

*/
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = PF_INET;
	servaddr.sin_port = htons(atoi(argv[2]));
	servaddr.sin_addr.s_addr = inet_addr(argv[1]);

/*

*/

	while ( 1 )
	{
		printf("client > ");
		fgets(command, N, stdin);
		command[strlen(command)-1] = '\0';
		if (strncmp(command, "help", 5) == 0)
		{
			do_help();
		}
		else if (strncmp(command, "quit", 5) == 0)
		{
			printf("bye\n");
			exit(0);
		}
		else if (strncmp(command, "list", 5) == 0)
		{
			do_list(servaddr);
		}
		else if (strncmp(command, "get", 3) == 0)
		{
			do_get(servaddr, command+4);
		}
		else if (strncmp(command, "put", 3) == 0)
		{
			do_put();
		}
		else
		{
			printf("  wrong command : %s\n", command);
			do_help();
		}
	}

	return 0;
}
