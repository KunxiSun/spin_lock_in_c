/*
    Normal test, test if lock works for the normal operation by checking
    the value of counter equals to THREAD_NUM * SIZE
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../src/spinlock.h"

#define THREAD_NUM (2) 
#define SIZE (10000)

struct entry{
    int ctr;
    struct tas tas_lock;
};

void *thread_func(void* arg){
    struct entry* e = (struct entry*)arg;

    for(int i=0;i<SIZE;i++){
        tas_lock(&(e->tas_lock));
        e->ctr+=1;
        tas_unlock(&(e->tas_lock));
    }

    return NULL;
}

int main(){

    puts("Test2 start...");
    
    //init an element for thread function
    struct entry * e = (struct entry*)malloc(sizeof(struct entry));
    e->ctr=0;
    tas_init(&(e->tas_lock));

    //thread ids
    pthread_t threads[THREAD_NUM];

    //create threads
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_create(threads + i, NULL, thread_func, e);
    }

    //threads join
    for (int i = 0; i < THREAD_NUM; i++)
    {
        pthread_join(threads[i], NULL);
    }

    //check the value    
    printf("Counter value is: %d\nSuppose to be: %d\n",e->ctr, SIZE*THREAD_NUM);

    assert(e->ctr ==SIZE*THREAD_NUM);

    //free the memory of element
    tas_destroy(&(e->tas_lock));
    free(e);

    puts("Test2 finish\n");

    return 0;
}