#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/resource.h>

static long prev_minflt = 0;

static void faults(const char *tag)
{
    struct rusage ru;
    getrusage(RUSAGE_SELF, &ru);

    fprintf(stderr, "%s: minflt=%ld delta=%ld majflt=%ld\n",
            tag,
            ru.ru_minflt,
            ru.ru_minflt - prev_minflt,
            ru.ru_majflt);

    prev_minflt = ru.ru_minflt;
}

static void pause_here(void)
{
    getchar();
}

int main(void)
{
    size_t size = 100 * 1024 * 1024;
    long pgsz = sysconf(_SC_PAGESIZE);

    faults("before malloc");
    pause_here();

    char *large = malloc(size);

    if (!large) {
        perror("malloc");
        return 1;
    }

    faults("after malloc");
    pause_here();

    uintptr_t beg = (uintptr_t)large & ~(uintptr_t)(pgsz - 1);
    uintptr_t end = ((uintptr_t)large + size + pgsz - 1)
                    & ~(uintptr_t)(pgsz - 1);

    madvise((void *)beg, end - beg, MADV_NOHUGEPAGE);

    faults("after madvise");
    pause_here();

    for (size_t i = 0; i < size; i += pgsz)
        large[i] = 'A';

    faults("after touching 100MB");
    pause_here();

    free(large);

    faults("after free");
    pause_here();

    return 0;
}