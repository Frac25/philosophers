#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *p_live(void *arg)
{
    printf("Hello from thread %d\n", *(int *)arg);
    return NULL;
}

int main()
{
    pthread_t threads[5];
    int ids[5];

    for (int i = 0; i < 5; i++)
    {
        ids[i] = i;
        if (pthread_create(&threads[i], NULL, p_live, &ids[i]) != 0)
        {
            perror("Failed to create thread");
        }
    }

    for (int i = 0; i < 5; i++)
    {
        pthread_join(threads[i], NULL);
    }

    return 0;
}
