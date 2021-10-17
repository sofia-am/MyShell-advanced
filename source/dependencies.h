#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 4096
#define CLR "\033[1;1H\033[2J"

#define clrscr() write(STDOUT_FILENO, CLR, strlen(CLR))
//printf("\033[1;1H\033[2J")

void mysh_init();
void refresh_prompt(char* user, char* cwd);
void parser(char *stream);
//void resize(char *input);