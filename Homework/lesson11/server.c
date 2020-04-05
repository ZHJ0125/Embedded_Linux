#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

#define PUBLIC_FIFO "Server_FIFO"
#define PRIVATE_FIFO "Client_FIFO_"

struct FIFO_Data{
    int client_pid;
    char message[100];
};

void Create_FIFO(char *FIFO_Name);
char* Get_Private_FIFO_Name(int Client_PID);
void sigcatch(int signum);
char Private_Name[20];

int main(){

    int Client_Num = 0;
    int PublicFd, PrivateFd;
    char* Private_FIFO_Name;
    struct FIFO_Data Client_to_Server, Server_to_Client;

    if(signal(SIGINT, &sigcatch) == SIG_ERR){
        printf("Couldn't register signal handler\n");
        exit(1);
    }

    Create_FIFO(PUBLIC_FIFO);

    while(1){
        if((PublicFd = open(PUBLIC_FIFO, O_RDONLY)) < 0){
            printf("Fail to open PUBLIC_FIFO\n");
            exit(1);
        }
        //printf("PUBLIC_FIFO has been opened\n");
    
        if(read(PublicFd, &Client_to_Server, sizeof(struct FIFO_Data)) > 0){
            
            printf("Client Pid is : %d\n", Client_to_Server.client_pid);
            printf("Client Message is : %s", Client_to_Server.message);
            Private_FIFO_Name = Get_Private_FIFO_Name(Client_to_Server.client_pid);
            
            if(strcmp(Client_to_Server.message, "00000\n") == 0){
                printf("Yes! You are a new client!\nClient Number: %d\n", Client_Num ++);
                Create_FIFO(Private_FIFO_Name);
            }
            
            if(strcmp(Client_to_Server.message, "quit\n") == 0){
                unlink(Private_FIFO_Name);
                printf("Closed Client_%d Private FIFO\n\n", Client_to_Server.client_pid);
            }
            else{
                if((PrivateFd = open(Private_FIFO_Name, O_WRONLY)) > 0){
                    Server_to_Client.client_pid = Client_to_Server.client_pid;
                    sprintf(Server_to_Client.message, "Hello,Client_%d!\nI Received your message: ", Client_to_Server.client_pid);
                    strcat(Server_to_Client.message, Client_to_Server.message);
                    if(write(PrivateFd, &Server_to_Client, sizeof(struct FIFO_Data))){
                        printf("Write message to Client Success!\n\n");
                        close(PrivateFd);
                    }
                }
            }
            
        }
        else{
            printf("Read Date error!\n");
            exit(1);
        }
    }
    
    return 0;
}

void Create_FIFO(char *FIFO_Name){
    int TempFd;
    if((TempFd = open(FIFO_Name, O_RDONLY)) == -1){
        umask(0);
        mknod(FIFO_Name, S_IFIFO|0666, 0);
        printf("%s has been bulid\n", FIFO_Name);
    }
    else{
        close(TempFd);
    }
}

char* Get_Private_FIFO_Name(int Client_PID){
    char TempBuffer[6];
    strcpy(Private_Name, PRIVATE_FIFO);
    sprintf(TempBuffer, "%d", Client_PID);
    //printf("TempBuffer is : %s\n", TempBuffer);
    strcat(Private_Name, TempBuffer);
    return Private_Name;
}

void sigcatch(int num){
    printf("\nServer is exiting...\n");
    unlink(PUBLIC_FIFO);
    printf("Removed %s\nSee you again 😉\n\n", PUBLIC_FIFO);
    exit(0);
}