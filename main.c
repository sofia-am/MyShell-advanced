#include "src/utils.h"

int main(int argc, char *argv[])
{
    char *stream;
    char **tokens_buff;
    pipe_flag = 0;
    // char** buffer;
    init();
    set_env();
    if (signal(SIGINT, SIG_IGN) == SIG_ERR || signal(SIGTSTP, SIG_IGN) == SIG_ERR || signal(SIGQUIT, SIG_IGN) == SIG_ERR)
    {
        perror("Error al ignorar señales");
        exit(EXIT_FAILURE);
    }

    if (argc > 1)
    {
        read_from_file(argv[1]);
    }

    while (1)
    {
        refresh_prompt();
        printf("%s ", workspace);
        stream = read_line();
        tokens_buff = parser(stream);
        if (tokens == 0)
        {
            continue;
        }
        else if (strcmp(tokens_buff[tokens - 1], "&") == 0)
        {
            tokens--;
            background_exec(tokens_buff);
        }
        else
        {
            // printf("foreground\n");
            for (int i = 0; i < tokens; i++)
            {
                if (strcmp(tokens_buff[i], "|") == 0)
                {
                    pipe_flag = 1;
                }
                else if(strcmp(tokens_buff[i], "<") == 0 || strcmp(tokens_buff[i], ">") == 0){
                    io_flag = 1;                    
                }
            }
            if(pipe_flag) piping(tokens_buff);
            if(io_flag){
                printf("En io redirection\n");
                io_redirection(tokens_buff);
                break;
            }
            else
            {
                interpreter(tokens_buff);
                printf("\n");
            }
        }
    }
}