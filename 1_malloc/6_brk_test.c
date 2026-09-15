#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    long page_size = sysconf(_SC_PAGESIZE);
    void *brk_addr = sbrk(0);

    getchar();

    printf("Page size: %ld\n", page_size);
    printf("Initial brk: %p\n", brk_addr);

    for (long i = 1; i <= 1000; i++) {

        void *new_brk =
            (char *)brk_addr + page_size;

        // ENOMEM
        if (brk(new_brk) == -1) {
            printf("\nbrk failed at iteration %ld\n", i);
            printf("errno = %d (%s)\n",
                   errno, strerror(errno));
            break;
        }

        brk_addr = new_brk;

        printf("Page %4ld: brk = %p\n", i, brk_addr);
    }

    printf("\nFinal brk: %p\n", sbrk(0));

    getchar();

    return 0;
}