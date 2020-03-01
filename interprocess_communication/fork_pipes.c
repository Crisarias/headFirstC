#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void printFromMain(char *msg)
{
    static int cont = 0;
    if (strcmp(msg,"endline\n") == 0)
    {
        cont++;
        return;
    }
    char fileName[12];
    snprintf(fileName, 12, "order%d.txt", cont);
    FILE *f = fopen(fileName, "a");
    if (!f)
    {         
        char errorMsg[17 + sizeof(fileName)];
        strcpy(errorMsg, "Can't open file ");
        strcat(errorMsg, fileName);
        error(errorMsg);
    }
    if (fprintf(f, "%s", msg) == -1)
    {
         error("Error writing in file");
    }    
    fclose(f);    
}

char *my_env[] = {"JUICE=peach and apple", NULL};

int main()
{
    int i;
    int fd[2];
    if (pipe(fd) == -1)
    {
        error("Can't create the pipe");
    }
    
    for (i = 0; i < 10; i++)
    {
        __pid_t pid= fork();        
        if (pid == -1)
        {
            error("Can't fork the process");
        }
        if (!pid)
        {
            dup2(fd[1], 1);
            close(fd[0]);
            char orderNumber[sizeof(i)];
            snprintf(orderNumber, sizeof(i), "%d", i);
            if (execle("dinner_info", "dinner_info", orderNumber, NULL, my_env) == -1)
            {
                error("An error ocurred");
            } 
        }
        int pid_status;
        if (waitpid(pid, &pid_status, 0) == -1)
        {
            error("Error waiting for child process");
        }
        if(WEXITSTATUS(pid_status))
            puts("Error status non-zero");              
    }
    dup2(fd[0], 0);
    close(fd[1]);
    char line[255];
    while (fgets(line, 255, stdin))
    {
        printFromMain(line);
    }
    return 0;    
}