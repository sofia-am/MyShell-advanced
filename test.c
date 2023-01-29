#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/utsname.h>

int main()
{
    /* //el size_t no admite valores negativos
    ssize_t read_c; //caracteres leidos
    char *stream = NULL;
    size_t size = 0;
    read_c = getline(&stream, &size, stdin);
    //getline alloca memoria por nosotros
    /*
    size_t i = 0;
    for(i = 0;i <= (read_c-2); i++){
        printf("%s \n", stream);
    }
*/
/*
    char *ptr;
    char *aux = stream;
    char **aux2;
    char *delim = " \t\n";
    int tokens = 0;
    char** buff = malloc(sizeof(char*));
    ptr = strtok(stream, delim);
    buff[tokens] = strdup(ptr);
    while (ptr != NULL)
    {
        //printf("%s\n", buff[0]);
        buff = realloc(buff, sizeof(char*)*(tokens+1));
        if(buff == NULL){
            printf("error");
        }
        // if (aux2 != NULL)
        // {
        //     buff = aux2;
        // }
        buff[tokens] = malloc(sizeof(char)*((strlen(ptr))+1));
        strcpy(buff[tokens],ptr);
        //printf("%s", buff[tokens]);
        ptr = strtok(NULL, " \t\n");
        tokens++;
    }

    for (int i = 0; i < (tokens); i++)
    {
        //printf("%s\n", buff[i]);
    }
    free(stream);
    
    if(strcmp(buff[0],"echo")==0){
        char* chr;
        char* env_var;
        char* echoed;
        chr = strchr(buff[1], '$');
        echoed = malloc(sizeof(char*)*tokens);
        if(chr != NULL){
            env_var = getenv((chr+1));//me desplazo un lugar para "saltar" el $
            if(env_var != NULL) printf(" %s\n ", env_var);
            else printf("   ");
        }else{
            for(int j = 1; j<tokens; j++){
                echoed = strcat(echoed, buff[j]);
                echoed = strcat(echoed, " ");
            }
            printf("%s\n", echoed);
        }
        free(echoed);
    }

 */

    printf("Hello World!\n");
}