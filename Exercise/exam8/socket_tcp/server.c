#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#define SHAKEHAND_MSG "Welcome to my server\n"
#define SERVER_IP "101.200.50.245"
#define SERVER_PORT 8888

int main(int argc, char *argv[]){
    int len;
    int sin_size = sizeof(struct sockaddr_in);;
	char buf[BUFSIZ];                           //数据传送的缓冲区
	int server_sockfd;                          //服务端套接字
	int client_sockfd;                          //客户端套接字
	struct sockaddr_in my_addr;                 //服务器网络地址结构体
	struct sockaddr_in remote_addr;             //客户端网络地址结构体
	memset(&my_addr,0,sizeof(my_addr));         //数据初始化--清零

	my_addr.sin_family = AF_INET;               //设置为IP通信
	my_addr.sin_addr.s_addr = INADDR_ANY;       //服务器IP地址--允许连接到所有本地地址上
	my_addr.sin_port = htons(SERVER_PORT);      //服务器端口号(后台已开放8888和6666端口)

	/*创建服务器端套接字--IPv4协议，面向连接通信，TCP协议*/
	if((server_sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0){  
		perror("socket error");
		return 1;
	}

	/*将套接字绑定到服务器的网络地址上*/
	if(bind(server_sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) < 0){
		perror("bind error");
		return 1;
	}

	/*监听连接请求--监听队列长度为5*/
    printf("listening ...\n");
	if(listen(server_sockfd, 5) < 0){
		perror("listen error");
		return 1;
	}

	/*等待客户端连接请求到达*/
	if((client_sockfd = accept(server_sockfd, (struct sockaddr *)&remote_addr, &sin_size)) < 0){
		perror("accept error");
		return 1;
	}
	printf("accepted client %s\n", inet_ntoa(remote_addr.sin_addr));
	len = send(client_sockfd, SHAKEHAND_MSG, strlen(SHAKEHAND_MSG), 0); //发送欢迎信息
	
	/*接收客户端的数据并将其发送给客户端--recv返回接收到的字节数，send返回发送的字节数*/
	while((len = recv(client_sockfd, buf, BUFSIZ, 0)) > 0){
		buf[len] = '\0';
		printf("Recive from client: %s\n", buf);
		if(send(client_sockfd, buf, len, 0) < 0){   //将收到的数据发回到客户端
			perror("write error");
			return 1;
		}
	}

	/*关闭套接字*/
	close(client_sockfd);
	close(server_sockfd);

	return 0;
}
