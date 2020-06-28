#include <sys/time.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMCPUS 16
int threadsID[NUMCPUS];

typedef struct __counter_t {
    int             global;
    pthread_mutex_t glock;
    int             local[NUMCPUS];
    pthread_mutex_t llock[NUMCPUS];
    int             threshold;
} counter_t;

typedef struct __argument_t {
    counter_t *c;
    int thread;
} argument_t;

// init: record threshold, init locks, init values
//       of all local counts and global count
void init(counter_t *c, int threshold){
    c->threshold = threshold;
    c->global = 0;
    pthread_mutex_init(&c->glock, NULL);
    int i;
    for(i = 0; i < NUMCPUS; i++){
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

// update: usually, just grab local lock and update
// local amout; once local count has risen 'threshold'.
// grab global lock and thransfer local values to it
void update(counter_t *c, int threadID, int amt){
    // int cpu = threadID & NUMCPUS;
    int cpu = 0;
    for(int i = 0; i< NUMCPUS; i++)
    {
        if(threadsID[i] == threadID)
        {
            cpu = i;
            break;
        }
        if(threadsID[i] == 0)
        {
            threadsID[i] = threadID;
            cpu = i;
            break;
        }
    }
    pthread_mutex_lock(&c->llock[cpu]);
    c->local[cpu] += amt;
    if (c->local[cpu] >= c->threshold){
        // transfer to global (assumes amt>0)
        pthread_mutex_lock(&c->glock);
        c->global += c->local[cpu];
        pthread_mutex_unlock(&c->glock);
        c->local[cpu] = 0;
    }
    pthread_mutex_unlock(&c->llock[cpu]);
}

// get: just return global amount (approximate)
int get(counter_t *c){
    pthread_mutex_lock(&c->glock);
    int val = c->global;
    pthread_mutex_unlock(&c->glock);
    return val; // only approximate;
}

/* void *loop(void* arg)
{
    counter_t *c = (counter_t *)arg;
    pthread_t id = pthread_self();
    int tid = (id % 10000000000) / 10000000;
    //printf("thread ID: %lu\n",(id%10000000000)/10000000);
    argument_t *a = (argument_t *)arg;
    int tid = a->threadID; 
    int i = 0;
    while(i < 1000000)
    {
        update(c, 0, 1);
        i++;
    }
} */

void *loop(void *arg)
{
    argument_t *m = (argument_t *)arg;
    pthread_t threadID = pthread_self();
    int i = 0;
    while(i < 1000000)
    {
        update(m->c, (int)threadID, 1);
        i++;
    }
}

int main(int argc, char *argv[])
{
    //argument_t argument;
    counter_t *counter;
    counter = calloc(1, sizeof(counter_t));
    pthread_t pthread[16];
    argument_t args;
    struct timeval startTime, endTime;
    int thr_id;
    double diffTime;
    double avgTime = 0;
    
    args.c = counter;
    int arr[] = {1,2,4,8,16,32,64,128,256,512,1024,2048,4096,8192,16384};
    for (int j = 0; j< 15; j++){
        int th = arr[j];
        for(int i = 0; i < 10; i++)
        {
            init(counter, th);
            gettimeofday(&startTime, NULL);
            for(int k = 0; k < atoi(argv[1]); k++)
            {
                pthread_create(&pthread[k], NULL, loop, &args);
            }
            for (int k = 0; k < atoi(argv[1]); k++)
            {
                pthread_join(pthread[k], NULL);
            }
            gettimeofday(&endTime,NULL);
            diffTime = (double)(endTime.tv_sec - startTime.tv_sec) + ((double)(endTime.tv_usec - startTime.tv_usec)/1000000);
            avgTime += diffTime;

        }
        avgTime /= 10;
        printf("th: %d\n", th);
        printf("counter: %d\n", get(counter));
        printf("%d thread avg: %f s\n", atoi(argv[1]), avgTime);
    }
    free(counter);


    return 0;
}