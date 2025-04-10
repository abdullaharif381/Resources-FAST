/*
        TCP_Server. This Program will will create the Server side for TCP_Socket Programming.
        It will receive the data from the client and then send the same data back to client.
*/

#include <stdio.h> 
#include <string.h> 
#include <sys/socket.h> //socket
#include <arpa/inet.h> //inet_addr
#include<stdbool.h>
 char*rev(char*str);
int main(void)
{
        int socket_desc, client_sock, client_size; 
        struct sockaddr_in server_addr, client_addr;
        char server_message[2000], client_message[2000];

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
        
        printf("Binded\n");
        
        //Put the socket into Listening State
        
        //Accept the incoming Connections
      

        if(listen(socket_desc, 1) < 0)
        {
                printf("Listening Failed. Error!!!!!\n");
                return -1;
        }
        
        printf("Listening for Incoming Connections.....\n");
        
        client_size = sizeof(client_addr);
        client_sock = accept(socket_desc, (struct sockaddr*)&client_addr, &client_size);
        
        if (client_sock < 0)
        {
                printf("Accept Failed. Error!!!!!!\n");
                return -1;
        }
        
        printf("Client Connected with IP: %s and Port No: %i\n",inet_ntoa(client_addr.sin_addr),ntohs(client_addr.sin_port));
        
        //Receive the message from the client
          while(1){
        if (recv(client_sock, client_message, sizeof(client_message),0) < 0)
        {
                printf("Receive Failed. Error!!!!!\n");
                return -1;
        }
    
        char* token=strtok(client_message," ");
        printf("%s\n",token);        

  
        int curr=0;
        while(token!=NULL)
        {
            int i=0;
            char *str=token;
            int size =strlen(str);
            bool flag=false;
            while(size>0 && !flag)
            {
             int v = (int)str[i];

            if((v==97||v==101||v==105||v==111||v==117))
            {
                flag=true;
                rev(str);
            }
            i++;
            size--;
            }
            for(int j=0;j<strlen(str);j++)
            {
                server_message[curr]=str[j];
                curr++;
            }
            
            server_message[curr]=' ';
            curr++;
            token=strtok(NULL," ");
        }
        
  
        printf("Client Message: %s\n",server_message);
        printf("Enter Message: ");
      gets(server_message);
        
 
        if (send(client_sock, server_message, strlen(server_message),0)<0)
        {
                printf("Send Failed. Error!!!!!\n");
                return -1;
        }
 }       
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
              
        //Closing the Socket
        
        close(client_sock);
        close(socket_desc);
        return 0;       
}

 char*rev(char*str)
 {
  int i=strlen(str)-1,j=0;
  char ch;
  while(i>j)
  {
      ch=str[i];
      str[i]=str[j];
      str[j]=ch;
      i--;
      j++;
  }
  return str;
 } 
