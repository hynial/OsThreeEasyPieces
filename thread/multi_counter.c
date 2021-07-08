#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>

static const int NUM_CPU = 4;

typedef struct counter_t{
    int global;
    pthread_mutex_t glock;
    int local[NUM_CPU];
    pthread_mutex_t llock[NUM_CPU];
    int threshold;
} counter_t;

counter_t cg;

void init(counter_t *c, int threshold){
    c->global = 0;
    c->threshold = threshold;
    pthread_mutex_init(&c->glock, NULL);

    for(int i = 0; i < NUM_CPU; i++){
        c->local[i] = 0;
        pthread_mutex_init(&c->llock[i], NULL);
    }
}

void update(counter_t *c, int threadId, int amt){
    pthread_mutex_lock(&c->llock[threadId]);
    c->local[threadId] += amt;
    
    if(c->local[threadId] >= c->threshold){
        pthread_mutex_lock(&c->glock);
        c->global += c->local[threadId];
        pthread_mutex_unlock(&c->glock);
        
        c->local[threadId] = 0;
        
    }

    pthread_mutex_unlock(&c->llock[threadId]);
}

int get(counter_t *c){
    int val;
    pthread_mutex_lock(&c->glock);
    val = c->global;
    pthread_mutex_unlock(&c->glock);

    for(int i =0; i < NUM_CPU; i++){
        val += c->local[i];
    }
    return val;
}

void *mythread(void *arg){
    // counter_t *c = (counter_t *)arg;
    char *tid = (char *) arg;
    int threadId = (int) tid;
    int i;
    for(i = 0; i < 1e6; i++){
        update(&cg, threadId, 1);
    }

    return NULL;
}

int main(int argc, char *argv[]){
    init(&cg, 1024);

    int times = 1e6;
    int i;
    pthread_t p[NUM_CPU];
    for(i = 0; i < NUM_CPU; i++){
        pthread_create(&p[i], NULL, mythread, (char *) i);
    }

    for(i = 0; i < NUM_CPU; i++){
        pthread_join(p[i], NULL);
    }

    printf("total:%d\n", get(&cg));
}