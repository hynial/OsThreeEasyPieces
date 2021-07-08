#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<assert.h>

typedef struct myarg_t{
    int a;
    int b;
} myarg_t;

typedef struct myret_t{
    int x;
    int y;
} myret_t;

void *mythread(void *arg){
    myarg_t *m = (myarg_t *)arg;
    printf("a:%d b:%d\n", m->a, m->b);

    myret_t *n = malloc(sizeof(myret_t));
    // myret_t *n;
    n->x = 1;
    n->y = 2;

    return (void *) n;
}

int main(int argc, char *args[]){
    int rc;
    pthread_t p;
    myarg_t arg;
    myret_t *ret;

    arg.a = 10;
    arg.b = 20;
    pthread_create(&p, NULL, mythread, &arg);
    pthread_join(p, (void *) &ret);

    printf("returned: %d %d\n", ret->x, ret->y);

    return 0;
}