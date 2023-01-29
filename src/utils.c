#include "utils.h"

void init()
{
    printf("\n*---------------------------------------- ✽ Sofia's Shell ✽ ----------------------------------------*\n");
    printf("                                             (づ｡◕‿‿◕｡)づ\n\n✽ Este trabajo se realizo dentro del contexto de la materia Sistemas Operativos 1\n✽ Si necesitás ayuda, escribí el comando help\n✽ Linux masterrace\n\n");
    return;
}

void set_env()
{
    environment.cwd = getenv("PWD");
    environment.user = getenv("USER");
    uname(&uts);
    environment.hostname = uts.nodename;
    return;
}

void refresh_prompt()
{
    char *prompt;
    char *aux;
    // aloco memoria para el string del user
    prompt = malloc(strlen(environment.user));

    if (environment.cwd != NULL && environment.user != NULL && environment.hostname != NULL)
    {
        strcpy(prompt, environment.user);
        // aloco más memoria para todo el string que se va a imprimir en pantalla
        aux = realloc(prompt, malloc_usable_size(prompt) + strlen(environment.hostname) + strlen(environment.cwd) + strlen("@") + strlen(":~$ ") + 1);
        if (aux != NULL)
        {
            prompt = aux;
            // concateno a user el @, el hostname, etc
            strcat(prompt, "@");
            strcat(prompt, environment.hostname);
            strcat(prompt, ":~");
            strcat(prompt, getenv("PWD"));
            strcat(prompt, "$");
            // printf("%s", prompt);
            //  workspace es una variable global
            workspace = prompt;
            return;
        }
        else
        {
            fprintf(stderr, "Error al reservar memoria\n");
            exit(EXIT_FAILURE);
        }
    }
    else
    {
        fprintf(stderr, "Error al resolver entorno\n");
        exit(EXIT_FAILURE);
    }
    // free(aux);
    free(prompt);
}

char *read_line()
{
    char *stream = NULL;
    size_t buff = 0;
    stream_size = getline(&stream, &buff, stdin);
    /* getline va a devolver:
    la cant de palabras leidas
    + espacios
    + /n (si encuentra uno)
    + NULL (porque con eso termina el buffer)*/
    /*
        size_t i = 0;
        for(i = 0;i <= (read_c-2); i++){
            printf("%s \n", stream);
        }
    */
    return stream;
}

char **parser(char *stream)
{
    char *ptr;
    char **aux;
    char *delim = " \t\n";
    tokens = 0;
    char **buff = malloc(sizeof(char *)); // reservo memoria para los strings
    ptr = strtok(stream, delim);          /*This function returns a pointer to the first token found in the string.
             A null pointer is returned if there are no tokens left to retrieve.
             */
    while (ptr != NULL)
    {
        buff[tokens] = malloc(sizeof(char) * ((strlen(ptr)) + 1));
        aux = realloc(buff, malloc_usable_size(buff) + sizeof(char *) * (tokens + 1));
        if (aux == NULL)
        {
            fprintf(stderr, "Error de asignación");
            exit(EXIT_FAILURE);
        }
        else
            buff = aux;

        strcpy(buff[tokens], ptr);
        ptr = strtok(NULL, " \t\n");
        tokens++;
    }
    // for (int i = 0; i <= (tokens-1); i++)
    // {
    //     printf("%s\n", buff[i]);
    // }
    free(stream);
    // tokens -= 1; //saco el NULL
    return buff; // devuelve un buffer de tamaño palabras + 1 -> porque almacena el NULL al final
}

void interpreter(char **commands)
{
    if (strcmp(commands[0], "clr") == 0)
        printf("%s", CLR); // limpia la pantalla
    else if (strcmp(commands[0], "echo") == 0)
        echo_interp(commands);
    else if (strcmp(commands[0], "cd") == 0)
        cd_interp(commands);
    else if (strcmp(commands[0], "quit") == 0)
        exit(EXIT_SUCCESS);
    else if (strcmp(commands[0], "help") == 0)
        help_interp();
    else
    {
        launch_program(commands);
    }
}

void launch_program(char **commands)
{
    /* la razón por la que necesito crear un nuevo proceso es que la funcion exec, que es la que va a ejecutar el programa que se le mande como argumento, reemplaza mi programa actual por el que se le pasa como argumento, si hiciera esto en el mismo proceso, moriría mi shell original. Se reemplaza a si mismo con otra imagen de programa */
    // with L: comma separated values
    // with V: vector (i.e array of strings)
    // with P: include normal search path for executable
    // sin la P: busca el programa en la current folder
    // tiene que terminar con un NULL !!!!!!!!!!!!!!!!

    pid_t pid = fork();
    int status;

    switch (pid)
    {
    case -1:
        perror("Fallo al hacer fork");
    case 0:
        if(commands[0][0] == '.'){
            // caso donde el programa se encuentra en el mismo directorio
            execv(commands[0], commands);
            perror("Error al ejecutar el programa");
        }
        // sino lo busca en $PATH
        execvp(commands[0], commands);
        perror("Error al ejecutar programa");
        break;

    default:
        do{
            waitpid(pid, &status, WUNTRACED);
        }while(!WIFEXITED(status) && !WIFSIGNALED(status));
    }
}

void help_interp()
{
    printf("\n oh hiiii, bienvenido/a a mi shell!\nPara utilizarla, ingrese los comandos que desee, separados por espacios.\nLos comandos disponibles son:\nclr: limpia la pantalla\necho: imprime en pantalla el string ingresado\ncd: cambia el directorio actual\necho $VARIABLE: imprime en pantalla el valor de la variable de entorno ingresada\nquit: cierra la shell\n");
}

void echo_interp(char **commands)
{
    char *chr; // puntero que nos va a devolver la posicion del string donde encuentre $
    char *env_var;
    char *echoed;
    chr = strchr(commands[1], '$'); // returns a pointer to the first occurrence of the character
    echoed = malloc(sizeof(char *) * tokens);
    if (chr != NULL)
    {
        env_var = getenv((chr + 1)); // me desplazo un lugar para "saltar" el $
        if (env_var != NULL)
            printf(" %s\n ", env_var);
        else
            printf("   ");
    }
    else
    { // si no encuentra un $ (es decir, no es una variable de entorno) imprimo la palabra ingresada
        for (int j = 1; j < tokens; j++)
        {
            echoed = strcat(echoed, commands[j]); // appends las palabras
            echoed = strcat(echoed, " ");
        }
        printf("%s\n", echoed);
        free(echoed);
    }
}

void cd_interp(char **commands)
{
    char *chr;
    char *orig_dir = getenv("PWD");
    if ((chr = malloc(sizeof(char *) * tokens)) != NULL)
    {
        for (int j = 1; j < tokens; j++)
        {
            chr = strcat(chr, commands[j]); // appends las palabras
        }
        /* vamos al directorio base */
        if (commands[1] == NULL)
        {
            if (setenv("PWD", getenv("HOME"), 1) == -1)
            {
                perror("Error al cambiar de directorio");
                exit(EXIT_FAILURE);
            }
            return;
        }
        /* retornamos al directorio anterior */
        else if (strcmp(commands[1], "-") == 0)
        {
            if (chdir(getenv("OLDPWD")) == -1)
            {
                perror("Error al cambiar de directorio");
                return;
            }
            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", getenv("OLDPWD"), 1);
            return;
        }
        /* caso donde queremos ir al directorio padre */
        else if (strcmp(commands[1], "..") == 0)
        {
            char *parent_directory;
            char *tail;
            parent_directory = getenv("PWD");
            tail = strrchr(getenv("PWD"), '/');
            int len = strlen(parent_directory);
            parent_directory[len - strlen(tail)] = '\0';
            if (chdir(parent_directory) == -1)
            {
                perror("Error al cambiar de directorio");
                return;
            }

            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", parent_directory, 1);
            return;
        }
        /* caso donde queremos ir a un directorio dentro del directorio actual */
        else if (commands[1][0] != '/')
        {
            char *full_dir = malloc(sizeof(orig_dir) + sizeof(chr) + sizeof(char) * 1024);
            strcpy(full_dir, orig_dir);
            strcat(full_dir, "/");
            strcat(full_dir, chr);
            if (chdir(full_dir) == -1)
            {
                perror("Directorio inválido");
                return;
            }
            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", full_dir, 1);
            return;
        }
        else
        {
            if (chdir(chr) == -1)
            {
                perror("Error al cambiar de directorio");
                return;
            }

            setenv("OLDPWD", getenv("PWD"), 1);
            setenv("PWD", chr, 1);
            return;
        }
    }
    else
    {
        perror("Error al allocar memoria para string");
        exit(EXIT_FAILURE);
    }
}