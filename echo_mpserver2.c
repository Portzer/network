//
// Created by M on 2023/12/3.
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


int main(int argc, char * argv[]){
    int serv_sock,client_sock;
    struct sockaddr_in serv_addr,client_addr;
    pid_t pid;
    char buff[BUF_SIZE];
    int fds[2];
    int str_len;
    struct sigaction sig;
    if(argc!=2){
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1) {
        error_handling("socket error");
    }
    memset(&serv_addr,0,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    sig.sa_handler = read_child_proc;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGCHLD, &sig, NULL);
    pipe(fds);
    if (bind(serv_sock, (struct sockaddr *) &serv_addr, sizeof(serv_addr))) {
        error_handling("bind error");
    }
    if (listen(serv_sock, 5)) {
        error_handling("listen error");
    }
    pid = fork();
    //创建进程,将读取从通道读取到的内容写入到磁盘
    if (pid == 0) {
        FILE *fp = fopen("echomessage.text", "wb");
        if(fp == NULL) {
            printf("create file is failed");
        }
        char readbuff[BUF_SIZE];
        int read_len;
        for (int i = 0; i < 10; i++) {
            read_len = read(fds[0], readbuff, BUF_SIZE);
            printf("read message from pipe is : %s\n",readbuff);
            fseek(fp, 0, SEEK_END);
            int res = fwrite((void *) readbuff, 1, read_len, fp);
            fflush(fp);
            printf("write res is %d \n", res);
        }
        fclose(fp);
        return 0;
    }
    while (1) {
        socklen_t csz = sizeof(client_addr);
        client_sock = accept(serv_sock,(struct sockaddr*)&client_addr,&csz);
        if (client_sock == -1) {
            continue;
        }
        puts("new client connected..");
        pid = fork();
        if (pid == -1) {
            continue;
        }
        if (pid == 0){
            close(serv_sock);
            while ((str_len = read(client_sock, buff, BUF_SIZE)) != 0) {
                write(client_sock, buff, str_len);
                printf("write message from client is %s \n", buff);
                write(fds[1], buff, str_len);
            }
            close(client_sock);
            puts("client disconnected");
            return 0;
        } else
            close(client_sock);
    }
    close(serv_sock);
    return 0;
}

void error_handling(char *message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

void read_child_proc(int signal){
    int status;
    pid_t pid = waitpid(-1, &status,WNOHANG );
    if (WIFEXITED(status)) {
        printf("child process pid is %d, status is %d\n", pid, WEXITSTATUS(status));
    }
}