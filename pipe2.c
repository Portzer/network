//
// Created by M on 2023/12/3.
//

#include <stdio.h>
#include <unistd.h>

#define BUFF_SIZE 30

int main(int argc,char *argv[]){
    int fds[2];
    char str1[] = "hello world";
    char str2[] = "thank you";
    char buff[BUFF_SIZE];
    pipe(fds);
    pid_t  pid = fork();
    if (pid == 0) {
        puts("this is child process \n");
        write(fds[1], &str1, sizeof(str1));
        sleep(2);
        read(fds[0], buff, BUFF_SIZE);
        puts(buff);
    }else{
        read(fds[0], buff, BUFF_SIZE);
        puts(buff);
        puts("this is parent process \n");
        write(fds[1], &str2, sizeof(str2));
        sleep(3);
    }
    return 0;
}
