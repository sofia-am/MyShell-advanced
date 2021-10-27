#include "interp.h"

char* read_line(){
    char *stream = NULL;
    size_t buff = 0;
    stream_size = getline(&stream, &buff, stdin);
/*  
    size_t i = 0;
    for(i = 0;i <= (read_c-2); i++){
        printf("%s \n", stream);
    }
*/
    return stream;
}

char** parser(char *stream){
    tokens = 0;
    char* aux;
    char* ptr;
    char* delim = " \t\n";
    char** buffer = malloc(sizeof(char)*stream_size);

    if(buffer == NULL){
        fprintf(stderr, "Fallo al reservar memoria");
        exit(EXIT_FAILURE);
    }

    ptr = strtok(stream, delim);
    while (ptr != NULL)
    {
        //printf("%s\n", ptr);
        buffer[tokens] = ptr;
        ptr = strtok(NULL, delim);
        tokens++;

        if(tokens>=stream_size){
            if(aux = realloc(buffer, malloc_usable_size(buffer)+(sizeof(char)*stream_size)) != NULL){
                aux = buffer;
            }else{
                fprintf(stderr, "Fallo al reservar memoria");
                exit(EXIT_FAILURE);
            }
        }
    }
    free(stream);

    return buffer;
}
