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
#include <netdb.h>



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
	struct addrinfo hints;
	struct addrinfo *cur, *result;
	int clilen=-1; // length of client ip address 
	int iListenSuccess=-1;
	int middleman; 
	int iMessageLen=0; // length of user entered message
	int iSuccess=-1;
	
	char sendBuff[256];
	int iPid=0; // variable to track process id which is the process for each connection 
	
	if(argc<2)
	{
		fprintf(stderr,"There is no port number provided please try again with a port number\n");
		exit(EXIT_FAILURE);
	}
	memset(&hints,0,sizeof(struct addrinfo ));
	
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_flags=AI_PASSIVE;
	hints.ai_protocol = 0;          
    hints.ai_canonname = NULL;
    hints.ai_addr = NULL;       
    hints.ai_next = NULL;
    
    iSuccess=getaddrinfo(NULL,argv[1],&hints,&result);
    if(iSuccess!=0)
    {
		perror("Failed to obtain information on host...");
		exit(EXIT_FAILURE);
	}
    for(cur=result;cur !=NULL;cur=cur->ai_next)
    {
		server_fd=socket(cur->ai_family,cur->ai_socktype,cur->ai_protocol);
		if(server_fd==-1)
		{
			continue;
		}
		
		if(bind(server_fd,cur->ai_addr, cur->ai_addrlen)==0)
		{
			break;
		}
		close(server_fd);
	}
	

	if(cur==NULL)
	{
		perror("Couldn't bind to interface\n");
		exit(EXIT_FAILURE);
	}
	iListenSuccess=listen(server_fd,32);
	if(iListenSuccess<0)
	{
		perror("Failed to listen to port\n");
		exit(EXIT_FAILURE);
	}
	clilen=sizeof(cliaddr);
	
	
	while(1)
	{
		//new_socket=accept(server_fd,(struct sockaddr *) &cliaddr, &clilen);
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
		exit(0);
	}
	
	printf("Message : %s\n",buff);
	cUsermessage="I got your message \n";
	iMessageLen=strlen(cUsermessage);
	iMiddleman=write(iFd,cUsermessage,iMessageLen);
	if (iMiddleman<0)
	{
		perror("Failed to write from socket exiting...");
		exit(0);
	}
}
