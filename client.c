#include "globals.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <netdb.h>
int done = FALSE;
int sockfd;

void *sender();
void *receiver();
pthread_mutex_t mutexsum = PTHREAD_MUTEX_INITIALIZER;

char send_buffer[BUF_SIZE];
char recv_buffer[BUF_SIZE + USERNAME_LEN];
char username[USERNAME_LEN];
int main()
{
    bzero(send_buffer, BUF_SIZE);
    bzero(recv_buffer, BUF_SIZE + USERNAME_LEN);

    int portnum = PORT;

    // user name
    printf("Ingresa tu nombre de usuario: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strlen(username) - 1] = '\0';

    // ip
    char ip[16];
    // localhost
    strcpy(ip, IP);
    printf("IP: %s\n", ip);

    struct sockaddr_in server_addr;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    if (sockfd == SYSERR)
    {
        close(sockfd);
        perror("Error creating socket");
        exit(EXIT_FAILURE);
    }
    // allow server to resolve hostnames or use ip's
    struct hostent *server_host;
    server_host = gethostbyname(IP);
    server_addr.sin_family = AF_INET;      // IPv4
    server_addr.sin_port = htons(portnum); // port
    server_addr.sin_addr = *((struct in_addr *)server_host->h_addr);

    if(connect(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SYSERR){
        perror("Error connecting to server");
        exit(EXIT_FAILURE);
    }

    printf("Connected to server\n");

    strcpy(send_buffer, username);
    if(send(sockfd, send_buffer, strlen(send_buffer), 0) == SYSERR){
        perror("Error sending username to server");
        exit(EXIT_FAILURE);
    }

     // create threads
    // Thread 1: takes in user input and sends out messages
    // Thread 2: listens for messages that are comming in from the server and prints them to screen
    //  Set up threads
    pthread_t threads[2];
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    // Run the sender and receiver threads
    pthread_create(&threads[0], &attr, sender, NULL);
    pthread_create(&threads[1], &attr, receiver, NULL);

    // Wait until done is TRUE then exit program
    while (!done)
        ;

    close(sockfd);
    return OK;
}

void *sender()
{
    while (1)
    {
        bzero(send_buffer, BUF_SIZE);
        fgets(send_buffer, BUF_SIZE, stdin);

        // send message to server
        if (send(sockfd, send_buffer, strlen(send_buffer), 0) == SYSERR)
        {
            perror("send");
            done = TRUE;
            pthread_mutex_destroy(&mutexsum);
            pthread_exit(NULL);
        }

        // Check for quitinge
        if (strcmp(send_buffer, CLOSE) == 0 || strcmp(send_buffer, EXIT) == 0)
        {
            done = TRUE;
            pthread_mutex_destroy(&mutexsum);
            pthread_exit(NULL);
        }

        pthread_mutex_unlock(&mutexsum);
    }
}

void *receiver()
{
    int nbytes;

    while (1)
    {
        bzero(recv_buffer, BUF_SIZE);
        // Receive messages from server
        if ((nbytes = recv(sockfd, recv_buffer, BUF_SIZE - 1, 0)) == SYSERR)
        {
            perror("recv");
            done = TRUE;
            pthread_mutex_destroy(&mutexsum);
            pthread_exit(NULL);
        }

        recv_buffer[nbytes] = '\0';
        if (strcmp(ERROR, recv_buffer) == 0)
        {
            printf("Error: The username %s is already taken.\n", send_buffer);
            done = TRUE;
            pthread_mutex_destroy(&mutexsum);
            pthread_exit(NULL);
        }
        else
        {
            printf("%s", recv_buffer);
            pthread_mutex_unlock(&mutexsum);
        }
    }
}
