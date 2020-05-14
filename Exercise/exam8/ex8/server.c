#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
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
    int res = 0;
    int fd = 0;
    int lfd = 0;
    int cfd = 0;
    char path[BUFSIZE] = {0};
    char buf[BUFSIZE] = {0};
    int datasize = 0;
    struct sockaddr_in svaddr = {0};
    struct sockaddr_in claddr = {0};
    socklen_t addrlen = sizeof(claddr);

    if((lfd = socket(AF_INET, SOCK_STREAM, 6)) == -1){
        perror("call socket() failed!");
        exit(-1);
    }

    svaddr.sin_family = AF_INET;
    svaddr.sin_port = htons(SERVER_PORT);
    svaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    if(bind(lfd, (struct sockaddr *)&svaddr, sizeof(svaddr)) == -1){
        close(lfd);
        perror("call listen() failed!");
        exit(-1);
    }

    if(listen(lfd, 10) == -1){
        close(lfd);
        perror("call listen() failed!");
        exit(-1);
    }

    while(1){
        if((cfd = accept(lfd, (struct sockaddr *)&claddr, &addrlen)) == -1){
            perror("call accept() failed!");
            break;
        }
        else{
            printf("receive file from: %s:%d\n", inet_ntoa(claddr.sin_addr), ntohs(claddr.sin_port));
        }

        if((res = recv(cfd, buf, sizeof(int), MSG_WAITALL)) == -1){
            close(cfd);
            perror("Receive filename length");
            continue;
        }
        else if(res == 0){
            printf("Connect close\n");
            continue;
        }
        else{
            buf[res] = 0;
            datasize = ntohl(*((int *)buf));
        }

        if((res = recv(cfd, buf, datasize, MSG_WAITALL)) == -1){
            close(cfd);
            perror("recive file name");
            continue;
        }
        else if(res == 0){
            printf("connect close\n");
            continue;
        }
        else{
            buf[res] = 0;
            while(res >= -1){
                if(buf[res] == '/'){
                    break;
                }
                else{
                    res --;
                }
            }
            strcpy(path, &buf[res + 1]);
            if((fd = open(path, O_RDWR|O_CREAT|O_EXCL, 0666)) == -1){
                close(cfd);
                perror("open()");
                continue;
            }
        }

        while(1){
            if((res = recv(cfd, buf, sizeof(int), MSG_WAITALL)) == -1){
                close(fd);
                close(fd);
                perror("recive file data");
                break;
            }
            else if(res == 0){
                printf("recive file successful: %s\n", path);
                break;
            }
            else{
                buf[res] = 0;
                datasize = ntohl(*((int *)buf));
            }

            if((res = recv(cfd, buf, datasize, MSG_WAITALL)) == -1){
                close(fd);
                close(fd);
                perror("recive file block data");
                break;
            }
            else if(res == 0){
                printf("connect close\n");
                break;
            }
            else{
                buf[res] = 0;
                if(write(fd, buf, strlen(buf)) == -1){
                    close(fd);
                    close(cfd);
                    perror("write()");
                    break;
                }
            }
        }

        close(fd);
        close(cfd);

    }

    close(fd);
    close(lfd);

    exit(0);
}