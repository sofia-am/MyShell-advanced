#include "src/interp.h"
#include "src/init.h"

int main(){
    char* stream;
    char** buffer;

    init();
    set_env();
    refresh_prompt();
    stream = read_line();
    buffer = parser(stream);
    for(int i = 0; i < tokens; i++){
        printf("%s\n", buffer[i]);  
    }
}