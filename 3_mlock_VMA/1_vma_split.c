// to see locked
//  cat /proc/$(pidof a.out)/smaps | grep -E '^[0-9a-f]+-|^Size:|^Locked:|^VmFlags:'
// cat /proc/$(pidof a.out)/smaps

#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main(void)
{
    size_t size = 3 * 4096;

    getchar();

    void *p = mmap(NULL, size,
                   PROT_READ | PROT_WRITE,
                   MAP_PRIVATE | MAP_ANONYMOUS,
                   -1, 0);

    if (p == MAP_FAILED) {
        perror("mmap");
        return 1;
    }

    printf("PID: %d\n", getpid());
    printf("Mapping: %p - %p\n",
           p, (char *)p + size);

    printf("Press Enter before mlock...");
    getchar();

    if (mlock((char *)p + 4096, 200) == -1) {
        perror("mlock");
        return 1;
    }

    printf("mlock() done\n");
    printf("Press Enter after mlock...");
    getchar();

    munlock((char *)p + 4096, 200);
    getchar();
    munmap(p, size);

    return 0;
}