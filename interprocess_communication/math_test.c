#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <string.h>

int score = 0;

void end_game (int sig)
{
    printf("\nFinal score: %i\n", score);
    exit(0);
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

void times_up(int sig)
{
    puts("\nTIME'S UP!");
    raise(SIGINT);
}

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char const *argv[])
{
    if (catch_signal(SIGINT, end_game) == -1)
    {
        error("Can't map the handler");
    }
    if (catch_signal(SIGALRM, times_up) == -1)
    {
        error("Can't map the handler");
    }    
    srandom( time(0));    
    while (1)
    {
        int a = random() % 11;
        int b = random() % 11;        
        char txt[4];
        alarm(5);
        printf("\nWhat is %i times %i?", a, b);
        fgets(txt, 4, stdin);
        int answer = atoi(txt);
        if (answer == a * b)
            score++;
        else           
            printf("\nWrong! Score: %i", score);
    }
    return 0;
}
