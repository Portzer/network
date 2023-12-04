//
// Created by M on 2023/12/3.
//
#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 30

int main(int argc, char *argv[]){
    int fds1[2], fds2[2];
    char str1[] = "this is parent message\n";
    char str2[] = "this is child message\n";
    char buff[BUFF_SIZE];
    pipe(fds1);
    pipe(fds2);
    pid_t pid = fork();
    if (pid == 0) {
        write(fds2[1], str1, sizeof(str1));
        read(fds1[0],buff, BUFF_SIZE);
        puts(buff);
    } else{
        read(fds2[0], buff, BUFF_SIZE);
        puts(buff);
        write(fds1[1], str2, sizeof(str2));
    }
    return 0;
}
