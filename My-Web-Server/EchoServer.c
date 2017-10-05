#include<limits.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<errno.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<pthread.h>
#include<sys/stat.h>

#define FALSE 0
#define TRUE 1
#define BAD_REQUEST 400
#define NOT_FOUNF 404
#define NOT_IMPLEMENTED 501
#define INTERNET_SERVER_ERROR 051

#define MAXBUFFSIZE 1024

#define THREAD_NUM 4
#define FILESIZE 100


struct HTTP_FORM{
	char method[FILESIZE];
	char URL[FILESIZE];
	char http_version[FILESIZE];
}

// set socket and bind for connection
int socket_bind(int port_num, int client_num){

	struct sockaddr_in server;
	int sock;

  server.sin_family = AF_INET;
  server.sin_port = htons(port_num);
  server.sin_addr.s_addr = INADDR_ANY;

  // make it zero the sockaddr_in struct for the right size
  memset(server.sin_zero, '\0', sizeof(server.sin_zero));

 if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
     perror("server socket: ");
     exit(-1);
   }
 puts("socket created\n");

if ((bind(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_in))) < 0) {
    perror("bind : ");
    exit(-1);
  }
puts("bind done\n");

// listen part, make it listen to number of clients, client_num : max number of cients
if((listen(sock, client_num)) < 0){
	perror("listen failed\n");
	exit(-1);
}

return sock;

}


int main(int argc, char ** argv){

	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in client;
	unsigned int sockaddr_len = sizeof(struct sockaddr_in);

	// set up server
	//setup_server



	// set socket
	//socket_desc = socket_bind()





}