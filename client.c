#pragma comment(lib,"ws2_32.lib") //The #pragma comment indicates to the linker that the Ws2_32.lib file is needed
#include<winsock2.h>
#include<io.h>
#include<stdio.h>
#include<stdbool.h>
  
#define PORT 8888
#define IPADDR "127.0.0.1"

SOCKET connection;

void client_thread()
{
	char buffer[256]; //Create buffer to hold messages up to 256 characters
	while (true)
	{
		recv(connection, buffer, sizeof(buffer), NULL); //receive buffer
		printf("%s\n", buff);
	}
}

int main(int argc , char *argv[])
{
	WSADATA wsa;
	struct sockaddr_in client_addr;
	int addrlen;
	char *message;
	
	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
    {
        printf("Failed. Error Code : %d",WSAGetLastError());
        return 1;
    }
	
	//Create a  host socket
    if((connection = socket(AF_INET , SOCK_STREAM , 0 )) == INVALID_SOCKET)
    {
        printf("Could not create socket : %d" , WSAGetLastError());
        return 1;
    }
	
	addrlen = sizeof(struct sockaddr_in);
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(IPADDR);
    client_addr.sin_port = htons(PORT);
	
	if (connect(connection, (SOCKADDR*)&client_addr, addrlen) != 0) //If we are unable to connect...
	{
		printf("Failed to connect");
		return 1; //Failed to Connect
	}
	printf("Connection established");
	CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)client_thread, NULL, NULL, NULL); //Create the client thread that will receive any data that the server sends.
	char buff[256];
	while(true)
	{
		printf("Enter your message:");
		fgets(buff, sizeof(buff), stdin);
		send(connection, buffer, sizeof(buffer), NULL); //Send buffer
	}

	closesocket(connection);
    WSACleanup();
	
	return 0; 
}