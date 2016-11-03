#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
#include <netinet/in.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>

#define PORTNUM 14000

#define oops(s) {perror(s);exit(1);}

int main(int argc,char *argv[]){
    struct sockaddr_in saddr;
    int sock_id;
    int sock_fd;
    FILE *sock_fp;
    time_t thetime;
    char *myaddr = "115.28.53.241";

    /* socket */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id == -1)
        oops("socket error");
    
    /* bind */
    bzero((void *)&saddr, sizeof(saddr));

    saddr.sin_addr.s_addr = inet_addr(myaddr);
    saddr.sin_port = htons(PORTNUM);
    saddr.sin_family = AF_INET;

    if(bind(sock_id, (struct sockaddr *)&saddr, sizeof(saddr))==-1)
        oops("bind error");

    /*listen*/
    if(listen(sock_id, 1) == -1)
        oops("listen error");

    /* main loop */
    while(1){
        sock_fd = accept(sock_id, NULL, NULL);
        printf("\n");
        if(sock_fd == -1)
            oops("accept error");
        sock_fp = fdopen(sock_fd, "w");
        if(sock_fp == NULL)
            oops("error");

        thetime = time(NULL);

        fprintf(sock_fp, "The time is .. ");
        fprintf(sock_fp, "%s\n", ctime(&thetime));

        fclose(sock_fp);
        
    }


}
