#include "src/init.h"

int main(){
    char* stream;
    //char** buffer;
    init();
    set_env();
      
    while(1)
    {   refresh_prompt();  
        printf("%s ", workspace);
        stream = read_line();
        integrador(stream);
        printf("\n");
    }
}