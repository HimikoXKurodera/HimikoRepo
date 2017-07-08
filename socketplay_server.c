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

int main()
{
	int server_fd=0;
	int new_socket=0;
	int valread=0;
	
	server_fd=socket(AF_INET,SOCK_STREAM,0);
	if(server_fd == 0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	
	
	
	
		
}
