//
// Created by M on 2023/11/18.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>



#define BUF_SIZE 1024
void error_handing(char * message);
int main(int argc, char *argv[]){
   int sock;
   char message[BUF_SIZE];
   int str_len;
   struct sockaddr_in serv_addr;

    if (argc != 3) {
        printf("Usage: %s <IP> <port> \n", argv[0]);
        exit(1);
    }
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        error_handing("socket error\n");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));
    if (connect(sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handing("connect error\n");
    } else
        puts("Connected....");
    while (1) {
        fputs("Inputs message (Q to quit):", stdout);
        fgets(message, BUF_SIZE, stdin);
        if(!strcmp(message,"q\n")||!strcmp(message,"Q\n"))
        break;
        write(sock, message, strlen(message));
        str_len = read(sock, message, BUF_SIZE - 1);
        message[str_len] = 0;
        printf("Message form server :%s", message);
    }
    close(sock);
}
void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n',stderr);
    exit(1);
}