#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>

#define MAXLINE 1024

/*unbuffer input/output function*/

ssize_t rio_readn(int fd,void *usrbuf,size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0){
        if((nread = read(fd,bufp,nleft)) < 0){
            if(errno == EINTR){/*interrupted by sig handler return*/
                nread = 0;
            }else{
                return -1;/*error*/
            }
        }else if(nread == 0){
            break;  /*EOF*/
        }else{/*read content*/
            nleft -= nread;
            bufp += nread;
        }
    }
    return (n - nleft);
}

ssize_t rio_writen(int fd,void *usrbuf,size_t n)
{
    size_t nleft = n;
    ssize_t nwritten;
    char *bufp = usrbuf;

    while(nwritten = write(fd,bufp,nleft) <= 0){
        if(errno == EINTR){
            nwritten = 0;
        }else{
            return -1;
        }
        nleft -= nwritten;
        bufp += nwritten;
    }
    return n;
}
/******************************************************************************/
#define RIO_BUFSIZE 8192
typedef struct{
    int rio_fd; /*To operate the file descriptor*/
    int rio_cnt;/*unread bytes in internal buf*/
    char *rio_bufptr;/*next unread byte int internal buf*/
    char rio_buf[RIO_BUFSIZE];/*internal buf*/
}rio_t;
void rio_readinitb(rio_t *rp,int fd)
{
    rp->rio_fd = fd;
    rp->rio_cnt = 0;
    rp->rio_bufptr = rp->rio_buf;
}
static ssize_t rio_read(rio_t *rp,char *usrbuf,size_t n)
{
    int cnt;
    while(rp->rio_cnt <= 0){/*Read the file content if buf is empty*/
        rp->rio_cnt = read(rp->rio_fd, rp->rio_buf,sizeof(rp->rio_buf));
        if(rp->rio_cnt < 0){
            if(errno != EINTR){
                return -1;
            }
        }else if(rp->rio_cnt == 0){/*EOF*/
            return 0;
        }else {/*reset buf ptr*/
            rp->rio_bufptr = rp->rio_buf;
        }
    }
    /*when n < rp->rio_cnt, need copy some times */
    cnt = n;
    if(rp->rio_cnt < n){/*one time copy end*/
        cnt = rp->rio_cnt;
    }
    memcpy(usrbuf,rp->rio_bufptr,cnt);
    rp->rio_bufptr += cnt;
    rp->rio_cnt -= cnt;
    return cnt;
}
ssize_t rio_readlineb(rio_t *rp, void *usrbuf,size_t maxlen)
{
    int n,rc;
    char c,*bufp = usrbuf;
    for(n = 1; n < maxlen; n++){
        if (( rc = rio_read(rp,&c,1)) == 1){
            *bufp++ = c;
            if(c == '\n'){
                break;
            }
        }else if (rc == 0){
            if(n == 1){/*EOF no data read*/
                return 0;
            }else{/*EOF some data read*/
                break;
            }
        }else{/*ERROR*/
            return -1;
        }
    }
    *bufp = 0;/*string end sign :'\0'*/
    return n;
}

ssize_t rio_readnb(rio_t *rp,void *usrbuf,size_t n)
{
    size_t nleft = n;
    ssize_t nread;
    char *bufp = usrbuf;

    while(nleft > 0){
        if((nread = rio_read(rp,bufp, nleft)) < 0){
            if(errno == EINTR){/*interrupted by sig handler return*/
                nread =0;
            }else{/*errno set by read() */
                return -1;
            }
        }else if(nread == 0){/*EOF*/
            break;
        }
        nleft -= nread;
        bufp += nread;
    }
    return (n-nleft);/*return >=0*/
}

int main()
{
    int n;
    rio_t rio;
    char buf[MAXLINE];

    int fd = open("1.txt",O_RDONLY,755);
    if(fd <=0){
        printf("error\n");
    }
    rio_readinitb(&rio,fd);
    while ((n = rio_readlineb(&rio,buf,MAXLINE)) != 0){
           rio_writen(1,buf,n);
    }
    close(fd);
    return 0;
}
