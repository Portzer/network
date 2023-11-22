//
// Created by M on 2023/11/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define BUFF_SIZE 30
void error_handling(char *message);

int main(int argc, char *argv[]){
    int server_fd,client_fd;
    FILE *fp;
    char buff[BUFF_SIZE];
    int read_cnt;
    struct sockaddr_in serv_addr,client_addr;
    socklen_t client_addr_len;
    if (argc != 2) {
        printf("Usage: %s <port>\n", argv[0]);
        exit(1);
    }
    fp = fopen("file_server.c", "rb");
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        error_handling("socket error");
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));
    bind(server_fd,(struct sockaddr*)&serv_addr, sizeof(serv_addr));
    listen(server_fd, 5);
    client_addr_len = sizeof(client_addr);
    client_fd = accept(server_fd,(struct sockaddr*)&client_addr,&client_addr_len);
    while (1) {
        read_cnt = fread((void *) buff, 1, BUFF_SIZE, fp);
        if(read_cnt<BUFF_SIZE){
            write(client_fd, buff, read_cnt);
            break;
        }
        write(client_fd, buff, BUFF_SIZE);
    }
    shutdown(client_fd, SHUT_WR);
    read(client_fd, buff, BUFF_SIZE);
    printf("message from client %s \n", buff);
    fclose(fp);
    close(server_fd);
    close(client_fd);
    return 0;
}
void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}