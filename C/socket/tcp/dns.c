#include <stdio.h>
#include <netdb.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(int argc,char *argv[])
{
	struct hostent *p;
	struct sockaddr_in addr;
	if(argc < 2)
	{
		printf("Usage:%s <name>\n",argv[0]);
		exit(-1);
	}
	p = gethostbyname(argv[1]);
	printf("h_name : %s\n",p -> h_name);
	memcpy(&addr.sin_addr,p -> h_addr,p->h_length);//内存拷贝
	printf("%s\n",inet_ntoa(addr.sin_addr));

	return 0;
}
