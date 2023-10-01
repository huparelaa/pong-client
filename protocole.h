#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> //para la estructura de la direccion
#include "game_status.h"

#ifndef PROTOCOLE_H
#define PROTOCOLE_H


void stablish_communication(int sockfd, game_status *game, int commands[5], struct sockaddr_in addr);


#endif