#include <stdio.h>
#include <stdlib.h>
#include<winsock2.h>
#pragma comment(lib,"ws2_32.lib")

#define NO_FLAGS_SET 0
#define PORT 80
#define MAXBUFLEN 20480

void connectCl_v2(char * request, char * baseAddress,char * host_name, SOCKET recvSocket, char * tempBuffer);
void final_request(char * request, char * baseAddress,char * host_name, SOCKET recvSocket, char * tempBuffer,char * message,char * buffer3);
int connectCl();

int main()
{
  return connectCl();
}

void connectCl_v2(char * request, char * baseAddress,char * host_name, SOCKET recvSocket, char * tempBuffer)
{
    char * bufferPos=(char*)malloc(400);
    int numrcv = 0,status,i;
    char buffer2[MAXBUFLEN];
    memset(buffer2,0,MAXBUFLEN);
    sprintf(request, baseAddress, host_name);
    send(recvSocket, request, strlen(request), 0);
    numrcv = recv(recvSocket, buffer2, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
            printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
            printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
    printf("%s Strlen: %i\r\n", buffer2,strlen(buffer2));
    bufferPos=strstr(buffer2,"\r\n\r\n");
    strcpy(tempBuffer,"");
    for(i=0; i<strlen(bufferPos)-4; i++)
    {

        tempBuffer[i]=bufferPos[i+4];
    }
    return tempBuffer;
}

void final_request(char * request, char * baseAddress,char * host_name, SOCKET recvSocket, char * tempBuffer,char * message,char * buffer3)
{
    int numrcv,status;
    strcpy(baseAddress,"result=");
    baseAddress=strcat(baseAddress,message);
    printf("\nAddress3.0: %s  END\n",baseAddress);
    sprintf(request, "POST /var/4 HTTP/1.1\r\n"
            "Host: %s\r\n"
            "Content-type: application/x-www-form-urlencoded\r\n"
            "Content-length: %d\r\n\r\n"
            "%s\r\n", host_name, strlen(baseAddress), baseAddress);
    send(recvSocket, request, strlen(request), 0);
    numrcv = recv(recvSocket,buffer3, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
            printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
            printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
    printf("%s\r\n", buffer3);
}

int connectCl()
{
    WSADATA Data;
    SOCKADDR_IN recvSockAddr;
    SOCKET recvSocket;
    int status,i;
    int pos=0,count=0,max;
    char * bufferPos=(char*)malloc(400);
    char tempBuffer[100];
    int numrcv = 0;
    struct hostent * remoteHost;
    char * ip;
    char * baseAddress=(char*)malloc(400);
    char * receivedAddress;
    const char bA2[]=" HTTP/1.1\r\nHost:%s\r\n\r\n";
    const char * host_name ="pb-homework.appspot.com";
    char buffer[MAXBUFLEN];
    char buffer2[MAXBUFLEN];
    char buffer3[MAXBUFLEN];
    memset(buffer,0,MAXBUFLEN);
    memset(buffer2,0,MAXBUFLEN);
    memset(buffer3,0,MAXBUFLEN);
    memset(tempBuffer,0,100);
    // Initialize Windows Socket DLL
    status = WSAStartup(MAKEWORD(2, 2), &Data);
    if(status != 0)
    {
        printf("ERROR: WSAStartup unsuccessful\r\n");
        return 0;
    }
    // Get IP address from host name
    remoteHost = gethostbyname(host_name);
    ip = inet_ntoa(*(struct in_addr *)*remoteHost->h_addr_list);
    printf("IP address is: %s.\n", ip);
    memset(&recvSockAddr, 0, sizeof(recvSockAddr)); // zero the sockaddr_in structure
    recvSockAddr.sin_port=htons(PORT); // specify the port portion of the address
    recvSockAddr.sin_family=AF_INET; // specify the address family as Internet
    recvSockAddr.sin_addr.s_addr= inet_addr(ip); // specify ip address
    // Create socket
    recvSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if(recvSocket == INVALID_SOCKET)
    {
        printf("ERROR: socket unsuccessful\r\n");
        system("pause");
        return 0;
    }
    // Connect
    if(connect(recvSocket,(SOCKADDR*)&recvSockAddr,sizeof(SOCKADDR_IN)) == SOCKET_ERROR)
    {
        printf("ERROR: socket could not connect\r\n");
        closesocket(recvSocket);
        WSACleanup();
        return 0;
    }
    char request[2000];
    sprintf(request,"GET /var/4 HTTP/1.1\r\nHost:%s\r\n\r\n", host_name); // add Host header with host_name value
    send(recvSocket, request, strlen(request), 0);
    numrcv = recv(recvSocket, buffer, MAXBUFLEN, NO_FLAGS_SET);
    if (numrcv == SOCKET_ERROR)
    {
        printf("ERROR: recvfrom unsuccessful\r\n");
        status = closesocket(recvSocket);
        if(status == SOCKET_ERROR)
            printf("ERROR: closesocket unsuccessful\r\n");
        status = WSACleanup();
        if (status == SOCKET_ERROR)
            printf("ERROR: WSACleanup unsuccessful\r\n");
        system("pause");
        return(1);
    }
    printf("%s\r\n", buffer);
    bufferPos=strstr(buffer,"\r\n\r\n");
    strcpy(tempBuffer,"");
    for(i=0; i<strlen(bufferPos)-4; i++)
    {

        tempBuffer[i]=bufferPos[i+4];
    }
    printf("BufferPos: %s",tempBuffer);
    strcpy(baseAddress,"GET /var/4?");
    baseAddress=strcat(baseAddress,tempBuffer);
    baseAddress=strcat(baseAddress," HTTP/1.1\r\nHost:%s\r\n\r\n");
    printf("\nAddress2.0: %s\n", baseAddress);
    connectCl_v2(request,baseAddress, host_name,  recvSocket,tempBuffer);
    char * message=(char*)malloc(100);
    memset(message,0,100);
    max=0;
    for(i=0; i<strlen(tempBuffer); i++)
    {
        if(tempBuffer[i]==' ')
        {
            if(count>max)
            {
                max=count;
                pos=i-count;
            }
            count=-1;
        }
        if(i==strlen(tempBuffer)-1)
        {
            if(count>max)
            {
                max=count;
                pos=i-count;
            }
        }
        count++;
    }
    printf("Max: %i PosMax: %i",max,pos);
    for(i=0; i<max; i++)
    {
        message[i]=tempBuffer[i+pos];
    }
    final_request(request,  baseAddress, host_name,  recvSocket,  tempBuffer, message, buffer3);
    system("pause");
    return 0;
}
