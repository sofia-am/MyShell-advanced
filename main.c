#include "src/utils.h"

int main(int argc, char *argv[])
{
    char *stream;
    char **tokens;
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
        tokens = parser(stream);

        interpreter(tokens);

        printf("\n");
    }
}