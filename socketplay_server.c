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
	int iInterfaceassoc=-1;
	int set_socketopt=1;
	
	int iPort=-1;
	struct sockaddr_in servaddr, cliaddr; 
	int clilen=-1; // length of client ip address 
	int iListenSuccess=-1;
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
	
	if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,&set_socketopt, sizeof(set_socketopt)))
    {
        perror("Failed to set the appropiate socket options");
        exit(EXIT_FAILURE);
    }
	
	memset(&servaddr,'0',sizeof(servaddr));
	memset(&sendBuff,'0',sizeof(sendBuff));
	iPort=atoi(argv[1]);
	
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(iPort);
    iInterfaceassoc=bind(server_fd,(struct sockaddr *) &servaddr,sizeof(servaddr));
    if(iInterfaceassoc<0)
    {
		perror("Failed to associate socket with network interface");
		exit(EXIT_FAILURE);
	}
	iListenSuccess=listen(server_fd,32);
	if(iListenSuccess<0)
	{
		perror("Listening failed, try again later");
		exit(EXIT_FAILURE);
	}
	clilen=sizeof(cliaddr);
	/*
	 * Just an aside to myself as the developer: 
	 * 	 The accept system call does the following:
	 * 			Takes the first pending connection from the queue for the listening
	 * 			socket [which in our case is the socket associated with the file descriptor server_fd]
	 * creates a new socket file descriptor referring to that socket. At that point, client and server are ready to exchange data. 
	 * */
	new_socket=accept(server_fd,(struct *sockaddr) &cliaddr, &clilen);
	
}
