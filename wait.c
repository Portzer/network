//
// Created by M on 2023/11/28.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
/**
 * wait(int *status)在父进程获取到子进程return和exit()函数的返回值,
 * wait函数的缺点 如果没有终止的子进程，那么程序将一直阻塞直到有子进程终止
 */
int main(int argc, char *argv[]){

    int status;
    pid_t pid = fork();
    if (pid == 0) {
        return 3;
    }else{
        printf(" Child process id is %d\n", pid);
        pid = fork();
        if (pid == 0) {
            exit(7);
        }
        else {
            printf(" Parent process id is %d\n", pid);
            wait(&status);
            if (WIFEXITED(status)) {
                printf(" Child process send one %d\n", WEXITSTATUS(status));
            }
            wait(&status);
            if (WIFEXITED(status)) {
                printf(" Child process send two %d \n", WIFEXITED(status));
            }
            sleep(30);
        }
    }
    return 0;
}