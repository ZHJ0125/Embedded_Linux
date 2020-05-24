#include <stdlib.h>
#include <sys/types.h>
#include <stdio.h>
#include <sys/socket.h>
#include <string.h>
#include <signal.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <pthread.h>
#define HANDSHARK_MSG "Hello,Client!\n"
#define SERVER_PORT 18888

void *fun_thrReceiveHandler(void *socketInfo);
void *fun_thrAcceptHandler(void *socketListen);
int checkThrIsKill(pthread_t thr);
int ReadToSend = 0;

typedef struct MySocketInfo{
    int socketCon;
    char *ipaddr;
    uint16_t port;
}_MySocketInfo;

// 客户端数组
struct MySocketInfo arrConSocket[10];
int conClientCount = 0;

// 接受客户端线程列表
pthread_t arrThrReceiveClient[10];
int thrReceiveClientCount = 0;
char buffer[BUFSIZ];

int main()
{
    printf("Start Server...\n");
    /* 创建TCP连接的Socket套接字 */
    int socketListen = socket(AF_INET, SOCK_STREAM, 0);
    if(socketListen < 0){
        printf("Fail to create Socket\n");
        exit(-1);
    }else{
        printf("Create Socket successful.\n");
    }

    /* 填充服务器端口地址信息，以便下面使用此地址和端口监听 */
    struct sockaddr_in server_addr;
    // bzero(&server_addr,sizeof(struct sockaddr_in));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY); /* 这里地址使用全0，即所有 */
    server_addr.sin_port = htons(SERVER_PORT);

    /*将套接字绑定到服务器的网络地址上*/
    if(bind(socketListen, (struct sockaddr *)&server_addr,sizeof(struct sockaddr)) != 0){
        perror("bind error");
		exit(-1);
    }else{
        printf("call bind() successful\n");
    }

    /* 开始监听相应的端口 */
    if(listen(socketListen, 10) != 0){
        perror("call listen()");
        exit(-1);
    }else{
        printf("call listen() successful\n");
    }

    /* 创建一个线程用来接收客户端的连接请求 */
    pthread_t thrAccept;
    pthread_create(&thrAccept, NULL, fun_thrAcceptHandler, &socketListen);

    /* 主线程用来向所有客户端循环发送数据 */
    while(1){
        if(ReadToSend){
            //判断线程存活多少
            int i;
            for(i = 0; i < thrReceiveClientCount; i++){
                if(checkThrIsKill(arrThrReceiveClient[i])){
                    printf("A Thread has been killed\n");
                    thrReceiveClientCount --;
                }
            }
            printf("Number of connected client: %d\n", thrReceiveClientCount);
            // 发送消息
            if(conClientCount <= 0){
                printf("No Clients!\n");
            }
            else{
                printf("conClientCount = %d\n", conClientCount);
                for(i = 0; i < conClientCount; i++){
                    printf("socketCon = %d\nbuffer is: %s\n", arrConSocket[i].socketCon, buffer);
                    int sendMsg_len = send(arrConSocket[i].socketCon, buffer, sizeof(buffer), 0);
                    // sendMsg_len = send(arrConSocket[i].socketCon, HANDSHARK_MSG, sizeof(HANDSHARK_MSG), 0);
                    // int sendMsg_len = write(arrConSocket[i].socketCon,HANDSHARK_MSG,30);
                    if(sendMsg_len > 0){
                        printf("向%s:%d发送成功\n", arrConSocket[i].ipaddr, arrConSocket[i].port);
                        ReadToSend = 0;
                    }else{
                        printf("向%s:%d发送失败\n", arrConSocket[i].ipaddr, arrConSocket[i].port);
                    }
                }
            }
        }
        sleep(0.5);
    }

    // 等待子进程退出
    printf("等待子线程退出，即将退出！\n");
    char *message;
    pthread_join(thrAccept,(void *)&message);
    printf("%s\n",message);

    return 0;
}

/* thrAccept线程一直循环接收来自客户端的连接请求 */
void *fun_thrAcceptHandler(void *socketListen){
    while(1){
        int sockaddr_in_size = sizeof(struct sockaddr_in);
        struct sockaddr_in client_addr;
        int _socketListen = *((int *)socketListen);

        // 连接相应的客户端
        int socketCon = accept(_socketListen, (struct sockaddr *)(&client_addr), (socklen_t *)(&sockaddr_in_size));
        if(socketCon < 0){
            printf("call accept()");
        }else{
            printf("Connected %s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
        }
        printf("Client socket: %d\n", socketCon);

        // 获取新客户端的网络信息
        _MySocketInfo socketInfo;
        socketInfo.socketCon = socketCon;
        socketInfo.ipaddr = inet_ntoa(client_addr.sin_addr);
        socketInfo.port = client_addr.sin_port;

        // 将新客户端的网络信息保存在arrConSocket数组中
        arrConSocket[conClientCount] = socketInfo;
        conClientCount++;
        printf("连接了%d个用户\n",conClientCount);

        // 为新连接的客户端开辟线程，该线程用来循环接收客户端的数据
        pthread_t thrReceive = 0;
        pthread_create(&thrReceive, NULL, fun_thrReceiveHandler, &socketInfo);
        arrThrReceiveClient[thrReceiveClientCount] = thrReceive;
        thrReceiveClientCount ++;
        printf("已为该用户创建一个线程\n");
 
        //让进程休息0.1秒
        usleep(100000);
    }
 
    char *s = "安全退出接受进程";
    pthread_exit(s);
}

/* 该线程函数用来循环接收客户端的数据 */
void *fun_thrReceiveHandler(void *socketInfo){
	int buffer_length;
    int con;
    int i;
	_MySocketInfo _socketInfo = *((_MySocketInfo *)socketInfo);
    send(_socketInfo.socketCon, HANDSHARK_MSG, sizeof(HANDSHARK_MSG), 0);

    while(1){
    	//添加对buffer清零
    	bzero(&buffer,sizeof(buffer));

        printf("正在读取客户端消息，客户端标识符%d\n", _socketInfo.socketCon);
        buffer_length = recv(_socketInfo.socketCon, buffer, BUFSIZ, 0);
        if(buffer_length == 0){
            printf("%s:%d Closed!\n", _socketInfo.ipaddr, _socketInfo.port);
            for(con = 0; con < conClientCount; con++){
                if(arrConSocket[con].socketCon == _socketInfo.socketCon){
                    break;  // 找到该客户端在数组中的位置
                }
            }
            // 将该客户端的信息删除，重置客户端数组
            for(i = con; i < conClientCount-1; i++){
                arrConSocket[i] = arrConSocket[i+1];
            }
            conClientCount --;
            break;
        }
        else if(buffer_length < 0){
            printf("Fail to call read()\n");
            break;
        }
        buffer[buffer_length] = '\0';
        printf("%s:%d said：%s\n", _socketInfo.ipaddr, _socketInfo.port, buffer);
        ReadToSend = 1;
        usleep(100000);
    }
    printf("%s:%d Exit\n", _socketInfo.ipaddr, _socketInfo.port);
    return NULL;
}
 
int checkThrIsKill(pthread_t thr){
    int res = 1;
    int res_kill = pthread_kill(thr, 0);
    if(res_kill == 0){
        res = 0;
    }
    return res;
}