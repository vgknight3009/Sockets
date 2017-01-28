#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>		
#include<netinet/in.h>		// to provide the size of structures
#include<errno.h>		// for perror
#include<string.h>		// for bzero(& others)
#include<unistd.h>
#include<arpa/inet.h>
#include<strings.h>

#define error -1
#define buffer 1024

main(int argc,char **argv)
{
	struct sockaddr_in remoteserver ;
	int len,sock;
	char ip[buffer];
	char op[buffer];

	if((sock=socket(AF_INET,SOCK_STREAM,0))==error)
	{
		perror("socket: ");
		exit(-1);
	}
	
	remoteserver.sin_family = AF_INET;
	remoteserver.sin_port = htons(atoi(argv[2]));
	remoteserver.sin_addr.s_addr = inet_addr(argv[1]) ;
	bzero(&remoteserver.sin_zero,8) ;
	
	/*if((connect(sock,(struct sockaddr *)& remoteserver,sizeof(struct 		sockaddr_in)))==error);
	{printf("nkkii\n");
		perror("connect") ;
		exit(-1);
	}*/

	connect(sock,(struct sockaddr *)& remoteserver,sizeof(struct 			sockaddr_in));
	
	while(1)
{
	fgets(ip,buffer,stdin) ;
	send(sock,ip,strlen(ip),0) ;
	
	len = recv(sock,op,buffer,0); 
	op[len]='\0' ;
	printf("%s\n",op) ;
	
}

	close(sock) ;


}
