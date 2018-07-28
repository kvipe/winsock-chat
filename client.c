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
	SOCKET connection;
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
    }
	
	addrlen = sizeof(struct sockaddr_in);
	client_addr.sin_family = AF_INET;
	client_addr.sin_addr.s_addr = inet_addr(IPADDR);
    client_addr.sin_port = htons(PORT);
	
	if (connect(connection, (SOCKADDR*)&client_addr, addrlen) != 0) //If we are unable to connect...
	{
		printf("Failed to connect");
		return 0; //Failed to Connect
	}
	char buff[256];
	while(true)
	{
		recv(connection, buff, sizeof(buff), NULL);
		printf("%s\n", buff);
	}

	closesocket(connection);
    WSACleanup();
	
	return 0; 
}