#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>

ssize_t stream_size; //caracteres leidos
size_t tokens;
char* read_line();
char** parser(char* stream);