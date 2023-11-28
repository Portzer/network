//
// Created by M on 2023/11/28.
//

#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
int main(int argc, char *argv[]){
    int status;
    pid_t pid = fork();
    if (pid == 0) {
        sleep(15);
        return 24;
    }else{
        while (!waitpid(-1, &status, WNOHANG)) {
            sleep(3);
            puts("sleep 3 sec");
        }
        if(WIFEXITED(status))
            printf("Child process send %d\n", WEXITSTATUS(status));
    }
    return 0;
}
