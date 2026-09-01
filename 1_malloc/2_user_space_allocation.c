#include <stdio.h>
#include <stdlib.h>

int main() {
    int *ptrs[1000];
    getchar();
    // 1000 small allocations
    for (int i = 0; i < 1000; i++) {
        ptrs[i] = malloc(40);

        if (ptrs[i] == NULL) {
            printf("malloc failed at allocation %d\n", i);
            return 1;
        }

        // Touch the memory so we actually use it
        *ptrs[i] = i;
    }

    printf("1000 small allocations completed\n");

    getchar();

    // Free the small allocations
    for (int i = 0; i < 1000; i++) {
        free(ptrs[i]);
    }

    printf("1000 small allocations freed\n");
    getchar();

    // One large allocation
    size_t size = 100 * 1024 * 1024;  // 100 MB

    char *large = malloc(size);

    if (large == NULL) {
        printf("Large allocation failed\n");
        return 1;
    }

    printf("100 MB allocation completed\n");
    getchar();
    
    // Touch the memory
    large[0] = 'A';
    large[size - 1] = 'Z';

    free(large);

    printf("100 MB allocation freed\n");
    getchar();

    return 0;
}

// brk(NULL)                               = 0x6479e86f0000
// brk(0x6479e8711000)                     = 0x6479e8711000
// 1000 small allocations completed
// 1000 small allocations freed
// mmap(NULL, 104861696, ...)              = 0x7efb151ff000
// 100 MB allocation completed
// munmap(0x7efb151ff000, 104861696)       = 0
// 100 MB allocation freed