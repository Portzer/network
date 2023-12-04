//
// Created by M on 2023/12/4.
//
#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include <sys/select.h>
#include <unistd.h>

#define BUF_SIZE 30

int main(int argc, char *argv[]){
    fd_set reads,temp;
    int result,str_len;
    char buf[BUF_SIZE];
    struct timeval timeout;
    FD_ZERO(&reads);
    FD_SET(0, &reads);


    while (1) {
        temp = reads;
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        result = select(1, &temp, 0, 0, &timeout);
        if (result == -1) {
            puts("select failed");
            break;
        }else if (result == 0) {
            puts("time-out");
        } else {
            if (FD_ISSET(0, &reads)) {
                str_len = read(0, buf, BUF_SIZE);
                buf[str_len] = 0;
                printf("message from console %s \n", buf);
            }
        }
    }
    return 0;
}
