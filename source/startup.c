#include "startup.h"

void mysh_init(){

    printf("\n######################## ✽ Sofia's Shell ✽ ########################\n\n");

}

char* refresh_prompt(char* user, char* cwd){
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

            return prompt;
        }
    }
    return "error";
}

void parser(char **stream){
    
}