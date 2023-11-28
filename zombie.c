//
// Created by M on 2023/11/28.
//

/**
 * 这段代码产生僵尸进程的原因:fu'jin
 */
#include <stdio.h>
#include <unistd.h>
int main(int argc, char *argv[]){

    pid_t pid = fork();
    if (pid == 0) {
        puts("Hi, I am a child process");
    }else{
        printf("child process ID is %d\n", pid);
        sleep(30);
    }
    if (pid == 0) {
        puts("End child process \n");
    }else{
        puts("End parent process \n");
    }
    return 0;
}



