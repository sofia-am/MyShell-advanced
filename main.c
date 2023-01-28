#include "src/utils.h"

int main()
{
    char *stream;
    char **tokens;
    // char** buffer;
    init();
    set_env();

    while (1)
    {
        refresh_prompt();
        printf("%s ", workspace);
        stream = read_line();
        tokens = parser(stream);

        if (tokens != NULL)
        {
            shell_exec(tokens);
        }

        free(tokens);
        free(stream);
        printf("\n");
    }
}