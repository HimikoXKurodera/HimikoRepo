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
#include <strings.h>

int main(int argc, char *argv[])
{
	int server_fd=0;
	int new_socket=0;
	int valread=0;
	int set_socketopt=0;
	int iPort=-1;
	struct sockaddr_in servaddr, cliaddr; 
	int clilen; 
	int n; 
	
	char sendBuff[256];
	if(argc<2)
	{
		fprintf(stderr,"There is no port number provided please try again with a port number\n");
		exit(EXIT_FAILURE);
	}
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd <0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	memset(&servaddr,'0',sizeof(servaddr));
	memset(&sendBuff,'0',sizeof(sendBuff));
	iPort=atoi(argv[1]);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(iPort);
    
		
}
