//
// Created by M on 2023/11/26.
//
#include <stdio.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    int i;
    struct hostent *host;
    if (argc != 2) {
        printf("Usage: %s <address> \n", argv[0]);
        exit(1);
    }
    host = gethostbyname(argv[1]);
    printf("official name is %s\n", host->h_name);
    for(i=0; host->h_aliases[i]; i++) {
        printf("Address alias is %s\n", host->h_aliases[i]);
    }
    printf("Address type is %s\n", (host->h_addrtype == AF_INET) ? "AF_NET" : "AF_NET6");
    for (int j = 0; host->h_addr_list[j]; j++) {
        printf("IP address is %s \n", inet_ntoa(*(struct in_addr *) host->h_addr_list[j]));
        return 0;
    }
}