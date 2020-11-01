#include <stdio.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>

int clientSocketDescriptor;

char** separate(char command[]){
    char** result = (char**)malloc(100 * sizeof(char*));

    for(int i=0 ;i<100;i++){
        result[i] = (char*)malloc(100 * sizeof(char));
    }
    int j=0, k=0;
    for(int i=0;i<strlen(command);i++){
        if(command[i] == ' '){
            result[j][k] = '\0';
            j++;
            k=0;
        } else{
            result[j][k++] = command[i];
        }
    }
    result[j+1] = ">";
    result[j+2] = "cv.txt";
    result[j+3] = NULL;
    return result;
}

void executeCommand(){
    char command[100];

    recv(clientSocketDescriptor, command, 100, 0);
    //printf("%s\n", command);

    char** shellCommand = separate(command);

    strcat(command, "> cv.txt");

    //FILE* fd = fopen("cv.txt", "w");
    //fclose(fd);

    if(fork() == 0){
        execlp( "/bin/sh", "/bin/sh", "-c", command, (char *)NULL );
        //execvp(shellCommand[0], shellCommand);
    }

    wait(0);

    char result[1000], line[100];
    memset(result, 0, 1000);

    FILE* fd = fopen("cv.txt", "r");
    //fgets(result, 1000, fd);

    while(fgets(line, 100, fd) > 0){
        strcat(result, line);
    }

    send(clientSocketDescriptor, result, 1000, 0);

    fclose(fd);

    close(clientSocketDescriptor);

    exit(0);
}



int main() {
    int socketDescriptor;
    struct sockaddr_in client, server;

    socketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(socketDescriptor < 0){
        printf("Error creating socket");
        exit(1);
    }

    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(4321);
    server.sin_addr.s_addr = 0;

    int code = bind(socketDescriptor, ( struct sockaddr *)&server, sizeof(server));

    if(code < 0){
        printf("Bind error");
        exit(1);
    }

    listen(socketDescriptor, 3);

    while (1){
        memset(&client, 0, sizeof(client));
        printf("Listening for incoming connections.\n");

        int size = sizeof(client);

        clientSocketDescriptor = accept(socketDescriptor, (struct sockaddr *)&client, &size);

        if(clientSocketDescriptor < 0){
            printf("Error returning client socket");
            exit(1);
        }

        printf("A client with adrress %s and port %d connected.\n", inet_ntoa(client.sin_addr), ntohs(client.sin_port));
        int pid = fork();

        if(pid < 0){
            printf("Error on fork");
            exit(1);
        }
        if(pid == 0){
            executeCommand();
        }
    }



    return 0;
}
