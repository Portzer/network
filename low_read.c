//
// Created by M on 2023/11/7.
//
#include <stdio.h>
#include <stdlib.h>
#include<fcntl.h>
#include <unistd.h>
#define BUF_SIZE 100
void error_handling(char *message);
int main(void){
    int read_len = 0,idx = 0;
    int str_len = 0;
    int fd;
    char buf[BUF_SIZE];
    fd = open("data.text", O_RDONLY);
    if (fd == -1) {
        error_handling("open () error!");
    }
    printf("file descriptor:%d \n", fd);
    while (read_len = read(fd, &buf[idx++], 1)) {
        printf("read_len:%d \n", read_len);
        if (read_len == -1) {
            error_handling("read () error!");
        }
        str_len += read_len;
    }
    printf("final read_len:%d \n",read_len);
    printf("str_len:%d \n",str_len);
    printf("file data %s", buf);
    close(fd);
    return 0;
}
void error_handling(char *message){
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
