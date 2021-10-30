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
        aux = realloc(buff, malloc_usable_size(buff)+sizeof(char*)*(tokens+1));
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

void interpreter(char** commands){
    if(strcmp(commands[0], "clr") == 0){
        printf("%s", CLR);
    }else if(strcmp(commands[0],"echo") == 0){
        echo_interp(commands);
    }else if(strcmp(commands[0],"cd") == 0){
        printf("%s", "encontre un cd!\n");
    }else if(strcmp(commands[0], "quit") == 0){
        //printf("%s", "encontre un quit!\n");
        exit(EXIT_SUCCESS);
    }
}

void integrador(char* stream){
    char** buffer;
    buffer = parser(stream);
    if(buffer != NULL && tokens>=1){
        interpreter(buffer);
    }
}
/*toma el buffer de palabras parseadas y llama al interpeter que lee el 1er token y 
se fija si corresponde a alguna funcionalidad */

void echo_interp(char** commands){
    char* chr; //puntero que nos va a devolver la posicion del string donde encuentre $
    char* env_var;
    char* echoed;
    chr = strchr(commands[1], '$');
    echoed = malloc(sizeof(char*)*tokens);
    if(chr != NULL){
        env_var = getenv((chr+1));//me desplazo un lugar para "saltar" el $
        if(env_var != NULL) printf(" %s\n ", env_var);
        else printf("   ");
    }else{
        for(int j = 1; j<tokens; j++){
            echoed = strcat(echoed, commands[j]); //appends las palabras
            echoed = strcat(echoed, " ");
        }
        printf("%s\n", echoed);
        free(echoed);
    }
}
 
