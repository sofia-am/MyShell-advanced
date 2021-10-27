#include "interp.h"

char* read_line(){
    char *stream = NULL;
    size_t buff = 0;
    stream_size = getline(&stream, &buff, stdin);
    /* getline va a devolver:
    la cant de palabras leidas
    + espacios
    + /n (si encuentra uno)
    + NULL (porque con eso termina el buffer)*/
/*  
    size_t i = 0;
    for(i = 0;i <= (read_c-2); i++){
        printf("%s \n", stream);
    }
*/
    return stream;
}

char** parser(char *stream){
    char *ptr;
    char** aux;
    char *delim = " \t\n";
    tokens = 0;
    char** buff = malloc(sizeof(char*)); //reservo memoria para los strings
    ptr = strtok(stream, delim);
    while (ptr != NULL)
    {
        buff[tokens] = malloc(sizeof(char)*((strlen(ptr))+1));
        aux = realloc(buff, sizeof(char*)*(tokens+1));
        if(aux == NULL){
            fprintf(stderr, "Error de asignación");
            exit(EXIT_FAILURE);
        }else
            buff = aux;

        strcpy(buff[tokens],ptr);
        ptr = strtok(NULL, " \t\n");
        tokens++;
    }
    // for (int i = 0; i <= (tokens-1); i++)
    // {
    //     printf("%s\n", buff[i]);
    // }
    free(stream);
    //tokens -= 1; //saco el NULL
    return buff; //devuelve un buffer de tamaño palabras + 1 -> porque almacena el NULL al final
}
