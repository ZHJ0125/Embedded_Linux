#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#define PUBLIC_FIFO "Server_FIFO"
#define PRIVATE_FIFO "Client_FIFO_"

struct FIFO_Data{
    int client_pid;
    char message[70];
};

char* Get_Private_FIFO_Name(int Client_PID);
void Send_and_Recive_Message(void);
char Private_Name[20];
char* Private_FIFO_Name;
int PublicFd, PrivateFd;
struct FIFO_Data Client_to_Server, Server_to_Client;

int main(){

    Client_to_Server.client_pid = getpid();
    strcpy(Client_to_Server.message, "00000\n");
    Private_FIFO_Name = Get_Private_FIFO_Name(getpid());
    printf("Client PID is: %d\nClient Message is: %s\n", Client_to_Server.client_pid, Client_to_Server.message);
    Send_and_Recive_Message();

    while(1){
        printf("Please input message: ");
        fgets(Client_to_Server.message, 60, stdin);
        Client_to_Server.client_pid = getpid();
        Send_and_Recive_Message();
    }
}

char* Get_Private_FIFO_Name(int Client_PID){
    char TempBuffer[6];
    strcpy(Private_Name, PRIVATE_FIFO);
    sprintf(TempBuffer, "%d", Client_PID);
    printf("TempBuffer is : %s\n", TempBuffer);
    strcat(Private_Name, TempBuffer);
    return Private_Name;
}

void Send_and_Recive_Message(void){
    if((PublicFd = open(PUBLIC_FIFO, O_WRONLY)) > 0){
        if(write(PublicFd, &Client_to_Server, sizeof(struct FIFO_Data)) > 0){
            //printf("Success to write client_%d message to server!\n", getpid());
            close(PublicFd);
        }
        else{
            printf("Fail to write client data\n");
        }
        usleep(200000);

        if(strcmp(Client_to_Server.message, "quit\n") == 0){
            printf("Client_%d exit\n", Client_to_Server.client_pid);
            printf("Removed %s\n", Private_FIFO_Name);
            exit(0);
        }

        if((PrivateFd = open(Private_FIFO_Name, O_RDONLY)) > 0){
            if(read(PrivateFd, &Server_to_Client, sizeof(struct FIFO_Data)) > 0){
                printf("Recive from Server: 👇\n%s\n", Server_to_Client.message);
                close(PrivateFd);
            }
        }
    }
    else{
        printf("Fail to open PUBLIC_FIFO\n");
        exit(1);
    }
}
