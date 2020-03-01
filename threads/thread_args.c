#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <pthread.h>

void error(char *msg) 
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

void* does_stuff(void *param){
    long thread_no = (long)param;
    printf("Thread number %ld\n", thread_no);
    return (void *) (thread_no + 1);
}

int main(int argc, char const *argv[])
{
    pthread_t threads[20];
    long t;
    for (t = 0; t < 3; t++)
    {
        if(pthread_create(&threads[t], NULL, does_stuff, (void*) t) == -1)
            error("Can't create thread");
    }
    void* result;
    for (t = 0; t < 3; t++)
    {
        if (pthread_join(threads[t], &result) == -1)
            error("Can't join thread");
        printf("Thread %ld returned %ld\n", t, (long) result);
    }
    return 0;
}
