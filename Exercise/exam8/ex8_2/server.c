#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>

#define LISTENQ 5
#define MAXLINE 512

int main(){
    int listenfd, connfd;
    socklen_t len;
    struct sockaddr_in servaddr, cliaddr;
    char buff[MAXLINE];
    time_t ticks;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if(listenfd < 0){
        printf("Socket created failed!\n");
        return -1;
    }
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(6667);
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0){
        printf("bind failed!\n");
        return -1;
    }
    printf("Listening...\n");
    listen(listenfd, LISTENQ);
    while(1){
        len = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
        printf("Connect from %s, port %d \n", inet_ntoa(cliaddr.sin_addr), ntohs(cliaddr.sin_port));
        ticks = time(NULL);
        sprintf(buff, "%s", ctime(&ticks));
        write(connfd, buff, strlen(buff));
        close(connfd);
    }
}