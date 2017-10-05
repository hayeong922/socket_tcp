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
#define FILESIZE 200
#define FILE_NUM 9

// this is for setting things for server
#define PORT_NUM 2
#define WEB_ROOT 4
#define DEFAULT 6
#define HTML 8
#define HTM 9
#define TXT 10
#define PNG 11
#define GIF 12
#define JPG 13
#define CSS 14
#define JS 15
#define ICON 16

int glob_port_num;
char *glob_web_root;
char *glob_default;


struct HTTP_FORM{
	char method[FILESIZE];
	char URL[FILESIZE];
	char http_version[FILESIZE];
};

struct ws_conf{
	int port_num;
	char web_root[FILESIZE];
	char defualt[FILESIZE];
	// content type
	char content_ext[FILE_NUM+1][FILESIZE];  //  content type [0] column
	char content_enc[FILE_NUM+1][FILESIZE];	// content type [1] column
};

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

void read_conf(struct ws_conf *config){
	char *root_path;
	char *curr;
	char *read_param;
	char *test;
	char buff[MAXBUFFSIZE+1];
	char temp_path[MAXBUFFSIZE+1];
	char read[FILESIZE];
	int count = 1;

	root_path = getcwd(buff,MAXBUFFSIZE);
	strcpy(temp_path,root_path);
	strcat(temp_path,"/ws.conf");
	printf("temp_path:%s\n",temp_path);


	//ws.conf file
	FILE *file;
	file = fopen(temp_path,"r");
	if(file == NULL){
		perror("cannot read file\n");
		exit(-1);
	}

	while(fgets(read,FILESIZE,file) != NULL)
	{
		switch(count){
			case PORT_NUM:
				curr = strtok_r(read, " ",&read_param);
				printf("pot number: %s\n", read_param);
				glob_port_num = atoi(read_param);
				break;
			case WEB_ROOT:
				curr = strtok_r(read, " ",&read_param);
				test = strtok(saveptr,"\"");
				printf("test: %s %d\n",test,strlen(test));
				strcpy(glob_web_root,test);
				break;
			case DEFAULT:
				curr = strtok_r(read, " ",&read_param);
				test = strtok(saveptr,"\n");
				printf("test: %s %d\n",test,strlen(test));
				strcpy(glob_default,test);
				break;
			case HTML:
				break;
			case HTM:
				break;
			case TXT:
				break;
			case PNG:
				break;
			case GIF:
				break;
			case JPG:
				break;
			case CSS:
				break;
			case JS:
				break;
			case ICON:
				break;

		}
			

		count++;
	}
	fclose(file);

}

int main(int argc, char ** argv){

	int socket_desc, client_sock, c, read_size;
	struct sockaddr_in client;
	unsigned int sockaddr_len = sizeof(struct sockaddr_in);
	struct ws_conf config;

	// set up server
	//setup_server
	printf("start!\n");
	read_conf(&config);





	// set socket
	//socket_desc = socket_bind()





}