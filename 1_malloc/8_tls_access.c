#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

__thread int tls_value;

int *t2_tls_address;

pthread_barrier_t barrier;

void *thread2(void *arg)
{
    tls_value = 222;

    t2_tls_address = &tls_value;

    printf("T2: TLS address = %p\n", (void *)&tls_value);
    printf("T2: TLS value   = %d\n", tls_value);

    // Wait until T1 has accessed the TLS.
    pthread_barrier_wait(&barrier);

    printf("T2: TLS value after T1 modified it = %d\n", tls_value);

    return NULL;
}

void *thread1(void *arg)
{
    // Wait until T2 has published its TLS address.
    while (t2_tls_address == NULL)
        sched_yield();

    printf("T1: T2 TLS address = %p\n",
           (void *)t2_tls_address);

    printf("T1: reading T2 TLS = %d\n",
           *t2_tls_address);

    *t2_tls_address = 999;

    printf("T1: wrote 999 into T2 TLS\n");

    pthread_barrier_wait(&barrier);

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    pthread_barrier_init(&barrier, NULL, 2);

    pthread_create(&t2, NULL, thread2, NULL);
    pthread_create(&t1, NULL, thread1, NULL);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_barrier_destroy(&barrier);

    return 0;
}