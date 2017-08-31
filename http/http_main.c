#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
#include <pthread.h>

#include "http.h"


void * pthread_fuc(void * data)
{
    char *res = NULL;
    res = http_post("http://123.57.135.235:666/back.php","user=111&password=222");

    if(res){
        printf("res is :%s\n",res);   
        free(res);
    }
    res = http_get("http://123.57.135.235:666/back.php?user=111&password=222");

    if(res){
        printf("res is :%s\n",res);   
        free(res);
    }
	
}

int main()
{
    pthread_t th;

    int i;

    for(i = 0; i < 10;i++){
        pthread_create(&th,0,pthread_fuc,NULL);
        pthread_detach(th);
    }

    getchar();
    
    return 0;

}
