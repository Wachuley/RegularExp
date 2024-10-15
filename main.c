#include "main.h"

TNodo *CreaNodo(const char d[]) {
    TNodo *ptr;

    ptr = (TNodo *)malloc(sizeof(TNodo));
    if (ptr == NULL) {
        printf("ERROR\n");
        exit(1);
    }

    strcpy(ptr->dato, d);
    ptr->sig = ptr->ant = NULL;
    return ptr;
}

void Libera(TLista *lista) {
    TNodo *ptr = lista->inicio, *aux;

    while (ptr != NULL) {
        aux = ptr;
        ptr = ptr->sig;
        free(aux);
    }
}

void Imprime(TLista *lista) {
    TNodo *ptr = lista->inicio;

    printf("Imprimiendo...\n\n");

    while (ptr->sig!= NULL) {
        printf("%s", ptr->dato);
        ptr = ptr->sig;
    }
}

void InsertaFinal(TLista *lista, char d[]) {
    TNodo *nodo = CreaNodo(d);

    if (lista->inicio == NULL)
        lista->inicio = lista->fin = nodo;
    else {
        nodo->ant = lista->fin;
        lista->fin = nodo;
        nodo->ant->sig = nodo;
    }
}

int main() {
    FILE *fptr;
    char string[100], name[40];
    TLista lista;
    lista.inicio = NULL;
    lista.fin = NULL;

    printf("Enter the name of the file: \n");
    scanf("%s", name);
    strcat(name,".txt");

    fptr = fopen(name, "r");
    if (fptr == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    while (fgets(string, sizeof(string), fptr)) {
        InsertaFinal(&lista, string);
    }

    fclose(fptr);

    Imprime(&lista);

    Libera(&lista);
    return 0;
}
