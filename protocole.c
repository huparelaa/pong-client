#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h> //para la estructura de la direccion
#include "game_status.h"
#include "protocole.h"

char *interpret_command(int command_index);

void stablish_communication(int sockfd, game_status *game, int commands[5], struct sockaddr_in addr)
{
    for (int i = 0; i < 5; i++)
    {
        if (commands[i] != 0)
        {
            char *command = interpret_command(i);
            sendto(sockfd, command, sizeof(command), 0, (struct sockaddr *)&addr, sizeof(addr));
        }
    }
    socklen_t addr_len = sizeof(addr);
    recvfrom(sockfd, game, sizeof(game), 0, (struct sockaddr *)&addr, &addr_len);
}

// función para interpretar comandos y si es commands[0]==1 devolver el string "UP1"
//  commands description
/*
commands[0] - up1
commands[1] - down1
commands[2] - up2
commands[3] - down2
commands[4] - start
commands[5] - exit

*/

char *interpret_command(int command_index)
{
    if (command_index == 0)
    {
        return "UP1";
    }
    else if (command_index == 1)
    {
        return "DOWN1";
    }
    else if (command_index == 2)
    {
        return "UP2";
    }
    else if (command_index == 3)
    {
        return "DOWN2";
    }
    else if (command_index == 4)
    {
        return "START";
    }
    else if (command_index == 5)
    {
        return "EXIT";
    }
    else
    {
        return "ERROR";
    }
}