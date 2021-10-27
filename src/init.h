#include "interp.h"

typedef struct Env{
    char *user;
    char *cwd;
} env;

env environment;

void init(void);
void set_env(void);
char* refresh_prompt(void);