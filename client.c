#include "globals.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "protocole.h"

extern int done;
extern int sockfd;

pthread_t threads[2];
pthread_attr_t attr;

int main()
{
    start_server(threads, attr);
    // Run the sender and receiver threads
    pthread_create(&threads[0], &attr, sender, NULL);
    pthread_create(&threads[1], &attr, receiver, NULL);

    // Wait until done is TRUE then exit program
    while (!done)
        ;

    close(sockfd);
    return OK;
}