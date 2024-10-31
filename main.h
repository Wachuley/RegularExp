#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct nodo {
    struct nodo *sig;
    struct nodo *ant;
    char dato[20];
} TNodo;

#endif
