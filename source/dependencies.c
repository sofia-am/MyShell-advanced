#include "dependencies.h"

void mysh_init(){
    printf("\n######################## ✽ Sofia's Shell ✽ ########################\n\n");
}

void refresh_prompt(char* user, char* cwd){
    char *prompt;
    char *aux;

    prompt = malloc(strlen(user));

    if(cwd != NULL && user != NULL){
        strcpy(prompt, user);
        if((aux = realloc(prompt, strlen(cwd)+strlen("@")+strlen(":~ ")+1)) != NULL){
            prompt = aux;
            strcat(prompt, "@");
            strcat(prompt, cwd);
            strcat(prompt,":~ ");

            write(STDOUT_FILENO, prompt, strlen(prompt));
            return;
        }
    }
    write(STDOUT_FILENO, "error", strlen("error"));
    //free(aux);
    free(prompt);
}

void parser(char *stream){
    char *aux;

    while(stream != NULL){
        aux = strtok(stream, " \t\n");
        if(strcmp(aux, "cd") == 0){
            aux = strtok(NULL, " \t\n");
            //llama a funcion para camiar de directorio
        }
        else if(strcmp(aux, "clr") == 0){
            clrscr();
        }
    }

}