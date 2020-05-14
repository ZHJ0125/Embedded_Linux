#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define BUFSIZE 1024
#define SERVER_IP "192.168.86.129"
#define SERVER_PORT 6688

int main(int argc, char* argv[]){
    int fd,sfd;
    int res = 0;
    int datasize = 0;
    struct sockaddr_in svaddr = {0};
    char buf[BUFSIZE] = {0};

    if(argc != 2){
        printf("usage error!\n");
        exit(-1);
    }

    if((fd = open(argv[1], O_RDONLY)) == -1){
        perror("open()");
        exit(-1);
    }

    if((sfd = socket(AF_INET, SOCK_STREAM, 6)) == -1){
        close(fd);
        perror("socket()");
        exit(-1);
    }

    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(SERVER_PORT);
    svaddr.sin_addr.s_addr = inet_addr(SERVER_IP);

    if(connect(sfd, (struct sockaddr*)&svaddr, sizeof(svaddr)) == -1){
        close(fd);
        close(sfd);
        perror("connect()");
        exit(-1);
    }

    datasize = htonl(strlen(argv[1]));
    if(send(sfd, &datasize, sizeof(int), 0) == -1){
        close(fd);
        close(sfd);
        perror("send filename size");
        exit(-1);
    }

    if(send(sfd, argv[1], strlen(argv[1]), 0) == -1){
        close(fd);
        close(sfd);
        perror("send filename content");
        exit(-1);
    }

    while(1){
        res = read(fd, buf, BUFSIZE - 1);
        if(res == -1){
            close(fd);
            close(sfd);
            perror("read()");
            exit(-1);
        }
        else if(res == 0){
            printf("send file successful\n");
            break;
        }
        else{
            buf[res] = 0;
            datasize = htonl(res);
            if(send(sfd, &datasize, sizeof(int), 0) == -1){
                close(fd);
                close(sfd);
                perror("send file block data");
                exit(-1);
            }
            if(send(sfd, buf, strlen(buf), 0) == -1){
                close(fd);
                close(sfd);
                perror("send file block data");
                exit(-1);
            }
        }
    }

    close(fd);
    close(sfd);
    return 0;

}