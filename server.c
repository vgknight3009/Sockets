#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>		
#include<netinet/in.h>		
#include<errno.h>		
#include<string.h>		
#include<unistd.h>
#include<arpa/inet.h>
#include<strings.h>

#define error -1
#define max_client 2
#define max_data 1024

main(int argc,char **argv)	
{
	struct  sockaddr_in server,client ;
	int sock;		
	int new	;		
	int sockaddr_len = sizeof (struct sockaddr_in) ;
	int data_len ;
	char data[max_data] ;


	if((sock=socket(AF_INET,SOCK_STREAM,0))==error)
	{
		perror("server socket: ");
		exit(-1);
	}
	
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[1]));
	server.sin_addr.s_addr = INADDR_ANY ;
	bzero(&server.sin_zero,8) ;

	if((bind(sock,(struct sockaddr *)&server,sockaddr_len))==error)    
	{
		perror("bind");
		exit(-1) ;
	}
	
	
	if((listen(sock,max_client))==error)
	{
		perror("listen");
		exit(-1) ;
	}

	while(1)
{	
	new=accept(sock,(struct sockaddr *)& client,&sockaddr_len);

	printf("NEW client connected from port no %d & IP %s\n",ntohs(client.sin_port),inet_ntoa(client.sin_addr)) ;

	data_len = 1;
	while(data_len)
	{
		data_len = recv(new,data,max_data,0) ;
		if(data_len)
		{
			send(new,data,data_len,0) ;
			data[data_len]='\0' ;
			printf("Sent mess : %s\n",data) ;
		}
	}

	printf("Client disconnected...\n") ;
	close(new) ;
	
	}
	
	close(sock) ;

}
