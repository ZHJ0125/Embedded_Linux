#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <signal.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
// #define SERVER_IP "127.0.0.1"		// 用于本地测试
#define SERVER_IP "47.95.13.239"	// 用于公网测试
#define SERVER_PORT 18888

int main(int argc, char *argv[]){
	int client_sockfd;
	int len;
	pid_t pid;
    char buf_recv[BUFSIZ];                                 	//数据传送的缓冲区
	char buf_send[BUFSIZ];
	struct sockaddr_in remote_addr;                         //服务器端网络地址结构体
	memset(&remote_addr, 0, sizeof(remote_addr));           //数据初始化--清零

	remote_addr.sin_family = AF_INET;                       //设置为IP通信
	remote_addr.sin_addr.s_addr = inet_addr(SERVER_IP);     //服务器IP地址
	remote_addr.sin_port = htons(SERVER_PORT);              //服务器端口号
	
	/*创建客户端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((client_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
		perror("socket error");
		return 1;
	}
	
	/*将套接字绑定到服务器的网络地址上*/
	if(connect(client_sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) < 0){
		perror("connect error");
		return 1;
	}
	printf("connected to server\n");
	len = recv(client_sockfd, buf_recv, BUFSIZ, 0);			//接收服务器端信息
    buf_recv[len] = '\0';
	printf("%s", buf_recv); //打印服务器端的欢迎信息
	printf("Enter string to send: \n");
	
	if((pid = fork()) < 0){
		printf("Fail to call fork()\n");
		return 1;
	}
	else if(pid > 0){
		// 父进程用来发送数据
		while(1){
			scanf("%s", buf_send);
			if(!strcmp(buf_send, "quit")){
				kill(pid, SIGSTOP);
				break;
			}
			len = send(client_sockfd, buf_send, strlen(buf_send), 0);
		}
	}
	else{
		// 子进程用来接收数据
		while(1){
			memset(buf_recv, 0, sizeof(buf_recv));
			len = recv(client_sockfd, buf_recv, BUFSIZ, 0);
			buf_recv[len] = '\0';
			printf("Recive from server: %s\n", buf_recv);
		}
	}

	/*关闭套接字*/
	close(client_sockfd);

	return 0;
}
