//
//  main.cpp
//  TextClient
//
//  Created by programer on 2023/7/16.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>//POSIX線程控制
#include <sys/types.h> //size_t time_t
#include <sys/socket.h> //struct sockaddr
#include <netinet/in.h>//IPv4 struct sockaddr_in,htons
#include <arpa/inet.h> //將十進位IP轉換為整數 inet_addr

int main(int argc , char *argv[])
{

    //socket的建立
    int sockfd = 0;
    sockfd = socket(AF_INET , SOCK_STREAM , 0);

    if (sockfd == -1){
        printf("Fail to create a socket.");
    }

    //socket的連線

    struct sockaddr_in info; //IPv4地址和端口號的信息
    bzero(&info,sizeof(info));//將內存區清空
    info.sin_family = PF_INET;

    //localhost test
    info.sin_addr.s_addr = inet_addr("127.0.0.1");
    info.sin_port = htons(8000);

    //connect通常用於客戶端，用於連接到伺服器的套接字
    //info 服務器的地址信息，以建立與服務器的連接
    int err = connect(sockfd,(struct sockaddr *)&info,sizeof(info));
    if(err==-1){
        printf("Connection error");
        exit(0);
    }


    //Send a message to server
    char message[] = {"Hi there"};
    char receiveMessage[100] = {};
    for(int i=0;i<100;i++)
    {
        send(sockfd,message,sizeof(message),0);
        recv(sockfd,receiveMessage,sizeof(receiveMessage),0);
        
        printf("%s",receiveMessage);
        printf("close Socket\n");
    }
    close(sockfd);
    return 0;
}
