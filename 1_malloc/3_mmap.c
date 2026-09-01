#include <stdio.h>
#include <sys/mman.h>

int main() {
    size_t size = 4096;

    char *p = mmap(
        NULL,
        size,
        PROT_READ | PROT_WRITE,
        MAP_PRIVATE | MAP_ANONYMOUS,
        -1,
        0
    );

    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    p[0] = 'A';
    p[1] = 'B';

    printf("%c %c\n", p[0], p[1]);

    munmap(p, size);

    return 0;
}