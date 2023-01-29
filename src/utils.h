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
#include <sys/wait.h>

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

/**
 * @brief Lee la entrada del usuario y la devuelve como un buffer.
 *
 * @return buffer con la entrada del usuario.
 */
char* read_line(void);
/**
 * @brief Recorre el buffer que se le pasa como parámetro y devuelve un arreglo donde cada elemento es un token.
 *
 * @param stream
 * @return arreglo de tokens.
 */
char** parser(char* stream);
void interpreter(char** commands);

void launch_program(char** commands);
void echo_interp(char** commands);
void cd_interp(char** commands);
void help_interp(void);

void init(void);
/**
 * @brief  Setea las variables de entorno CWD, USER y HOSTNAME.
 * 
 */
void set_env(void);

/**
 * @brief Actualiza el prompt con el usuario, el hostname y el directorio actual.
 * 
 */
void refresh_prompt(void);

int num_builtins(void);

#endif
