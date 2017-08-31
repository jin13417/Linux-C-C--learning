#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define HELO "HELO %s\r\n"
#define MAIL_FORM "MAIL FROM <%s>\r\n"
#define MAIL_TO "RCPT TO <%s>\r\n"
#define SUBJECT "SUBJECT:%s\r\nMIME-VERSION: 1.0\r\nCONTENT-TYPE: MULTIPART/MIXED;BOUNDARY=\"#BOUNDARY#\"\r\n\r\n"
#define CONTENT "--#BOUNDARY#\r\nCONTENT-TYPE: TEXT/HTML\r\n\r\n%s\r\n\r\n"
#define ATTACHMENT "--#BOUNDARY#\r\nCONTENT-TYPE:APPLICATION/MSWORD; NAME=%s\r\nCONTENT-DISPOSITION: ATTACHMENT; FILENAME=%s\r\nCONTENT-TRANSFER-ENCODING:BASE64\r\n\r\n"
#define DATA "DATA\r\n"
#define QUIT "QUIT\r\n"

#define MAIL_MAX_BUF_SIZE 4096
#define MAIL_MAX_ENCODE_BUF_SIZE (((MAIL_MAX_BUF_SIZE + 2) / 3) * 4 + 1)

#define MAIL_SERVER_ADDRESS "smtp.163.com"
#define MAIL_SERVER_PORT    25

#define MAIL_NAME "freeswitch123@163.com"
#define MAIL_PASSWORD "asd123"


static int send_socket(int sockfd,const char *out_buf, int size)
{
    int count = 0;
    int ret = 0;
    int len = 0;

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

static void read_socket(int sockfd)
{
    int len = 0;
    char buf[BUFSIZ + 1] = "\0";

    len = read(sockfd, buf, BUFSIZ);
    buf[len] = '\0';
    printf("%s\n", buf);
}


static int base64_encode(const char *in, int ilen, char *out, int olen)
{
    int convlen = 0;
    const char base64tab[65] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    convlen = ((ilen + 2) / 3) * 4;
    if (convlen >= olen)
    {
        printf("outlen should be ((%d+2)/3)*4+1=%d,but it is %d\n", ilen, convlen + 1, olen);
        return -1;
    }

    /** we don't need to check olen anymore */
    while (ilen >= 3)
    {
        out[0] = base64tab[(((unsigned char)in[0]) >> 2)];
        out[1] = base64tab[(((unsigned char)in[0] & 0x03) << 4) | (((unsigned char)in[1]) >> 4)];
        out[2] = base64tab[(((unsigned char)in[1] & 0x0F) << 2) | (((unsigned char)in[2]) >> 6)];
        out[3] = base64tab[(((unsigned char)in[2] & 0x3F))];
        out += 4;
        in += 3;
        ilen -= 3;
    }

    if (!ilen)
    {
        out[0] = '\0';
    } else
    {
        out[0] = base64tab[((unsigned char)in[0]) >> 2];
        if (ilen == 1)
        {
            out[1] = base64tab[((unsigned char)in[0] & 0x03) << 4];
            out[2] = '=';
        } else
        {
            out[1] = base64tab[(((unsigned char)in[0] & 0x03) << 4) |
                (((unsigned char)in[1]) >> 4)];
            out[2] = base64tab[((unsigned char)in[1] & 0x0F) << 2];
        }
        out[3] = '=';
        out[4] = '\0';
    }

    return convlen;
}

static int connect_MailServer()
{
    struct sockaddr_in server;
    struct hostent *hp  = NULL;
    int sockfd = -1;


    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (-1 == sockfd){
        perror("socket");
        return sockfd;
    }

    hp = gethostbyname(MAIL_SERVER_ADDRESS);
    if (NULL == hp){
        perror("gethostbyname");
        return -1;
    }

    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    memcpy((char *)&server.sin_addr, (char *)hp->h_addr, hp->h_length);
    server.sin_port = htons(MAIL_SERVER_PORT);

    if (connect(sockfd, (struct sockaddr *)&server, sizeof (server)) < 0){
        perror("connect");
        return -1;
    }

    read_socket(sockfd);

    return sockfd;
}

int sendmail(const char* mailto,const char *subject,const char* content,const char *attachmentPath)
{
    int sockfd = -1;
    char buf[MAIL_MAX_BUF_SIZE] = {'\0'};
    char encode_buf[MAIL_MAX_ENCODE_BUF_SIZE] = {'\0'};
    FILE *fp = NULL;

    sockfd = connect_MailServer();
    if(sockfd == -1){
        printf("failed to connect_MailServer\n");
        return -1;
    }
    
    //login email
    memset(buf,0,sizeof(buf));
    sprintf(buf,HELO,MAIL_NAME);
    send_socket(sockfd,buf,strlen(buf));
    read_socket(sockfd);

    memset(buf,0,sizeof(buf));
    sprintf(buf,"AUTH LOGIN\r\n");
    send_socket(sockfd,buf,strlen(buf));
    read_socket(sockfd);

    //username
    memset(encode_buf,0,sizeof(encode_buf));
    base64_encode(MAIL_NAME, strlen(MAIL_NAME), encode_buf, sizeof(encode_buf));
    memset(buf,0,sizeof(buf));
    sprintf(buf,"%s\r\n",encode_buf);
    send_socket(sockfd,buf,strlen(buf));
    read_socket(sockfd);

    //password
    memset(encode_buf,0,sizeof(encode_buf));
    base64_encode(MAIL_PASSWORD, strlen(MAIL_PASSWORD), encode_buf, sizeof(encode_buf));
    memset(buf,0,sizeof(buf));
    sprintf(buf,"%s\r\n",encode_buf);
    send_socket(sockfd,buf,strlen(buf));
    read_socket(sockfd);


    //mail head
    memset(buf,0,sizeof(buf));
    sprintf(buf,MAIL_FORM,MAIL_NAME);
    send_socket(sockfd,buf,strlen(buf));
    read_socket(sockfd);

    memset(buf,0,sizeof(buf));
    sprintf(buf,MAIL_TO,mailto);
    send_socket(sockfd,buf,strlen(buf));
    read_socket(sockfd);

    //mail info
    send_socket(sockfd,DATA,strlen(DATA));
    read_socket(sockfd);

    //send subject
    memset(buf,0,sizeof(buf));
    sprintf(buf,SUBJECT,subject);
    send_socket(sockfd,buf,strlen(buf));

    //send Content
    memset(buf,0,sizeof(buf));
    sprintf(buf,CONTENT,content);
    send_socket(sockfd,buf,strlen(buf));
   //send attachment

    memset(buf,0,sizeof(buf));
    sprintf(buf,ATTACHMENT,attachmentPath,attachmentPath);
    send_socket(sockfd,buf,strlen(buf));


    fp = fopen(attachmentPath, "rb");
    if (NULL == fp)
    {
        perror("fopen");
        return -1;
    }

    fseek(fp, 0L, SEEK_END);
    int length = ftell(fp);
    fseek(fp, 0L, SEEK_SET);

    int count = 0L;
    int ret = 0;
    int tmp_ret;
    while (count < length)
    {
        ret = fread(buf, 1, MAIL_MAX_BUF_SIZE, fp);
        tmp_ret = base64_encode(buf, ret, encode_buf, MAIL_MAX_ENCODE_BUF_SIZE);
        if (-1 == tmp_ret)
        {
            perror("base64_encode");
            return -1;
        }
        send_socket(sockfd,encode_buf, tmp_ret);
        count += ret;
    }
    fclose(fp);
    send_socket(sockfd,"\r\n.\r\n", -1);
    read_socket(sockfd);
    send_socket(sockfd,QUIT,sizeof(QUIT));
    read_socket(sockfd);

    close(sockfd);
    return 0;
}

int main()
{
   sendmail("413977243@qq.com","1111","22222222222","mail.h");

}

