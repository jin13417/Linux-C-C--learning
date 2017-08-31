#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sqlite3.h>
#include <signal.h>
#include <time.h>

#define BUFSIZE 256
#define NAMESIZE 16

typedef struct sockaddr SA;

typedef struct {
	char type;
	char name[NAMESIZE];
	char data[BUFSIZE];
}MSG;
char *errmsg;
MSG massage;


void do_insert(sqlite3 *db, int connectfd,MSG massage)
{
	char buf[BUFSIZE];
	sprintf(buf,"insert into user values ('%s','%s')",massage.name,massage.data);
	if(sqlite3_exec(db,buf,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("error: %s\n",errmsg);
		strcpy(massage.data,errmsg);
		send(connectfd,&massage,BUFSIZE,0);
		//exit(-1)

	}
	else
	{
		strcpy(massage.data,"Y");
		send(connectfd,&massage,BUFSIZE,0);
	}
}
void do_login(sqlite3 *db,int connectfd,MSG massage)
{
	char buf[BUFSIZE],**resultp;
	int nrow,ncolumn;

	sprintf(buf,"select * from user where name = '%s' and passwd = '%s'",massage.name,massage.data);
	if(sqlite3_get_table(db,buf,&resultp,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
	{
		printf("error: %s\n",errmsg);
		strcpy(massage.data,errmsg);
		send(connectfd,&massage,BUFSIZE,0);
		//exit(-1);
	}
	else
	{
		if(nrow == 0)
		{
			strcpy(massage.data,"N");
			send(connectfd,&massage,BUFSIZE,0);
		}
		else
		{
			strcpy(massage.data,"Y");
			send(connectfd,&massage,BUFSIZE,0);
		}
	}
}
void do_insertword(MSG massage,sqlite3 *db)
{
	time_t t;
	struct tm *tp;
	char tim[64];
	char buf[BUFSIZE];
	time(&t);
	tp = localtime(&t);
	sprintf(tim,"%d-%d-%d %d:%d:%d",tp -> tm_year +1990,tp -> tm_mon+1,
			tp -> tm_mday,tp -> tm_hour,tp -> tm_min,tp -> tm_sec); 
	sprintf(buf,"insert into history ('%s','%s','%s')",massage.name,tim,massage.data);
	if(sqlite3_exec(db,buf,NULL,NULL,&errmsg) != SQLITE_OK)
	{
		printf("error: %s\n",errmsg);
	}
}



void do_query(sqlite3 *db,int connectfd,MSG massage)
{
	FILE *fp;
	char line[BUFSIZE],*p;
	int n,len,flag = 0;
	if((fp = fopen("dict.txt","r")) == NULL)
	{
		perror("fail to fopen");
		return;
	}
	len = sizeof(massage.data);
	while(fgets(line,BUFSIZE,fp) != NULL)
	{
		n = strncmp(line,massage.data,len);
		if((n == 0)&&(line[len] == ' '))
		{
			flag = 1;
	puts("a");
			p = line+len;
			while(*p == ' ')p++;
			strcpy(massage.data,p);
			do_insertword(massage,db);
			break;
		}
		else
			continue;
	}
	if(!flag) 
		strcpy(massage.data,"have not this words");
	send(connectfd,&massage,BUFSIZE,0);
}
void do_history(sqlite3 *db,int connectfd,MSG massage)
{
	int nrow,i,j,ncolumn,index;
	char **resultp;
	if(sqlite3_get_table(db,"select *from history",&resultp,&nrow,&ncolumn,&errmsg) != SQLITE_OK)
	{
		printf("error: %s\n",errmsg);
		return;
	}
	index = ncolumn;
	for(i=0;i<nrow;i++)
		for(j=0;j<ncolumn;j+3)
		{
			sprintf(massage.data,"%s:%s|%s:%s|%s:%s|",resultp[j],resultp[index++],resultp[j+1],
					resultp[index++],resultp[j+2],resultp[index++]);
			send(connectfd,&massage,BUFSIZE,0);
		}
}


int main(int argc,char *argv[])
{
	struct sockaddr_in serveraddr,clientaddr;
	int socketfd,clientlen,connectfd;
	char buf[BUFSIZE];
	sqlite3 *db;
	if(argc <3)
	{
		printf("Usage %s <IP><port>\n",argv[0]);
		exit(-1);
	}

	if((socketfd = socket(PF_INET,SOCK_STREAM,0)) < 0)
	{
		perror("fail to socket");
		exit(-1);
	}
	//填充服务器地址：
	bzero(&serveraddr,sizeof(serveraddr));
	serveraddr.sin_family = PF_INET;
	serveraddr.sin_port = htons(atoi(argv[2]));
	serveraddr.sin_addr.s_addr = inet_addr(argv[1]);
	//绑定服务器
	if(bind(socketfd,(SA *)&serveraddr,sizeof(serveraddr)) < 0)
	{
		perror("fail to bind");
		exit(-1);
	}
	//监听模式
	listen(socketfd,10);
	clientlen = sizeof(clientaddr);
	if(sqlite3_open("online_English_dictionary.db",&db) != SQLITE_OK)
	{
		printf("error open: %s\n",sqlite3_errmsg(db));
		exit(-1);
	}
	signal(SIGCHLD,SIG_IGN);
	while(1)
	{
		if((connectfd = accept(socketfd,(SA*)&clientaddr,&clientlen)) < 0)
		{
			perror("fail to accept");
			exit(-1);
		}
		if(fork() == 0)
		{
			while(1)
			{

				if(recv(connectfd,&massage,BUFSIZE,0) < 0)
				{
					perror("fail to recv");
					continue;
				}
				switch (massage.type)
				{
				case 'R':
					do_insert(db,connectfd,massage);  break;
				case 'L':
					do_login(db,connectfd,massage);   break;
				case 'Q':
					do_query(db,connectfd,massage);   break;
				case 'H':
					do_history(db,connectfd,massage);   break;
				}

			}

		}
		close(connectfd);
	}
	return 0;
}








