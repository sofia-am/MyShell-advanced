#ifndef INTERP_DOT_H
#define INTERP_DOT_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/utsname.h>
#include <sys/types.h>
#include <sys/stat.h>

#define CLR "\033[1;1H\033[2J"

typedef struct Env{
    char *user;
    char *cwd;
    char *hostname;
} env;

env environment;
char* workspace;

struct utsname uts;
//el size_t y ssize_t no admiten valores negativos
ssize_t stream_size; //caracteres leidos
size_t tokens;
char* read_line(void);
/* recorre el buffer de entrada, y tokeniza cada uno de las 
palabras que se ingresan, almacenándolas en un arreglo buff
*/
char** parser(char* stream);
/* parsea cada uno de los tokens y si es un comando, llama a la función correspondiente
*/
void interpreter(char** commands);
/*llama a la funcion parser que tokeniza el stream de entrada y
 recorre el buffer de tokens, llamando a interpreter para saber 
 si corresponde a algun comando válido*/
void integrador(char* stream);
/* ejecuta el comando echo*/
void echo_interp(char** commands);
/* ejecuta el comando cd */
void cd_interp(char** commands);

void init(void);
void set_env(void);
void refresh_prompt(void);

#endif
