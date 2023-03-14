#include "utils.h"

void init()
{
    job_id = 0;
    printf("\n*---------------------------------------- ✽ \033[33;1mSofia's Shell\033[0m ✽ ----------------------------------------*\n");
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
        char user[100] = "\033[0;32m";
        strcat(user, environment.user);
        strcpy(prompt, user);
        // aloco más memoria para todo el string que se va a imprimir en pantalla
        aux = realloc(prompt, malloc_usable_size(prompt) + strlen(environment.hostname) + strlen(environment.cwd) + strlen("@") + strlen(":~$ ") + 1);
        if (aux != NULL)
        {
            prompt = aux;
            // concateno a user el @, el hostname, etc
            strcat(prompt, ("@"));
            strcat(prompt, environment.hostname);
            strcat(prompt, "\033[33;1m:~");
            strcat(prompt, getenv("PWD"));
            strcat(prompt, "\033[0m$");
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
    /*   for (int i = 0; i <= (tokens-1); i++)
        {
             printf("%s\n", buff[i]);
        }  */
    // free(stream); // con el batchfile se me explotaba??
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
    {
        printf("\nok byeeeeeeee    ଘ(੭*ˊᵕˋ)੭*☆ﾟ. * ･ ｡ﾟ\n");
        exit(EXIT_SUCCESS);
    }
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
    int wstatus;

    switch (pid)
    {
    case -1:
        perror("Fallo al hacer fork");
    case 0:
        signal(SIGINT, SIG_DFL);
        signal(SIGQUIT, SIG_DFL);
        signal(SIGTSTP, stop_handler);

        if (commands[0][0] == '.')
        {
            // caso donde el programa se encuentra en el mismo directorio
            execv(commands[0], commands);
            perror("Error al ejecutar el programa");
            break;
        }
        // sino lo busca en $PATH
        execvp(commands[0], commands);
        perror("Error al ejecutar programa");
        break;

    default:
        waitpid(-1, &wstatus, WUNTRACED);
        if (WIFSTOPPED(wstatus))
        {
            sleeping_bois++;
            printf("[%d] + %d suspended", sleeping_bois, pid);
        }
        else if (WIFCONTINUED(wstatus))
        {
            sleeping_bois--;
            printf("[%d] + %d continued", sleeping_bois, pid);
        }
        return;
    }
}

void help_interp()
{
    printf("\n Bienvenido/a a mi shell!\nPara utilizarla, ingrese los comandos que desee, separados por espacios.\nLos comandos disponibles son:\n\033[0;35m✽\033[0m clr: limpia la pantalla\n\033[0;35m✽\033[0m echo: imprime en pantalla el string ingresado\n\033[0;35m✽\033[0m cd: cambia el directorio actual\n\033[0;35m✽\033[0m echo $VARIABLE: imprime en pantalla el valor de la variable de entorno ingresada\n\033[0;35m✽\033[0m quit: cierra la shell\n");
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

void read_from_file(char *file_name)
{

    printf("Recibí un batchfile: %s\n", file_name);
    FILE *fp;
    char line[1024];
    char **tokens;
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        perror("Error al abrir el archivo");
        exit(EXIT_FAILURE);
    }
    printf("Abriendo el archivo...\n");
    while (fgets(line, sizeof(line), fp) != NULL)
    {
        printf("Leyendo linea: %s", line);
        tokens = parser(line);
        interpreter(tokens);
    }
    // free(tokens);
    fclose(fp);
    exit(EXIT_SUCCESS);
}

void background_exec(char **commands)
{
    pid_t pid;
    int status;
    int null_fd = open("/dev/null", O_WRONLY);

    int *job_id = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    if (job_id == MAP_FAILED) {
        perror("Error al crear espacio de memoria compartida");
        exit(EXIT_FAILURE);
    }

    job_id[0] = 0;

    pid = fork();

    switch (pid)
    {
    case -1:
        perror("Error al crear proceso");
        break;
    case 0:
        (job_id[0])++; 
        printf("[%d] %d\n", job_id[0], getpid());
        dup2(null_fd, STDOUT_FILENO);
        dup2(null_fd, STDERR_FILENO);
        close(null_fd);               
        interpreter(commands);        
        exit(EXIT_SUCCESS);
    default:
        waitpid(-1, &status, WNOHANG);
        sleep(1);
        printf("[%d] + %d done\n", job_id[0], pid);
        (job_id[0])--;
        munmap(job_id, sizeof(int));
    }
}

void stop_handler(int signum)
{
    printf("handler");
    sleeping_bois++;
    pause();
}

void recursive_piping(char ***programs, int pos, int in_fd)
{
    pid_t pid;
    if (programs[pos + 1] == NULL) // ultimo command
    {
        int pid = fork();
        if (pid == -1)
        {
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        }
        // tuve que hacer otro fork aca porque sino con la ejecución de execvp moría el proceso padre, ya que era reemplazado por la imagen nueva
        else if (pid == 0)
        {
            redirect(in_fd, STDIN_FILENO);
            execvp(programs[pos][0], programs[pos]);
            perror("Error al ejecutar ultimo programa");
            exit(EXIT_FAILURE);
        }
        else
        {
            int status;
            waitpid(pid, &status, 0);
            return;
        }
    }
    else
    {
        int fd[2];
        // creo el pipe
        if (pipe(fd) == -1)
        {
            perror("Error al crear pipe");
            exit(EXIT_FAILURE);
        }
        switch (pid = fork())
        {
        case -1:
            perror("Error al hacer fork");
            exit(EXIT_FAILURE);
        case 0:
            close(fd[0]);                   // cierro lectura
            redirect(in_fd, STDIN_FILENO);  // reemplazo stdin por in_fd
            redirect(fd[1], STDOUT_FILENO); // escribo a la entrada del pipe
            execvp(programs[pos][0], programs[pos]);
            perror("Error al ejecutar programa");
            exit(EXIT_FAILURE);
        default:
            // if you don't close the original file descriptor after duplication, the parent process and the child process may both attempt to write to the same pipe or file, which can cause unexpected results.
            close(fd[1]);
            close(in_fd);
            // el proceso padre se llama recursivamente con el file descriptor de escritura como el de entrada
            recursive_piping(programs, pos + 1, fd[0]);
            return;
        }
    }
}

void redirect(int oldfd, int newfd)
{
    if (oldfd != newfd)
    { //  The dup and dup2 system calls are used to duplicate a file descriptor, creating a new file descriptor that refers to the same file.
        if (dup2(oldfd, newfd) != -1)
            close(oldfd);
        // after redirecting the standard input or output to the appropriate file descriptor with dup2, the original file descriptor is closed to avoid such unintended sharing.
        else
        {
            perror("Error al ejecutar dup2");
            exit(EXIT_FAILURE);
        }
    }
}

void piping(char **commands)
{
    pipe_flag = 0;
    // programs es un arreglo que contiene, en cada posición, los arrays con argumentos para cada pipe por separado.
    char ***programs = (char ***)malloc(sizeof(char **) * tokens);
    for (int i = 0; i < tokens; i++)
    {
        programs[i] = (char **)malloc(sizeof(char *) * tokens);
        for (int j = 0; j < tokens; j++)
        {
            programs[i][j] = (char *)malloc(sizeof(char) * tokens);
        }
    }
    // int count_v[1024];
    int count = 0;
    int pipe_count = 0;
    for (int i = 0; i < tokens; i++)
    {
        if (strcmp(commands[i], "|") == 0)
        {
            programs[pipe_count][count] = NULL;
            pipe_count++;
            //      count_v[pipe_count] = count;
            count = 0;
        }
        else
        {
            // printf("String: %s\n", commands[i]);
            programs[pipe_count][count] = commands[i];
            count++;
        }
    }
    programs[pipe_count][count] = NULL;
    programs[pipe_count + 1] = NULL;
    int pid = fork();
    if (pid == -1)
    {
        perror("Error al hacer fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        // lo tiene que ejecutar otro proceso ya que sino el proceso padre no podía retomar la ejecución después de la llamada recursiva
        recursive_piping(programs, 0, STDIN_FILENO);
        exit(EXIT_SUCCESS);
    }
    else
    {
        int status;
        waitpid(pid, &status, 0);
    }
    pipe_flag = 0;
    return;
}

void io_redirection(char **commands)
{
    int input_fd = 0;
    int output_fd = 0;
    double_redir = 0;
    char *input_file = malloc(sizeof(char) * tokens);
    char *output_file = malloc(sizeof(char) * tokens);
    char **program = malloc(tokens * sizeof(char *));

    for (int i = 0; i < tokens; i++)
    {
        if (strcmp(commands[i], ">") == 0)
        {
            output_file = commands[i + 1];
            output_fd = 1;
        }
        else if (strcmp(commands[i], "<") == 0)
        {
            input_file = commands[i + 1];
            input_fd = 1;
        }
    }

    for (int i = 0; i < tokens; i++)
    {
        if (strcmp(commands[i], ">") == 0 || strcmp(commands[i], "<") == 0)
        {
            break;
        }
        //printf("Command %s\n", commands[i]);
        program[i] = commands[i];
    }

    if (input_fd != 0 && output_fd != 0){
        input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1)
        {
            perror("Error opening input file");
            exit(1);
        }
        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1)
        {
            perror("Error opening output file");
            exit(1);
        }
        double_redirection(program, input_fd, output_fd);
    }
    else if (input_fd != 0)
    {
        input_fd = open(input_file, O_RDONLY);
        if (input_fd == -1)
        {
            perror("Error opening input file");
            exit(1);
        }
        io_input_red(program, input_fd);
    }
    else if (output_fd != 0)
    {
        output_fd = open(output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (output_fd == -1)
        {
            perror("Error opening output file");
            exit(1);
        }
        io_output_red(program, output_fd);
    }

    io_flag = 0;
    return;
}

void io_output_red(char **commands, int fd)
{
    int status, d;

    switch (fork())
    {
    case 0:                          /* child */
        d = dup2(fd, STDOUT_FILENO); /* fd becomes the standard output */
        if (d == -1)
            perror("dup2 output\n");
        if(strcmp(commands[0], "echo") == 0) echo_interp(commands);
        else execvp(commands[0], commands);
        perror(commands[0]); /* execvp failed */
        exit(1);

    default: /* parent */
        while (wait(&status) != -1)
            ;
        close(fd);
        break;

    case -1: /* error */
        perror("fork");
    }
    return;
}

void io_input_red(char **commands, int fd)
{
    int status, d;

    switch (fork())
    {
    case 0:                         /* child */
        d = dup2(fd, STDIN_FILENO); /* fd becomes the standard input */
        if (d == -1)
            perror("dup2 input\n");
        execvp(commands[0], commands);
        perror(commands[0]); /* execvp failed */
        exit(1);

    default: /* parent */
        while (wait(&status) != -1)
            ; /* pick up dead children */
        close(fd);
        break;

    case -1: /* error */
        perror("fork");
    }
    return;
}

void double_redirection(char **commands, int fd_in, int fd_out)
{
    int status, d;

    switch (fork())
    {
    case 0:
        d = dup2(fd_in, STDIN_FILENO); /* fd becomes the standard input */
        if (d == -1)
            perror("dup2 input\n");
        d = dup2(fd_out, STDOUT_FILENO); /* fd becomes the standard input */
        if (d == -1)
            perror("dup2 input\n");

        execvp(commands[0], commands);
        perror(commands[0]); /* execvp failed */
        exit(1);

    default: /* parent */
        while (wait(&status) != -1)
            ; /* pick up dead children */
        close(fd_in);
        close(fd_out);
        break;

    case -1: /* error */
        perror("fork");
    }
    return;
}