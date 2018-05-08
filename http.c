#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>




int main(int argc,char* argv[]){
    if(argc != 3){
        printf("usage:%d [ip] [port]\n");
        return 1;
    }
    int sock = socket(AF_INET,SOCK_STREAM,0);
    if(sock < 0){
        perror("socket");
        return 2;
    }
    struct sockaddr_in local;
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[2]));//将整型由本地转向网络：htons
    local.sin_addr.s_addr = inet_addr(argv[1]);//将字符串由本地转向网络：inet_addr
    //绑定
    int ret = bind(sock,(struct sockaddr*)&local,sizeof(local));
    if(ret < 0){
        perror("bind");
        return 3;
    }
    //监听
    ret = listen(sock,5);
    if(ret < 0){
        //监听失败
        perror("listen");
        return 4;
    }
    printf("bind and listen success!\n");
    for(;;){
        struct sockaddr_in client_socket;
        socklen_t len;
        int client_sock = accept(sock,(struct sockaddr*)&client_socket,&len);
        if(client_sock<0){
            perror("accept");
            continue;
        }
        char input_buf[10240]={0};
        ssize_t read_size = read(client_sock,input_buf,sizeof(input_buf)-1);
        if(read_size<0){
            return 6;
        }
        printf("[Request]%s",input_buf);
        char buf[1024] = {0};
        const char*hello = "<h1>8b305say:hello world<h1>";
        sprintf(buf,"HTTP/1.0 200 OK\nContent-Length:%lu\n\n%s",strlen(hello),hello);
        write(client_sock,buf,sizeof(buf));
    }
    return 0;
}
