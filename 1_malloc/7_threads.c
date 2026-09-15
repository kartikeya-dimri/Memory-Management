#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

__thread int tls_variable;

void *thread_function(void *arg)
{
    long thread_id = (long)arg;

    tls_variable = thread_id * 100;
    int local_variable;

    printf("Thread %ld\n", thread_id);
    printf("  PID      : %d\n", getpid());
    printf("  TID      : %ld\n", syscall(186));
    printf("  TLS addr : %p\n", (void *)&tls_variable);
    printf("  TLS value: %d\n", tls_variable);
    printf("Stack: %p\n", &local_variable);

    printf("Thread %ld waiting...\n", thread_id);
    getchar();

    return NULL;
}

int main(void)
{
    pthread_t t1, t2, t3;

    printf("Process PID: %d\n", getpid());
    printf("Main thread waiting...\n");

    pthread_create(&t1, NULL, thread_function, (void *)1);
    pthread_create(&t2, NULL, thread_function, (void *)2);
    pthread_create(&t3, NULL, thread_function, (void *)3);

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    pthread_join(t3, NULL);

    return 0;
}