#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>


#define oops(s) {perror(s);exit(1);}

int main(int argc, char *argv[]){
    struct sockaddr_in saddr;
    int sock_id;
    int sock_rd;
    int n_read;
    char buf[BUFSIZ];

    /* socket */
    sock_id = socket(PF_INET, SOCK_STREAM, 0);
    if(sock_id == -1)
        oops("socket error");

    /* connect */
    bzero((void *)&saddr,sizeof(saddr));

    saddr.sin_addr.s_addr = inet_addr(argv[1]);
    saddr.sin_port = htons(atoi(argv[2]));
    saddr.sin_family = AF_INET;

    if(connect(sock_id, (struct sockaddr *)&saddr, sizeof(saddr)) ==-1)
            oops("connect error");
    
    /* read/write */
    if((n_read = read(sock_id, buf, BUFSIZ)) ==-1)
        oops("read error");
    if(write(1, buf, n_read) != n_read)
        oops("write error");

    close(sock_id);

}
