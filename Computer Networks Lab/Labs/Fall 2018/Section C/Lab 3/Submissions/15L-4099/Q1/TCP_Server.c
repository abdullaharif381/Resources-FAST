/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr

int main(void)
{

        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;
        char server_message[2000];
        char client_message[2000];
        char * s="Hello. I am server. Your id is ";

        //Cleaning the Buffers
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        //Creating Socket
        
        socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        
        if(socket_desc < 0)
        {
                printf("Could Not Create Socket. Error!!!!!\n");
                return -1;
        }
        
        printf("Socket Created\n");
        
        //Binding IP and Port to socket
        
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0)
        {
                printf("Bind Failed. Error!!!!!\n");
                return -1;
        }        
        
        printf("Bind Done\n");
        
        //Put the socket into Listening State
        
        if(listen(socket_desc, 1) < 0)
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        //Accept the incoming Connections
        
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        
        //Receive the message from the client
        while (1)
        {
        int i=0;
        char id[1]={'1'};
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Client Message: %s\n",client_message);
        
        
          while(i<strlen(client_message))
                {
                          if(client_message[i]=='0' || client_message[i]=='1' || client_message[i]=='2'|| client_message[i]=='3' ||client_message[i]=='4'|| 
                             client_message[i]=='9' || client_message[i]=='8' || client_message[i]=='7'|| client_message[i]=='6' || client_message[i]=='5')
                          {
                                  id[0]=client_message[i];
                                  break;
                                  
                          }
                        //id[1]='\0';
                         i++; 
                }
        //printf("%s",id);
             if (client_message=='q')
        {
                close(client_sock);
        close(socket_desc);
        }
        
        //Send the message back to client
        
        //strcpy(server_message, client_message);
       // printf("Enter Message: ");
      // gets(server_message);
        
     strcpy(server_message, s); 
      strcat (server_message, id); 
      //puts(server_message);
        if (send(client_sock, server_message, strlen(server_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
            
       
     
          //Closing the Socket
         
        }
        return 0;       
}
