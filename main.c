#include "source/dependencies.h"

int main(){
    mysh_init();
    //char *aux;
    char *input;
    int bytes;

    set_env();
    refresh_prompt();

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