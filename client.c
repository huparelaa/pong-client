#include "globals.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
#include "protocole.h"
#include "pong.h"

extern int done;
extern int sockfd;
extern int in_game;
pthread_t threads[3];
pthread_attr_t attr;

void *game()
{
    while (!done)
    {
        if (in_game)
        {
            pong_init();
        }
    }
}

int main()
{
    start_server(threads, attr);
    // Run the sender and receiver threads
    pthread_create(&threads[0], &attr, sender, NULL);
    pthread_create(&threads[1], &attr, receiver, NULL);
    pthread_create(&threads[2], &attr, game, NULL);
    // Wait until done is TRUE then exit program
    while (!done)
        ;

    close(sockfd);
    return OK;
}