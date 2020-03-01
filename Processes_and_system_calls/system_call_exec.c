#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

char *my_env[] = {"JUICE=peach and apple", NULL};

int main()
{
    execle("dinner_info", "dinner_info", "4", NULL, my_env);
    puts(strerror(errno));
    return 0;
}
