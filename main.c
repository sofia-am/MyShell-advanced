#include "src/interp.h"

int main(){
    char* stream;
    char** buffer;

    stream = read_line();
    buffer = parser(stream);
    for(int i = 0; i < tokens; i++){
        printf("%s\n", buffer[i]);  
    }
}