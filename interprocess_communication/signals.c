#include <stdio.h>
#include <errno.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void diediedie (int sig)
{
    puts("\nGoodbye cruel world....\n");
    exit(1);
}

//Register or replace a new signal
int catch_signal(int sig, void (*handler) (int))
{
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);    
}

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char const *argv[])
{
    if (catch_signal(SIGINT, diediedie) == -1)
    {
        error("Can't map the handler");
    }
    char name[30];
    printf("Enter your name: ");
    fgets(name, 30, stdin);
    printf("Hello %s\n", name);
    catch_signal(SIGTERM, SIG_DFL);//Default handler
    return 0;
}
