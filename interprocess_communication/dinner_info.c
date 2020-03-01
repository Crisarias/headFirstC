#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char const *argv[])
{
    printf("Dinners: %s\n", argv[1]);
    printf("Juice: %s\n", getenv("JUICE"));
    printf("endline\n");
    return 0;
}
