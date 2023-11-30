//
// Created by M on 2023/11/29.
//
#include <stdio.h>
#include <unistd.h>
#include <signal.h>

void timeout(int signal){
    if (signal == SIGALRM) {
        puts("timeout");
        alarm(2);
    }
}

void key_control(int signal){
    if (signal == SIGINT) {
        puts("CTRL_C pressed");
    }
}
int main(int argc, char *argv[]){
    signal(SIGALRM, timeout);
    signal(SIGINT, key_control);
    alarm(2);
    for (int i = 0; i < 3; ++i){
        puts("wait...");
        sleep(100);
    }
    return 0;
}