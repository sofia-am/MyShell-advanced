#include "src/interp.h"
#include "src/init.h"

int main(){
    char* stream;
    char** buffer;

    init();
    set_env();
      
    while(1)
    {   refresh_prompt();  
        printf(" %s ", workspace);
        stream = read_line();
        buffer = parser(stream);
        for(int i = 0; i < tokens; i++){
            printf(" %s\n", buffer[i]);  
        }
    }
}