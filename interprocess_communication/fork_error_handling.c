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

char *my_env[] = {"JUICE=peach and apple", NULL};

int main()
{
    int i;
    FILE *f = fopen("orders.txt", "w");
    if (!f)
    {
        error("Can't open file orderx.txt");
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
            if (dup2(fileno(f), 1) == -1)
            {
                error("Can't redirect Standard Output");
            }
            
            if (execle("dinner_info", "dinner_info", "4", NULL, my_env) == -1)
            {
                error("An error ocurred");
            }
            return 0;            
        }
        int pid_status;
        if (waitpid(pid, &pid_status, 0) == -1)
        {
            error("Error waiting for child process");
        }
        if(WEXITSTATUS(pid_status))
            puts("Error status non-zero");
              
    }
    return 0;    
}