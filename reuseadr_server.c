//
// Created by M on 2023/11/27.
//
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

#define TRUE 1
#define FALSE 0

void error_handing(char *message);

int main(int argc, char *argv[]){
    int serv_sock,clnt_sock;
    char message[BUF_SIZE];
    int ser_len,option;
    struct sockaddr_in serv_addr,clnt_addr;
    socklen_t clnt_addr_sz,opt_len;

    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1)
        error_handing("socket() error");

    opt_len = sizeof(option);
    option = TRUE;
    setsockopt(serv_sock, SOL_SOCKET, SO_REUSEADDR, (void *) &option, opt_len);
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htons(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handing("bind() error");
    }
    if (listen(serv_sock, 5) == -1) {
        error_handing("listen () error");
    }
    clnt_addr_sz = sizeof(clnt_addr);
    for (int i = 0; i < 5; ++i) {
        clnt_sock = accept(serv_sock, (struct sockaddr *)&clnt_addr,&clnt_addr_sz);
        if (clnt_sock == -1) {
            error_handing("accept {} error");
        }
        else
            printf("Connect client %d \n", i + 1);
        while ((ser_len = read(clnt_sock, message, BUF_SIZE)) != 0) {
            write(clnt_sock, message, ser_len);
        }
        close(clnt_sock);
    }
    close(serv_sock);
    return 0;

}
void error_handing(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
