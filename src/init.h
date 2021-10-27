#include "interp.h"

typedef struct Env{
    char *user;
    char *cwd;
} env;

env environment;

void init(void);
void set_env(void);
void refresh_prompt(void);