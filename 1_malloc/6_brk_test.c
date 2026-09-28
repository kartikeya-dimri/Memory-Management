#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>

int main(void)
{
    long page_size = sysconf(_SC_PAGESIZE);
    
    void *brk_addr = sbrk(0);

    // printf("Page size: %ld\n", page_size);
    // printf("Initial brk: %p\n", brk_addr);
    getchar();

    for (long i = 1; i <= 5; i++) {

        void *new_brk =
            (char *)brk_addr + page_size;

        // ENOMEM
        if (brk(new_brk) == -1) {
            printf("\nbrk failed at iteration %ld\n", i);
            printf("errno = %d (%s)\n",
                   errno, strerror(errno));
            break;
        }
        
        *((char *)brk_addr+1) = 'A';
        
        brk_addr = new_brk;

        // printf("Page %4ld: brk = %p\n", i, brk_addr);
    }

    getchar();

    printf("\nFinal brk: %p\n", sbrk(0));

    getchar();

    for (long i = 1; i <= 5; i++) {

        void *new_brk =
            (char *)brk_addr - page_size;

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

    getchar();

    return 0;
}