#include "source/startup.h"

int main(){
    mysh_init();
    char *cwd;
    char *user;
    char **input;
    int bytes;

    cwd = getcwd(NULL, 0);  //alloca memoria on its own
    user = getenv("USER");

    if(cwd != NULL && user != NULL){
        printf("%s @ %s \n",user, cwd);
    }else{
        printf("error al recuperar informacion sobre el entorno");
    }
   
    bytes = read(STDIN_FILENO, &input, SIZE); 
    while(bytes != -1){

    }
}
