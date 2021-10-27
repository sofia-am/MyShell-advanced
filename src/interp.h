#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <malloc.h>
#include <sys/utsname.h>

struct utsname uts;
//el size_t y ssize_t no admiten valores negativos
ssize_t stream_size; //caracteres leidos
size_t tokens;
char* read_line(void);
char** parser(char* stream);