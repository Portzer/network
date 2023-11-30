//
// Created by M on 2023/11/30.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include<sys/wait.h>
#include<arpa/inet.h>
#include<sys/socket.h>

#define BUF_SIZE 30
void error_handling(char *message);
void read_child_proc(int signal);

int main(int argc, char *argv[]){
    int serv_sock,client_sock;
    struct sockaddr_in serv_addr,client_addr;
    struct sigaction sig;
    char buf[BUF_SIZE];
    int str_len;
    socklen_t addr_len;
    if (argc != 2) {
        printf("Usage: %s <port> \n", argv[0]);
        exit(1);
    }
    serv_sock = socket(AF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    sig.sa_handler = read_child_proc;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGCHLD, &sig, 0);
    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        error_handling("bind error");
    }
    if (listen(serv_sock, 5)) {
        error_handling("listen error");
    }
    while (1) {
        addr_len = sizeof(client_addr);
        client_sock = accept(serv_sock,(struct sockaddr *) &client_addr, &addr_len);
        if (client_sock == -1) {
            continue;
        }
        pid_t pid = fork();
        if (pid == -1) {
            close(client_sock);
            continue;
        }
        if (pid == 0) {
            close(serv_sock);
            while (str_len = read(client_sock, buf, BUF_SIZE)) {
                write(client_sock, buf, str_len);
            }
            close(client_sock);
            puts("disconnected...");
        } else{
            close(client_sock);
        }
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message){
    fputs(message, stderr);
    putc('\n',stderr);
    exit(1);
}


void read_child_proc(int signal){
    int status;
    pid_t pid = waitpid(-1, &status,WNOHANG );
    if (WIFEXITED(status)) {
        printf("child process pid is %d, status is %d\n", pid, WEXITSTATUS(status));
    }
}