#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct timeval startTime, endTime;


typedef struct __counter_t
{
    int value;
    pthread_mutex_t lock;
} counter_t;

void init(counter_t *c)
{
    c->value = 0;
    pthread_mutex_init(&c->lock, NULL);
}

void increment(counter_t *c)
{
    pthread_mutex_lock(&c->lock);
    c->value++;
    pthread_mutex_unlock(&c->lock);
}

void *loop(void *arg)
{
    counter_t *c = (counter_t *) arg;
    int i = 0;
    while(i < 1000000)
    {
        increment(c);
        i++;
    }
}
/* void decrement(counter_t *c)
{
    c->value--;
}

int get(counter_t *c)
{
    return c->value;
}
 */
int main()
{
    counter_t counter;
    pthread_t pthread[7];
    int thr_id;
    int status;
    double diffTime;
    double avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        loop(&counter);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("One thread avg: %f s\n",avgTime);

    avgTime = 0;
    for (int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Two thread avg: %f s\n",diffTime);

    avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[1], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        pthread_join(pthread[1],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Three thread avg: %f s\n",diffTime);

    avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[1], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[2], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        pthread_join(pthread[1],NULL);
        pthread_join(pthread[2],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Four thread avg: %f s\n",diffTime);

    avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[1], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[2], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[3], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        pthread_join(pthread[1],NULL);
        pthread_join(pthread[2],NULL);
        pthread_join(pthread[3],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Five thread avg: %f s\n",diffTime);

    avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[1], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[2], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[3], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[4], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        pthread_join(pthread[1],NULL);
        pthread_join(pthread[2],NULL);
        pthread_join(pthread[3],NULL);
        pthread_join(pthread[4],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Six thread avg: %f s\n",diffTime);

    avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[1], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[2], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[3], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[4], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[5], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        pthread_join(pthread[1],NULL);
        pthread_join(pthread[2],NULL);
        pthread_join(pthread[3],NULL);
        pthread_join(pthread[4],NULL);
        pthread_join(pthread[5],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Seven thread avg: %f s\n",diffTime);

    avgTime = 0;
    for(int i = 0; i < 100; i++)
    {
        init(&counter);
        gettimeofday(&startTime, NULL);
        thr_id = pthread_create(&pthread[0], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[1], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[2], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[3], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[4], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[5], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        thr_id = pthread_create(&pthread[6], NULL, loop, &counter);
        if(thr_id < 0)
        {
            perror("thread create error: ");
            exit(0);
        }
        loop(&counter);
        pthread_join(pthread[0],NULL);
        pthread_join(pthread[1],NULL);
        pthread_join(pthread[2],NULL);
        pthread_join(pthread[3],NULL);
        pthread_join(pthread[4],NULL);
        pthread_join(pthread[5],NULL);
        pthread_join(pthread[6],NULL);
        gettimeofday(&endTime,NULL);
        diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
        avgTime += diffTime;
    }
    avgTime /= 100;
    printf("counter: %d\n", counter.value);
    printf("Eight thread avg: %f s\n",diffTime);

    return 0;
}