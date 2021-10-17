#include "source/dependencies.h"

int main(){
    mysh_init();
    char *cwd;
    char *user;
    //char *aux;
    char *input;
    int bytes;

    cwd = getcwd(NULL, 0);  //aloca memoria on its own
    user = getenv("USER");

    refresh_prompt(user, cwd);

    input = malloc(SIZE);
    bytes = read(STDIN_FILENO, input, SIZE); 

    while(bytes != -1){
        parser(input);
        refresh_prompt(user, cwd);
    }
/*
    for(int i = 0; i<strlen(input[i]); i++){
        write(STDOUT_FILENO, input[i], SIZE);
    }*/
    
}