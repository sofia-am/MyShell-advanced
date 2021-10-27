#include "init.h"

void init(){
    printf("\n######################## ✽ Sofia's Shell ✽ ########################\n\n");
    return;
}

void set_env(){
    environment.cwd = getcwd(NULL, 0);
    environment.user = getenv("USER");
    return;
}

char* refresh_prompt(){
    char *prompt;
    char *aux;
    prompt = malloc(strlen(environment.user));
    if(environment.cwd != NULL && environment.user != NULL){
        strcpy(prompt, environment.user);
        if((aux = realloc(prompt, strlen(environment.cwd)+strlen("@")+strlen(":~ ")+1)) != NULL){
            prompt = aux;
            strcat(prompt, "@");
            strcat(prompt, environment.cwd);
            strcat(prompt,":~ ");
            //printf("%s", prompt);
            return prompt;
        }else{
            fprintf(stderr, "Error al reservar memoria");
            return "error";
        }
    }else{
        fprintf(stderr, "Error al resolver entorno");
        return "error";
    }
    //free(aux);
    free(prompt);        
}