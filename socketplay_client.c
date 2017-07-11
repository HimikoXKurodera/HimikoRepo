#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <netdb.h>

int main(int argc, char const *argv[])
{
	int iClientfd=0;
	int iServeraddr=0;
	int iPort=-1;
	int iMiddleman=-1;
	int iClientLen=-1;
	int iConnectSucess=-1;
	char userbuff[256];
	
	struct sockaddr_in servaddr;
	struct hostent *server;
	if(argc<3)
	{
		fprintf(stderr,"Less than three arguments passed, the usage for this client program is %s hostname portname\n", argv[0]);
		exit(0);
	}
	iPort=atoi(argv[2]);
	iClientfd=socket(AF_INET,SOCK_STREAM,0);
	if(iClientfd <0)
	{
		perror("Error opening socket");
		exit(0);
	}
	server=gethostbyname(argv[1]);
	if(server==NULL)
	{
		fprintf(stderr,"Error no such host\n");
		exit(0);
	}
	memset(&servaddr,'0',sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	//bcopy((char *)server->h_addr,(char *)servaddr.sin_addr.s_addr,server->h_length);
	bcopy((char *)server->h_addr,(char *)&servaddr.sin_addr.s_addr,server->h_length);
	servaddr.sin_port=htons(iPort);
	iConnectSucess=connect(iClientfd,&servaddr,sizeof(servaddr));
	if(iConnectSucess<0)
	{
		perror("Connection to server failed\n");
		exit(0);
	}
	printf("Please enter your message: \n");
	bzero(userbuff,256);
	scanf("%s",userbuff);
	iMiddleman=write(iClientfd,userbuff,255);
	if(iMiddleman<0)
	{
		perror("Failed to write to socket exiting...");
		exit(0);
	}
	iMiddleman=read(iClientfd,userbuff,255);
	if(iMiddleman<0)
	{
		perror("Failed to read to socket exiting...");
		exit(0);
    }
    printf("%s/n",userbuff);
    return 0;
}
