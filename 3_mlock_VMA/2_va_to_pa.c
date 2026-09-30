#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
    int *x = malloc(4096);

    printf("PID = %d\n", getpid());
    printf("Virtual address = %p\n", (void *)x);

    getchar();

    free(x);
    return 0;
}