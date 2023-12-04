//
// Created by M on 2023/12/2.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<arpa/inet.h>
#include <sys/socket.h>

#define BUF_SIZE 30

void error_handling(char *message);

void write_routine(int sock, char buff[30]);

void read_routine(int sock, char buff[30]);

int main(int argc, char *argv[]){

    int serv_sock;
    struct sockaddr_in client_addr;
    char buff[BUF_SIZE];
    if (argc != 3) {
        printf("Usage: %s <IP> <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket() error");
    }
    memset(&client_addr, 0, sizeof(client_addr));
    client_addr.sin_family = AF_INET;
    client_addr.sin_addr.s_addr= inet_addr(argv[1]);
    client_addr.sin_port = htons(atoi(argv[2]));
    if (connect(serv_sock, (struct sockaddr *) &client_addr, sizeof(client_addr))) {
        error_handling("connect error");
    }
    pid_t pid = fork();
    if (pid == 0) {
        write_routine(serv_sock, buff);
    } else{
        read_routine(serv_sock, buff);
    }
}

void read_routine(int sock, char *buff) {
    while (1){
        int str_len = read(sock, buff, sizeof(sock));
        if (str_len == 0) {
            return;
        }
        buff[str_len] = 0;
        printf("message  form server is %s \n", buff);
    }
}

void write_routine(int sock, char *buff) {
    while (1) {
        fgets(buff, BUF_SIZE, stdin);
        if (!strcmp(buff, "q\n" || !strcmp(buff, "Q\n"))) {
            shutdown(sock, SHUT_WR);
            return;
        }
        write(sock, buff, strlen(buff));
    }
}

void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}