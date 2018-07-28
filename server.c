#pragma comment(lib,"ws2_32.lib") //The #pragma comment indicates to the linker that the Ws2_32.lib file is needed
#include<winsock2.h>
#include<io.h>
#include<stdio.h>
#include<stdbool.h>

#define PORT 8888
#define IPADDR "127.0.0.1"
  
int main(int argc , char *argv[])
{
    WSADATA wsa;
    SOCKET host_sock, new_conn_sock;
    struct sockaddr_in server_addr, client_addr;
    int addrlen;
  
    printf("\nInitialising Winsock...");
	//The WSAStartup function is called to initiate use of WS2_32.dll.
	//The WSADATA structure contains information about the Windows Sockets implementation.
	//The MAKEWORD(2,2) parameter of WSAStartup makes a request for version 2.2 of Winsock on the system,
	//and sets the passed version as the highest version of Windows Sockets support that the caller can use.
    if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
      
    printf("Initialised.\n");
      
    //Create a  host socket
    //для сокета sockfd определена только локальная часть канала. Это
    //позволяет серверу продолжать использовать sockfd для "прослушивания" последующих запросов.
    if((host_sock = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
    }
  
    printf("Socket created.\n");
      
    //Prepare the sockaddr_in structure
	addrlen = sizeof(struct sockaddr_in);
    server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = inet_addr(IPADDR);
    server_addr.sin_port = htons(PORT);
      
    //Bind
    if( bind(host_sock ,(struct sockaddr *)&server_addr , sizeof(server_addr)) == SOCKET_ERROR)
    {
        printf("Bind failed with error code : %d" , WSAGetLastError());
    }
      
    puts("Bind done");
  
    //Listen to incoming connections
    listen(host_sock , 3);
      
    //Accept and incoming connection
    puts("Waiting for incoming connections...");
	//accept gets first query from clients queue and create virtual chanel with him
	//besides that accept returns client parameters (sockaddr_in structure as well as server structure)
	//client's address have to for non anonymous
    // отдельный канал для взаимодействия
    new_conn_sock = accept(host_sock, (struct sockaddr *)&client_addr, &addrlen);
    if (new_conn_sock == INVALID_SOCKET)
    {
        printf("accept failed with error code : %d" , WSAGetLastError());
    }
	else
	{		
		puts("Connection accepted");
	}
    //Reply to client
    char buff[256] = "Welcome to kvipe server!";
    while(true)
    {
        printf("Message to client:");
        fgets(buff,sizeof(buff), stdin);
        send(new_conn_sock , buff , sizeof(buff) , NULL);
    }

    getchar();
  
    closesocket(host_sock);
    WSACleanup();
      
    return 0;
}