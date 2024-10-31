#include "main.h"

void Libera(TNodo *cab){
    TNodo *ptr = cab, *aux;

    while (ptr != NULL){
        aux = ptr;
        ptr = ptr->sig;
        free(aux);
    }
}

TNodo *CreaNodo(char str[]){ //crea nodos simples
	TNodo *ptr=(TNodo*)malloc(sizeof(TNodo));
	if(ptr){
        strcpy(ptr->dato, str);
        ptr->sig=ptr->ant=NULL;
		return ptr;
	}
	printf("Error al reservar memoria");
	exit(0);
}

void InsertaFinal(TNodo **cab, char string[]){
	TNodo *nodo=CreaNodo(string);

	if(*cab==NULL){
        *cab=nodo;
	} else{
	    TNodo *aux=cab;
        while(aux->sig!=NULL)
            aux=aux->sig;

	    aux->sig=nodo;
	    nodo->ant=aux;
	}
}

void Imprime(TNodo *cab){
    TNodo *ptr = cab;
    int i;

    while (ptr->sig!= NULL){
        printf("%s\n", ptr->dato);
        ptr = ptr->sig;
    }
}

void Paso1(TNodo *cab){
    TNodo *ptr=cab;
    TNodo *eliminar;
    int i;

    while(ptr->sig!=NULL){
        if(ptr->dato[0]==ptr->sig->dato[0]){
            strcat(ptr->dato,"|");
            strcat(ptr->dato,&ptr->sig->dato[3]);

            eliminar=ptr->sig;
            ptr->sig=ptr->sig->sig;
            free(eliminar);
        }
        ptr=ptr->sig;
    }
}

void Paso2(TNodo *cab){
    TNodo *ptr=cab;
    char letra, aux[15], aux2;
    char cad[20]="", aux3[20];
    int i, j;

    while(ptr!=NULL){
        letra=ptr->dato[0];
        i=1;


        while(ptr->dato[i]!=letra&&i<strlen(ptr->dato)){
            i++;
        }
        if(i<strlen(ptr->dato)){
            strcpy(aux, &ptr->dato[i+2]);
            aux2=ptr->dato[i-1];

            strcpy(cad, "");
            cad[0]=letra;
            cad[1]='-';
            cad[2]='>';
            cad[3]='{';
            cad[4]=aux2;
            cad[5]='}';
            cad[6]='\0';
            cad[0]=letra;
            strcat(cad, &aux);
            strcpy(ptr->dato, &cad);
        }
        ptr=ptr->sig;
    }
}

void Paso3(TNodo *ptr){
    char letra=ptr->sig->dato[0];
    int i;

    if(ptr->sig!=NULL){
        printf("(");
        for(i=3; i<strlen(ptr->dato); i++){
            if(ptr->dato[i]==letra){
                Paso3(ptr->sig);
                i++;
            }
            printf("%c",ptr->dato[i]);
        }
        printf(")");
    }
    if(ptr->sig==NULL){
        printf(")");
        return;
    }
}

int main(){
    FILE *fptr;
    char string[20], name[40];
    TNodo *cab=NULL;

    printf("Enter the name of the file: \n");
    scanf("%s", name);
    strcat(name,".txt");

    fptr = fopen(name, "r");
    if (fptr == NULL) {
        printf("No se pudo abrir el archivo.\n");
        return 1;
    }

    while (fgets(string, sizeof(string), fptr)){
        string[strlen(string)-1]='\0';
        InsertaFinal(&cab, string);
    }
    printf("Archivo:\n");
    Imprime(cab);

    printf("Paso 1:\n");
    Paso1(cab);
    Paso1(cab);
    Imprime(cab);

    printf("Paso 2:\n");
    Paso2(cab);
    Imprime(cab);

    printf("Paso 3:\n");
    printf("S->");
    Paso3(cab);

    fclose(fptr);
    Libera(&cab);

    return(0);
}
