#include <stdio.h>
#include <unistd.h>

int main() {
    void *first = sbrk(0);
    void *second = sbrk(10);
    void *third = sbrk(10);
    void *fourth = sbrk(0);
    printf("First: %p\n", first);
    getchar();
    printf("Second: %p\n", second);
    getchar();
    printf("Third: %p\n", third);
    getchar();
    printf("Fourth: %p\n", fourth);

    return 0;
}