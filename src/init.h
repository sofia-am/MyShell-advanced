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