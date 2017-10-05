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