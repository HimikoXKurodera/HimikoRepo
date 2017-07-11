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

void writemessage(int iFd, char *buff);

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
	int middleman; 
	int iMessageLen=0; // length of user entered message
	
	char sendBuff[256];
	int iPid=0; // variable to track process id which is the process for each connection 
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
	// TO DO: start the while loop here 
	/*new_socket=accept(server_fd,(struct sockaddr *) &cliaddr, &clilen);
	while(1)
	middleman=read(new_socket,sendBuff,255);
	if(middleman<0)
	{
		perror("Failed to read from socket exiting..");
		exit(EXIT_FAILURE);
	}
	printf("Message : %s\n",sendBuff);
	cUsermessage="I got your message\n";
	iMessageLen=strlen(cUsermessage);
	middleman=write(new_socket,cUsermessage,iMessageLen);
	if (middleman<0)
	{
		perror("Failed to write from socket exiting...");
		exit(EXIT_FAILURE);
	}*/
	
	while(1)
	{
		new_socket=accept(server_fd,(struct sockaddr *) &cliaddr, &clilen);
		if (new_socket<0)
		{
			perror("Error on accepting socket");
			exit(1);
		}
		iPid=fork();
		if(iPid<0)
		{
			perror("Error on fork");
			exit(1);
		}
		if(iPid==0)
		{
			close(server_fd);
			writemessage(new_socket, sendBuff);
			exit(0);
		}
		else
		{
			close(new_socket);
		}	
	}
	return 0;
}

void writemessage(int iFd, char *buff)
{
	int iMiddleman=-1;
	iMiddleman=read(iFd,buff,255);
	char *cUsermessage;
	int iMessageLen=-1;
	if(iMiddleman<0)
	{
		perror("Failed to read from socket exiting program...");
		exit(1);
	}
	
	printf("Message : %s\n",buff);
	cUsermessage="I got your message\n";
	iMessageLen=strlen(cUsermessage);
	iMiddleman=write(iFd,cUsermessage,iMessageLen);
	if (iMiddleman<0)
	{
		perror("Failed to write from socket exiting...");
		exit(1);
	}
}
