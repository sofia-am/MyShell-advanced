#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define SIZE 1024

void mysh_init();
char* refresh_prompt(char* user, char* cwd);
void parser(char **stream);
