#include<stdio.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<string.h>
#include<strings.h>
#include<unistd.h>
#include<netinet/in.h>
#include<netdb.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

#define FTP_SERVER_IP "192.168.5.110"
#define FTP_SERVER_PORT 21
#define MAX_BUF_SIZE 1024

#define FTP_USERNAME                  "jsh"
#define FTP_USERPASSWD                "jsh"
#define FTP_COMMEND_USERNAME          "USER %s\r\n"
#define FTP_COMMEND_USERPASSWD        "PASS %s\r\n"
#define FTP_COMMEND_STOR              "STOR %s\r\n"
#define FTP_COMMEND_QUIT              "QUIT\r\n"
#define FTP_COMMEND_RESET             "REST 0\r\n"
#define FTP_COMMEND_TYPE              "TYPE I\r\n"
#define FTP_COMMEND_GET_FILE_SIZE "SIZE %s\r\n"
#define FTP_COMMEND_PASV "PASV\r\n"
#define FTP_PASV_PARSE_RESULTS "227 Entering Passive Mode (%d,%d,%d,%d,%d,%d)."
#define FTP_COMMEND_RETR "RETR %s\r\n"
#define FTP_START_RECV_DATA "125 Data connection already open; Transfer starting."

static int send_socket(int sockfd,const char *out_buf, int size)
{
    int count = 0;
    int ret = 0;
    int len = 0;

    if(!out_buf){
        return -1;
    }

    count = 0;
    len = (-1 == size) ? strlen(out_buf) : size;

    while (count < len){
        ret = write(sockfd, out_buf + count, len - count);
        if (ret <= 0){
            perror("write");
            return -1;
        }
        count += ret;
    }

    return 0;
}

static int read_socket(int sockfd, char * buf,int size)
{
    int len = 0;
    
    if(!buf){
        return -1;
    }

    memset(buf,0,size);
    len = read(sockfd, buf, size);
    if(len > 0){
//        printf("%s\n", buf);
    }

    return len;
}


static int connect_to_ftpserver(char *host,int port)
{
    struct sockaddr_in server;
    struct hostent *hp  = NULL;
    int sockfd = -1;
    char buf[MAX_BUF_SIZE] = {'\0'};


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd){
        perror("socket");
        return sockfd;
    }

    hp = gethostbyname(host);
    if (NULL == hp){
        perror("gethostbyname");
        return -1;
    }

    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons(port);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof (server)) < 0){
        perror("connect");
        return -1;
    }
    
    if(port == FTP_SERVER_PORT){
        read_socket(sockfd,buf,MAX_BUF_SIZE);

        if(strncmp(buf,"220",3) == 0){
            printf("###%s(),connect ftp server sucessful!\n",__func__);
        }else{
            close(sockfd);
            return -1;
        }
    }
    
    return sockfd;
}

static int  login(int sockfd)
{
    char sendbuf[MAX_BUF_SIZE] = {'\0'};
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    
    if(sockfd < 0){
        return ret;
    }

    sprintf(sendbuf,FTP_COMMEND_USERNAME,FTP_USERNAME);
    ret = send_socket(sockfd,sendbuf,strlen(sendbuf));
    if(ret == -1){
        printf("###%s(),send username failed!\n",__func__);
        return -1;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"331",3) == 0){
            printf("###%s(),send commend username sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend username failed!\n",__func__);
            return -1;
        } 
    }


    sprintf(sendbuf,FTP_COMMEND_USERPASSWD,FTP_USERPASSWD);
    ret = send_socket(sockfd,sendbuf,strlen(sendbuf));
    if(ret == -1){
        printf("###%s(),send userpasswd failed!\n",__func__);
        return -1;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"230",3) == 0){
            printf("###%s(),send commend userpasswd sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend userpasswd failed!\n",__func__);
            return -1;
        } 
    }

    return ret;
}

//reset
static void ftp_quit(int sockfd)
{
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    
    if(sockfd < 0){
        return;
    }

    ret = send_socket(sockfd,FTP_COMMEND_QUIT,strlen(FTP_COMMEND_QUIT));
    if(ret == -1){
        printf("###%s(),send ftp quit failed!\n",__func__);
        return ;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"221",3) == 0){
            printf("###%s(),send commend quit sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend quit failed:%s!\n",__func__,recvbuf);
            return ;
        } 
    }
}

//reset
static void ftp_reset(int sockfd)
{
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    
    if(sockfd < 0){
        return;
    }

    ret = send_socket(sockfd,FTP_COMMEND_RESET,strlen(FTP_COMMEND_RESET));
    if(ret == -1){
        printf("###%s(),send ftp reset failed!\n",__func__);
        return ;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"350",3) == 0){
            printf("###%s(),send commend reset sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend reset failed!\n",__func__);
            return ;
        } 
    }
}

//type user binary mode tran data
static void ftp_type(int sockfd)
{
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    
    if(sockfd < 0){
        return;
    }

    ret = send_socket(sockfd,FTP_COMMEND_TYPE,strlen(FTP_COMMEND_TYPE));
    if(ret == -1){
        printf("###%s(),send ftp type failed!\n",__func__);
        return ;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"200",3) == 0){
            printf("###%s(),send commend type sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend type failed!\n",__func__);
            return ;
        } 
    }
}

//type user binary mode tran data
static long long  ftp_get_file_size(int sockfd,char *filename)
{
    char sendbuf[MAX_BUF_SIZE] = {'\0'};
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    long long file_size = -1;
    
    if(sockfd < 0){
        return -1;
    }

    sprintf(sendbuf,FTP_COMMEND_GET_FILE_SIZE,filename);
    ret = send_socket(sockfd,sendbuf,strlen(sendbuf));
    if(ret == -1){
        printf("###%s(),send ftp type failed!\n",__func__);
        return -1;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"213",3) == 0){
            printf("###%s(),send commend type sucessful!\n",__func__);
            sscanf(recvbuf,"213 %lld",&file_size);
            return file_size;
        }
    }

    printf("###%s(),send commend type failed!\n",__func__);
    return -1;
}

//type user binary mode tran data
static int ftp_pasv(int sockfd)
{
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int result[6] = {'\0'};
    char ip[32] = {'\0'};
    int port = -1;
    int ret = -1;
    
    if(sockfd < 0){
        return -1;
    }

    ret = send_socket(sockfd,FTP_COMMEND_PASV,strlen(FTP_COMMEND_PASV));
    if(ret == -1){
        printf("###%s(),send ftp pasv failed!\n",__func__);
        return -1;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strncmp(recvbuf,"227",3) == 0){
            printf("###%s(),send commend pasv sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend pasv failed!\n",__func__);
            return -1;
        } 
    }

    sscanf(recvbuf,FTP_PASV_PARSE_RESULTS,&result[0],&result[1],&result[2],&result[3],&result[4],&result[5]);
    sprintf(ip,"%d.%d.%d.%d",result[0],result[1],result[2],result[3]);
    port = result[4] * 256 + result[5];
    printf("###%s(),ip:%s,port:%d\n",__func__,ip,port); 
    return connect_to_ftpserver(ip,port);

}


//type user binary mode tran data
static int ftp_retr(int sockfd,char *filename,int datasockfd)
{
    char sendbuf[MAX_BUF_SIZE] = {'\0'};
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    FILE *fp = NULL;
    long long file_size = -1;
    long long read_size = 0;

    if(sockfd < 0){
        return -1;
    }
    
    file_size = ftp_get_file_size(sockfd,filename);
    if(file_size == -1){
        printf("###%s(),ftp get file size failed!\n",__func__);
        return -1;
    }
    printf("###%s(),ftp get file size :%lld!\n",__func__,file_size);
    

    sprintf(sendbuf,FTP_COMMEND_RETR,filename);
    ret = send_socket(sockfd,sendbuf,strlen(sendbuf));
    if(ret == -1){
        printf("###%s(),send ftp retr failed!\n",__func__);
        return -1;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strstr(recvbuf,FTP_START_RECV_DATA)){
            printf("###%s(),send commend retr sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend retr failed!\n",__func__);
            return -1;
        } 
    }

    fp = fopen(filename,"w+");
    if(!fp){
        printf("###%s(),failed to open filename!\n",__func__);
        return -1;
    }

    while(read_size < file_size){    
        ret = read_socket(datasockfd,recvbuf,sizeof(recvbuf));
        if(ret > 0){
            fwrite(recvbuf,1,ret,fp);
            read_size += ret;
        }else{
            printf("###%s(),read file size failed:%lld\n",__func__,read_size);
            return -1;
        }
    }

    fclose(fp);
    return 0;
}

static int ftp_close_datasockfd(int sockfd,int datasockfd)
{
    char recvbuf[MAX_BUF_SIZE] = {'\0'};

    if(sockfd < 0 || datasockfd < 0){
        return -1;
    }

    close(datasockfd);
    read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(strncmp(recvbuf,"226",3) == 0){
        printf("###%s(),send commend 226 get file sucessful!\n",__func__);
        return 0;
    }

    printf("###%s(),send commend  get file failed!\n",__func__);
    return -1;

}

//get user passive mode
int ftp_get(char *filename)
{
    int sockfd = -1;
    int pasv_sockfd = -1;
    int ret = -1;

    sockfd = connect_to_ftpserver(FTP_SERVER_IP,FTP_SERVER_PORT);
    if(sockfd < 0){
        return -1;
    }

    login(sockfd);

    ftp_reset(sockfd);
    ftp_type(sockfd);
    pasv_sockfd = ftp_pasv(sockfd);
    if(pasv_sockfd < 0){
        printf("###%s(),ftp_pasv failed!\n");
    }
    
    ret = ftp_retr(sockfd,filename,pasv_sockfd);
    ftp_close_datasockfd(sockfd,pasv_sockfd); 
    ftp_quit(sockfd);

out:    
    close(sockfd);
}

//type user binary mode tran data
static int ftp_stor(int sockfd,char *filename,int datasockfd)
{
    char sendbuf[MAX_BUF_SIZE] = {'\0'};
    char recvbuf[MAX_BUF_SIZE] = {'\0'};
    int ret = -1;
    FILE *fp = NULL;;
    
    if(sockfd < 0){
        return -1;
    }

    sprintf(sendbuf,FTP_COMMEND_STOR,filename);
    ret = send_socket(sockfd,sendbuf,strlen(sendbuf));
    if(ret == -1){
        printf("###%s(),send ftp stor failed!\n",__func__);
        return -1;
    }

    ret = read_socket(sockfd,recvbuf,sizeof(recvbuf));
    if(ret > 0){
        if(strstr(recvbuf,FTP_START_RECV_DATA)){
            printf("###%s(),send commend stor sucessful!\n",__func__);
        }else{
            printf("###%s(),send commend stor failed! : %s\n",__func__,recvbuf);
            return -1;
        } 
    }

    fp = fopen(filename,"r");
    if(!fp){
        printf("###%s(),failed to open filename!\n",__func__);
        return -1;
    }

    while(!feof(fp)){
        memset(sendbuf,0,sizeof(sendbuf));
        ret = fread(sendbuf,1,sizeof(sendbuf),fp);
        if(ferror(fp)){
            printf("###%s(),failed to fread filename!\n",__func__);
            break;
        }
        
        send_socket(datasockfd,sendbuf,ret);
    }

    fclose(fp);
    return 0;
}


//put user passive mode
int ftp_put(char *filename)
{
    int sockfd = -1;
    int pasv_sockfd = -1;
    int ret = -1;

    sockfd = connect_to_ftpserver(FTP_SERVER_IP,FTP_SERVER_PORT);
    if(sockfd < 0){
        return -1;
    }

    login(sockfd);

    //ftp_reset(sockfd);
    ftp_type(sockfd);
    pasv_sockfd = ftp_pasv(sockfd);
    if(pasv_sockfd < 0){
        printf("###%s(),ftp_pasv failed!\n");
    }
    
    ret = ftp_stor(sockfd,filename,pasv_sockfd);
    ftp_close_datasockfd(sockfd,pasv_sockfd); 
    ftp_quit(sockfd);

    close(sockfd);
}


int main()
{
    //ftp_get("http.c");
    ftp_put("ftp.c");
    return 0;
}

