//
// Created by M on 2023/12/2.
//

#include <unistd.h>
#include <stdio.h>

#define BUFF_SIZE 30

int main(int argc, char *argv[]){
    int fds[2];
    char message[] = "Hello, world!";
    char buff[BUFF_SIZE];
    pipe(fds);
    int pid = fork();
    if (pid == 0) {
        write(fds[1], message, sizeof(message));
    } else{
        read(fds[0], buff, BUFF_SIZE);
        printf("this is parent process \n");
        puts(buff);
    }
    return 0;
}