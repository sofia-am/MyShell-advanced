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

struct builtin{
    char* name;
    void (*func)(char**);
};

struct builtin builtins[] = {
    {"echo", echo_interp},
    {"cd", cd_interp},
    {"clr", clr_interp},
    {"quit", quit_interp},
    {"help", help_interp}    
};

env environment;
char* workspace;

struct utsname uts;
//el size_t y ssize_t no admiten valores negativos
ssize_t stream_size; //caracteres leidos
size_t tokens;
char* read_line(void);
char** parser(char* stream);
void interpreter(char** commands);

void integrador(char* stream);
void echo_interp(char** commands);
void cd_interp(char** commands);
void help_interp(void);
void quit_interp(void);
void clr_interp(void);

void shell_exec(char** commands);

void init(void);
void set_env(void);
void refresh_prompt(void);

#endif
