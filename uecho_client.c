//
// Created by M on 2023/11/20.
//
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#define BUF_SIZE 30

void error_handling(char *message);

int main(int argc, char * argv[]) {
    int sock;
    char message[BUF_SIZE];
    int str_len;
    struct sockaddr_in server_addr,from_addr;
    socklen_t adr_sz;


    if (argc != 3) {
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        error_handling("socket error");
    }
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(argv[1]);
    server_addr.sin_port = htons(atoi(argv[2]));

    while (1) {
        fputs("Insert message (q or Q to quit)", stdout);
        fgets(message, sizeof (message), stdin);
        if (!strcmp(message, "Q\n") || !strcmp(message, "q\n")) {
            break;
        }
        sendto(sock, message, strlen(message), 0,(struct sockaddr *)&server_addr,sizeof (server_addr));
        adr_sz = sizeof(from_addr);
        str_len = recvfrom(sock,message,BUF_SIZE,0,(struct sockaddr*)&from_addr,&adr_sz);
        message[str_len] = 0;
        printf("message from server %s\n", message);
    }
    close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
