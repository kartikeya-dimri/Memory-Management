#include <stdio.h>
#include <unistd.h>

int main() {
    // add \n or manual flush to flush out buffer immediately
    printf("hello");
    fflush(stdout);
    sleep(10);
}