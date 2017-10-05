/*
    C socket server example
*/
 
#include<stdio.h>
#include<string.h>    //strlen
#include<sys/socket.h>
#include<arpa/inet.h> //inet_addr
#include<unistd.h>    //write

#define BUFFSIZE 128
 
int main(int argc , char *argv[])
{
    int socket_desc , client_sock , c , read_size;
    struct sockaddr_in server , client;
    char client_message[2000];
    char mess[2000] = "HTTP/1.1 200 OK\r\nContent-Length: 30\r\nContent-Type: text/html\r\n\r\n<html><body><h1>test</h1></body></html>\r\n";
    

    int file_size;
    char message[BUFFSIZE];

    FILE* file;



    //Create socket
    socket_desc = socket(AF_INET , SOCK_STREAM , 0);
    if (socket_desc == -1)
    {
        printf("Could not create socket");
    }
    puts("Socket created");
     
    //Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;

    server.sin_port = htons( 8881 );
     
    //Bind
    if( bind(socket_desc,(struct sockaddr *)&server , sizeof(server)) < 0)
    {
        //print the error message
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");
     
    //Listen
    listen(socket_desc , 3);
     
    //Accept and incoming connection
    
    do{
        puts("Waiting for incoming connections...");
        c = sizeof(struct sockaddr_in);
         
        //accept connection from an incoming client
        client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t*)&c);
        if (client_sock < 0)
        {
            perror("accept failed");
            return 1;
        }
        puts("Connection accepted");

        read_size = recv(client_sock,client_message,3,0);
        message[4] = 0;
        file_size = atoi(client_message);

        read_size = recv(client_sock,client_message,file_size,0);
        message[file_size] = 0;
        file = fopen(client_message,"w");
         
        //Receive a message from client
        // while( (read_size = recv(client_sock , client_message , 2000 , 0)) > 0 )
        while( (read_size = recv(client_sock , mess , 30 , 0)) > 0 )
        {
            //Send the message back to client
            // write(client_sock , message , strlen(message));
            // printf("read_size: %d\n",read_size);
            write(client_sock , mess , strlen(mess));
            printf("%s",mess);
            // break;
        }
        // printf("%s",mess);
        // write(client_sock , mess , strlen(mess));

         
        if(read_size == 0)
        {
            puts("Client disconnected");
            fflush(stdout);
        }
        else if(read_size == -1)
        {
            perror("recv failed");
        }

    }while(1);
    
     
    return 0;
}
