#include<stdio.h>
#include<assert.h>
#include<pthread.h>

static volatile int counter = 0;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *mythread(void* arg){
    printf("%s\n", (char *)arg);
    int i = 0;
    for(; i < 1e7; i++){
        pthread_mutex_lock(&lock);
        counter += 1;
        pthread_mutex_unlock(&lock);
    }
    printf("%s: done\n", (char *)arg);
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t p1, p2;
    printf("main thread: start\n");

    int rc;
    rc = pthread_create(&p1, NULL, mythread, "A");
    assert(rc == 0);
    rc = pthread_create(&p2, NULL, mythread, "B");
    assert(rc == 0);

    rc = pthread_join(p1, NULL);
    assert(rc == 0);
    rc = pthread_join(p2, NULL);
    assert(rc == 0);

    printf("main thread: end (counter=%d)\n", counter);
    return 0;
}