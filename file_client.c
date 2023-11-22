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

    FILE *fp;
    int serv_fd;
    char buf[BUFF_SIZE];
    int read_cnt;
    struct  sockaddr_in serv_addr;
    if (argc != 3) {
        printf(" Usage : %s <IP address>\n", argv[0]);
        exit(1);
    }
    fp = fopen("receive.dat", "wb");
    serv_fd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    connect(serv_fd,(struct sockaddr *)&serv_addr, sizeof(serv_addr));
    while (read_cnt= read(serv_fd,buf,BUFF_SIZE)!=0)
        fwrite((void *) buf, 1, read_cnt, fp);
    puts("Received file data");
    write(serv_fd, "thank you", 10);
    fclose(fp);
    close(serv_fd);
    return 0;
}
void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}

