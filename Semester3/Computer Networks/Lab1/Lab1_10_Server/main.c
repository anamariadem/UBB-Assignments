#include <stdio.h>

#ifndef WIN32
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>


#define closesocket close

#else
// on Windows include and link these things
#include<WinSock2.h>
// for uint16_t an so
#include<cstdint>
// this is how we can link a library directly from the source code with the VC++ compiler – otherwise got o project settings and link to it explicitly
//#pragma comment(lib,"Ws2_32.lib")
#endif


/*
 * The client sends to the server two strings. The server sends back the character with the largest number of
 * occurrences on the same positions in both strings together with its count.
 */

int main() {
    int socketDescriptor;
    struct sockaddr_in server, client;

    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server, 0, sizeof(server));
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = 0;

    bind(socketDescriptor, (struct sockaddr*) &server, sizeof(server));

    listen(socketDescriptor, 7);
    memset(&client, 0, sizeof(client));

    while (1){
        int size = sizeof(client);
        printf("Listening for incomming connections\n");
        int clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr*) &client, &size);

        printf("Incomming connected client from: %s:%d", inet_ntoa(client.sin_addr), ntohs(client.sin_port));

        char receivedString[200];
        char anotherReceivedString[100];

        recv(clientSocketDescriptor, (char*)receivedString, 100, 0);
        receivedString[strlen(receivedString) - 1] = '\0';

        recv(clientSocketDescriptor, (char*)anotherReceivedString, 100, 0);

        strcat(receivedString, anotherReceivedString);

        send(clientSocketDescriptor, (char*)receivedString, 200, 0);

        close(clientSocketDescriptor);
    }

    return 0;
}
