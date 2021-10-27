#include "src/interp.h"
#include "src/init.h"

int main(){
    char* stream;
    char** buffer;
    char* workspace;

    init();
    set_env();
    workspace = refresh_prompt();
    while(1)
    {   printf("%s", workspace);
        stream = read_line();
        buffer = parser(stream);
        for(int i = 0; i < tokens; i++){
            printf("%s\n", buffer[i]);  
    }}
}