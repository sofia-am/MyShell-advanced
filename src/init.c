#include "init.h"

void init(){
    printf("\n######################## ✽ Sofia's Shell ✽ ########################\n\n");
    return;
}

void set_env(){
    environment.cwd = getcwd(NULL, 0);
    environment.user = getenv("USER");
    uname(&uts);
    environment.hostname = uts.nodename;
    return;
}

void refresh_prompt(){
    char *prompt;
    char *aux;
    prompt = malloc(strlen(environment.user));
    if(environment.cwd != NULL && environment.user != NULL && environment.hostname != NULL){
        strcpy(prompt, environment.user);
        aux = realloc(prompt, malloc_usable_size(prompt)+strlen(environment.hostname)+strlen(environment.cwd)+strlen("@")+strlen(":~$ ")+1);
        if(aux != NULL){
            prompt = aux;
            strcat(prompt, "@");
            strcat(prompt, environment.hostname);
            strcat(prompt,":~");
            strcat(prompt, environment.cwd);
            strcat(prompt, "$");
            //printf("%s", prompt);
            workspace = prompt;
            return;
        }else{
            fprintf(stderr, "Error al reservar memoria\n");
            exit(EXIT_FAILURE);
        }
    }else{
        fprintf(stderr, "Error al resolver entorno\n");
        exit(EXIT_FAILURE);
    }
    //free(aux);
    free(prompt);        
}