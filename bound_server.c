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
    char message[BUF_SIZE];
    struct sockaddr_in serv_addr,client_addr;
    socklen_t add_sz;
    int str_len;
    if(argc!=2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1)
        error_handling("socket error");
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    if (bind(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind error");
    }
    for (int i = 0; i < 3; ++i){
        sleep(5);
        add_sz = sizeof(client_addr);
        str_len = recvfrom(sock, message,BUF_SIZE, 0, (struct sockaddr*)&client_addr,&add_sz);
        printf("Message %d:%s\n", i + 1, message);

    }
    close(sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
