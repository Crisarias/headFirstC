#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *my_env[] = {"JUICE=peach and apple", NULL};

int main()
{
    int i;
    for (i = 0; i < 10; i++)
    {
        __pid_t pid= fork();
        if (pid == -1)
        {
            fprintf(stderr,"Can't fork the process: %s\n",strerror(errno));
            return 1;
        }
        if (!pid)
        {
            if (execle("dinner_info", "dinner_info", "4", NULL, my_env) == -1)
            {
                fprintf(stderr,"An error ocurred: %s\n",strerror(errno));
                return 1;
            }
            return 0;            
        }
    }
    return 0;    
}
