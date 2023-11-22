//
// Created by M on 2023/11/21.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#define BUF_SIZE 30
void error_handling(char *message);

int main(int argc,char *argv[]){

    int sock;
    char msg1[] = "hello";
    char msg2[] = "world";
    char msg3[] = "udp";
    struct sockaddr_in addr;
    socklen_t addrlen;
    if (argc != 3) {
        printf("Usage: %s <IP> <PORT>\n", argv[0]);
        exit(1);
    }
    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == 1) {
        error_handling("socket error");
    }
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr(argv[1]);
    addr.sin_port = htons(atoi(argv[2]));

    sendto(sock,msg1,sizeof(msg1),0,(struct sockaddr*)&addr, sizeof(addr));
    sendto(sock,msg2,sizeof(msg2),0,(struct sockaddr*)&addr, sizeof(addr));
    sendto(sock,msg3,sizeof(msg3),0,(struct sockaddr*)&addr, sizeof(addr));
    close(sock);
    return 0;
}
void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
