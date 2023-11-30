//
// Created by M on 2023/11/30.
//
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>


void read_child_pro(int signal){
    int status;
    pid_t pid = waitpid(-1, &status, NULL);
    if (WIFEXITED(status)) {
        printf("read child pid %d\n", pid);
        printf("child  process send signal %d \n", WEXITSTATUS(status));
    }
}


int main(int argc, char *argv[]){
    pid_t pid;
    struct sigaction sig;
    sig.sa_handler = read_child_pro;
    sigemptyset(&sig.sa_mask);
    sig.sa_flags = 0;
    sigaction(SIGCHLD, &sig, WNOHANG);
    pid = fork();
    if (pid == 0) {
        sleep(10);
        exit(21);
    }else{
        printf("child pid is %d \n", pid);
        pid = fork();
        if (pid == 0) {
            sleep(10);
            return 23;
        } else{
            printf("child pid is %d \n", pid);
            for(int i = 0; i <5;i++){
                puts("wait...");
                sleep(4);
            }
        }
    }
}
