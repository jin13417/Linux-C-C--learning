#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>

#include "http.h"

#define BUFFER_SIZE 1024

typedef struct _http_tcpclient{ 
    int socket;
    int remote_port;     
    char remote_ip[16];  
    struct sockaddr_in _addr; 
    int connected;       
} http_tcpclient;

http_tcpclient pclient;

static int http_tcpclient_create(const char *host, int port){
    struct hostent *he;

    memset(&pclient,0,sizeof(http_tcpclient));

    if((he = gethostbyname(host))==NULL){
        return -2;
    }

    pclient.remote_port = port;
    strcpy(pclient.remote_ip,inet_ntoa( *((struct in_addr *)he->h_addr) ));

    pclient._addr.sin_family = AF_INET;
    pclient._addr.sin_port = htons(pclient.remote_port);
    pclient._addr.sin_addr = *((struct in_addr *)he->h_addr);

    if((pclient.socket = socket(AF_INET,SOCK_STREAM,0))==-1){
        return -3;
    }


    return 0;
}

static int http_parse_url(char *url,char *host,char *file,int *port)
{
    char *ptr1,*ptr2;
    int len = 0;
    if(!url || !host || !file || !port){
        return -1;
    }

    ptr1 = url;

    if(!strncmp(ptr1,"http://",strlen("http://"))){
        ptr1 += strlen("http://");
    }else{
        return -1;
    }

    ptr2 = strchr(ptr1,'/');
    if(ptr2){
        len = strlen(ptr1) - strlen(ptr2);
        memcpy(host,ptr1,len);
        host[len] = '\0';
        if(*(ptr2 + 1)){
            memcpy(file,ptr2 + 1,strlen(ptr2) - 1 );
            file[strlen(ptr2) - 1] = '\0';
        }
    }else{
        memcpy(host,ptr1,strlen(ptr1));
        host[strlen(ptr1)] = '\0';
    }
    //get host and ip
    ptr1 = strchr(host,':');
    if(ptr1){
        *ptr1++ = '\0';
        *port = atoi(ptr1);
    }else{
        *port = MY_HTTP_DEFAULT_PORT;
    }

    return 0;
}

static int http_tcpclient_conn(){
    if(pclient.connected)
        return 1;

    if(connect(pclient.socket, (struct sockaddr *)&pclient._addr,sizeof(struct sockaddr))==-1){
        return -1;
    }
    pclient.connected = 1;
    return 0;
}

static int http_tcpclient_recv(char *lpbuff){
    int recvnum = 0;

    recvnum = recv(pclient.socket, lpbuff,BUFFER_SIZE*4,0);

    return recvnum;
}

static int http_tcpclient_send(char *buff,int size){
    int sent=0,tmpres=0;

    while(sent < size){
        tmpres = send(pclient.socket,buff+sent,size-sent,0);
        if(tmpres == -1){
            return -1;
        }
        sent += tmpres;
    }
    return sent;
}

char * http_post(char *url,char *post_str){

    char post[BUFFER_SIZE] = {'\0'};
    char host[BUFFER_SIZE] = {'\0'};
    char content_len[BUFFER_SIZE] = {'\0'};

    char lpbuf[BUFFER_SIZE*4] = {'\0'};
    char *ptmp;
    char host_addr[BUFFER_SIZE] = {'\0'};
    char file[BUFFER_SIZE] = {'\0'};
    int port = 0;
    int len=0;
	char *response = NULL;

    if(!url || !post_str){
        return NULL;
    }

    if(http_parse_url(url,host_addr,file,&port)){
        printf("http_parse_url failed!\n");
        return NULL;
    }
    //printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);

    http_tcpclient_create(host_addr,port);

    const char *header2="User-Agent:Mozilla/4.0(compatible;MSIE 6.0;Windows NT 5.2;SV1;.NET CLR 1.1.4322;.NET CLR 2.0.50727)\r\nAccept: */*\r\n";

    sprintf(post,"POST /%s HTTP/1.1\r\n",file);
    sprintf(host,"HOST: %s:%d\r\n",pclient.remote_ip,pclient.remote_port);
    sprintf(content_len,"Content-Length: %d\r\n\r\n",strlen(post_str));

    strcpy(lpbuf,post);
    strcat(lpbuf,host);
    strcat(lpbuf,header2);
    strcat(lpbuf,content_len);
    strcat(lpbuf,post_str);


    if(!pclient.connected){
        http_tcpclient_conn();
    }

    if(http_tcpclient_send(lpbuf,strlen(lpbuf)) < 0){
        printf("http_tcpclient_send failed..\n");
        return NULL;
    }
	//printf("发送请求:\n%s\n",lpbuf);

    /*it's time to recv from server*/
    if(http_tcpclient_recv(lpbuf) <= 0){
        return NULL;
    }

    /*响应代码,|HTTP/1.0 200 OK|
     *从第10个字符开始,第3位
     * */
    memset(post,0,sizeof(post));
    strncpy(post,lpbuf+9,3);
    if(atoi(post)!=200){
        return NULL;
    }
    printf("接收响应:\n%s\n",lpbuf);

#if 0
    ptmp = (char*)strstr(lpbuf,"\r\n\r\n");
    if(ptmp == NULL){
        return NULL;
    }
    ptmp += 4;/*跳过\r\n*/

    len = strlen(ptmp)+1;
    response=(char*)malloc(len);
    if(response == NULL){
        return NULL;
    }
    memset(response,0,len);
    memcpy(response,ptmp,len-1);
#endif
    /*从头域找到内容长度,如果没有找到则不处理*/
    ptmp = (char*)strstr(lpbuf,"gth:");
    if(ptmp != NULL){
        len = atoi(ptmp+strlen("gth:"));
        printf("len = %d\n",len);
        ptmp = (char *)strstr(ptmp,"\n\n");
        response = ptmp;


    }

    http_tcpclient_close();

    return response;
}

char * http_get(char *url){

    char post[BUFFER_SIZE] = {'\0'};
    char host[BUFFER_SIZE] = {'\0'};
    char content_len[BUFFER_SIZE] = {'\0'};

    char lpbuf[BUFFER_SIZE*4] = {'\0'};
    char *ptmp;
    char host_addr[BUFFER_SIZE] = {'\0'};
    char file[BUFFER_SIZE] = {'\0'};
    int port = 0;
    int len=0;
	char *response = NULL;

    if(!url){
        return NULL;
    }

    if(http_parse_url(url,host_addr,file,&port)){
        printf("http_parse_url failed!\n");
        return NULL;
    }
   // printf("host_addr : %s\tfile:%s\t,%d\n",host_addr,file,port);

    http_tcpclient_create(host_addr,port);

    const char *header2="User-Agent:Mozilla/4.0(compatible;MSIE 6.0;Windows NT 5.2;SV1;.NET CLR 1.1.4322;.NET CLR 2.0.50727)\r\nAccept: */*\r\n";

    sprintf(post,"GET /%s HTTP/1.1\r\n",file);
    sprintf(host,"HOST: %s:%d\r\n\r\n",pclient.remote_ip,pclient.remote_port);

    strcpy(lpbuf,post);
    strcat(lpbuf,host);
    strcat(lpbuf,header2);
    strcat(lpbuf,content_len);


    if(!pclient.connected){
        http_tcpclient_conn();
    }

    if(http_tcpclient_send(lpbuf,strlen(lpbuf)) < 0){
        printf("http_tcpclient_send failed..\n");
        return NULL;
    }
//	printf("发送请求:\n%s\n",lpbuf);

    /*it's time to recv from server*/
    if(http_tcpclient_recv(lpbuf) <= 0){
        return NULL;
    }
    printf("接收响应:\n%s\n",lpbuf);

    /*响应代码,|HTTP/1.0 200 OK|
     *从第10个字符开始,第3位
     * */
    memset(post,0,sizeof(post));
    strncpy(post,lpbuf+9,3);
    if(atoi(post)!=200){
        return NULL;
    }


    ptmp = (char*)strstr(lpbuf,"\r\n\r\n");
    if(ptmp == NULL){
        return NULL;
    }
    ptmp += 4;/*跳过\r\n*/

    len = strlen(ptmp)+1;
    response=(char*)malloc(len);
    if(response == NULL){
        return NULL;
    }
    memset(response,0,len);
    memcpy(response,ptmp,len-1);

    /*从头域找到内容长度,如果没有找到则不处理*/
    ptmp = (char*)strstr(lpbuf,"gth:");
    if(ptmp != NULL){
        char *ptmp2;
        ptmp += 15;
        ptmp2 = (char*)strstr(ptmp,"\r\n");
        if(ptmp2 != NULL){
            memset(post,0,sizeof(post));
            strncpy(post,ptmp,ptmp2-ptmp);
            if(atoi(post)<len)
                (response)[atoi(post)] = '\0';
        }
    }

    http_tcpclient_close();

    return response;
}
int http_tcpclient_close(){
    close(pclient.socket);
    pclient.connected = 0;
}

int main()
{
    char *res = NULL;
    res = http_post("http://182.92.83.144:666/back.php","user=111&password=222");

    if(!res){
        printf("res is :%s\n",res);   
        free(res);
    }
    res = http_get("http://182.92.83.144:666/back.php?user=111&password=222");

    if(!res){
        printf("res is :%s\n",res);   
        free(res);
    }
	
}
