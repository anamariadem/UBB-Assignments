#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int clientSocket;
    struct sockaddr_in server;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_port = htons(1234);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");

    connect(clientSocket, (struct sockaddr*) &server, sizeof(server));

    char stringToSend[100], anotherStringToSend[100];
    char receivedString[200];

    fgets(stringToSend, 100, stdin);
    fgets(anotherStringToSend, 100, stdin);

    send(clientSocket, (char*)stringToSend, 100, 0);
    send(clientSocket, (char*)anotherStringToSend, 100, 0);

    recv(clientSocket, (char*)receivedString, 200, 0);

    printf("%s", receivedString);
    return 0;
}
