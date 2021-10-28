#ifndef INIT_DOT_H
#define INIT_DOT_H
#include "interp.h"

typedef struct Env{
    char *user;
    char *cwd;
    char *hostname;
} env;

env environment;
char* workspace;

void init(void);
void set_env(void);
void refresh_prompt(void);

#endif /*INIT_DOT_H*/