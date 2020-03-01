#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    if (execlp("ip", "ip", "a", NULL) == -1)
    {
        if (execlp("ipconfig", "ipconfig", NULL) == -1)
        {
            fprintf(stderr, "Cannot run ipconfig: %s", strerror(errno));
            return 1;
        }
        
    }    
    return 0;
}
