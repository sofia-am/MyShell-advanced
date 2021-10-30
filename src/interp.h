#ifndef INTERP_DOT_H
#define INTERP_DOT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/utsname.h>

#define CLR "\033[1;1H\033[2J"

struct utsname uts;
//el size_t y ssize_t no admiten valores negativos
ssize_t stream_size; //caracteres leidos
size_t tokens;
char* read_line(void);
char** parser(char* stream);
void interpreter(char** commands);
void integrador(char* stream);
void echo_interp(char** commands);


#endif
