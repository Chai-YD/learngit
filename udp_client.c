#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<string.h>


int main(int argc,char* argv[]){
	if(argc!=3){
		printf("usage:%s [ip] [port]\n",argv[0]);
		return 2;
	}
	//创建套接字
	int sock = socket(AF_INET,SOCK_DGRAM,0);
	if(sock<0){
		perror("socket");
		return 2;
	}
	//创建struct sockaddr结构体
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_addr.s_addr = inet_addr(argv[1]);
	server.sin_port = htons(atoi(argv[2]));
	char buf[1024];
	struct sockaddr_in peer;
	while(1){
		socklen_t len = sizeof(peer);
		printf("Please input#");
		fflush(stdout);
		size_t s = read(0,buf,sizeof(buf)-1);
		if(s>0){
			buf[s-1] = 0;
			sendto(sock,buf,strlen(buf),0,(struct sockaddr*)&server,sizeof(server));
			size_t s = recvfrom(sock,buf,sizeof(buf)-1,0,(struct sockaddr*)&peer,&len);
			buf[s]=0;
			printf("server echo#%s\n",buf);
		}
	}
}
