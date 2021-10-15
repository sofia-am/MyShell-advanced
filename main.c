#include "source/startup.h"

int main(){
    mysh_init();
    char *cwd;
    char *user;
    char *prompt;
    char *aux;
    char **input;
    int bytes;

    cwd = getcwd(NULL, 0);  //aloca memoria on its own
    user = getenv("USER");

    prompt = malloc(strlen(user));

    if(cwd != NULL && user != NULL){
        strcpy(prompt, user);
        if((aux = realloc(prompt, strlen(cwd)+strlen("@")+strlen(":~ ")+1)) != NULL){
            prompt = aux;
            strcat(prompt, "@");
            strcat(prompt, cwd);
            strcat(prompt,":~ ");
        }
    }else{
        printf("error al recuperar informacion sobre el entorno");
    }

    write(STDOUT_FILENO, prompt, strlen(prompt));

    bytes = read(STDIN_FILENO, &input, SIZE); 
    while(bytes != -1){

    }

}
