#ifndef PROTOCOLE_H
#define PROTOCOLE_H
#include "globals.h"

void *sender();
void *receiver();
void start_server(pthread_t threads[2], pthread_attr_t attr);
void init_game();

#endif // PROTOCOLE_H