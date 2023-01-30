#include "src/utils.h"

int main(int argc, char *argv[])
{
    char *stream;
    char **tokens_buff;
    // char** buffer;
    init();
    set_env();

    if(argc > 1)
    {
        read_from_file(argv[1]);
    }

    while (1)
    {
        refresh_prompt();
        printf("%s ", workspace);
        stream = read_line();
        tokens_buff = parser(stream);

        if(strcmp(tokens_buff[tokens-1],"&") == 0)
        {
            tokens--;
            background_exec(tokens_buff);
        }else{
            //printf("foreground\n");
            interpreter(tokens_buff);

            printf("\n");
        }
    }
}