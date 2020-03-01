#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

int beers = 2000000;
pthread_mutex_t beers_lock = PTHREAD_MUTEX_INITIALIZER;

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void* drink_lots(void *a){
    int i = 0;
    pthread_mutex_lock(&beers_lock);
    for (i = 0; i < 100000; i++)
    {
        beers = beers - 1;
    }
    printf("There are now %i bottles of beer on the wall\n", beers);
    pthread_mutex_unlock(&beers_lock);
    return NULL;
}

int main(int argc, char const *argv[])
{
    pthread_t threads[20];
    int i;
    printf("%i bottles of beer on the wall\n%i bottles of beer\n", beers, beers);
    for (i = 0; i < 20; i++)
    {
       if(pthread_create(&threads[i], NULL, drink_lots, NULL) == -1)
        error("Can't create thread");
    }    
    void* result;
    for (i = 0; i < 20; i++)
    {
        if (pthread_join(threads[i], &result) == -1)
            error("Can't join thread");
    }
    printf("There are now %i bottles of beer on the wall\n", beers);
    return 0;
}
