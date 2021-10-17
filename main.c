#include "source/dependencies.h"

int main(){
    mysh_init();
    char *cwd;
    char *user;
    char *prompt;
    //char *aux;
    char *input;
    int bytes;

    cwd = getcwd(NULL, 0);  //aloca memoria on its own
    user = getenv("USER");

    prompt = refresh_prompt(user, cwd);

    write(STDOUT_FILENO, prompt, strlen(prompt));

    input = malloc(SIZE);
    bytes = read(STDIN_FILENO, input, SIZE); 


    while(bytes != -1){
        parser(input);
    }
/*
    for(int i = 0; i<strlen(input[i]); i++){
        write(STDOUT_FILENO, input[i], SIZE);
    }*/
    
}