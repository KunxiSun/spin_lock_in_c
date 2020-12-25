/*
    Single thread unit tests
*/

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "../src/spinlock.h"

struct entry{
    int ctr;
    struct tas tas_lock;
};

void test_lock_not_init(){
    
    struct entry * e = (struct entry*)malloc(sizeof(struct entry));
    e->ctr=0;
    //tas_init(&(e->tas_lock)); without init
    
    int res = tas_lock(&(e->tas_lock));
    assert(res!=0); //lock does not success

    free(e);
    puts("Test1-1");
}


void test_lock_init(){
    
    struct entry * e = (struct entry*)malloc(sizeof(struct entry));
    e->ctr=0;
    tas_init(&(e->tas_lock));
    
    assert(e->tas_lock.lock==0); //unlocked

    free(e);
    puts("Test1-2");
}

void test_lock_destory(){
    
    struct entry * e = (struct entry*)malloc(sizeof(struct entry));
    e->ctr=0;
    tas_init(&(e->tas_lock));
    tas_destroy(&(e->tas_lock));

    assert(e->tas_lock.lock==-1); //invalid statue

    free(e);
    puts("Test1-3");
}

void test_lock_lock(){
    
    struct entry * e = (struct entry*)malloc(sizeof(struct entry));
    e->ctr=0;
    tas_init(&(e->tas_lock));

    int res = tas_lock(&(e->tas_lock));

    assert(res==0); //success

    tas_destroy(&(e->tas_lock));

    free(e);
    puts("Test1-4");
}

void test_lock_unlock(){
    
    struct entry * e = (struct entry*)malloc(sizeof(struct entry));
    e->ctr=0;
    tas_init(&(e->tas_lock));

    int res1 = tas_lock(&(e->tas_lock));
    int res2 = tas_unlock(&(e->tas_lock));

    assert(res1==0); //success
    assert(res2==0); //success

    tas_destroy(&(e->tas_lock));

    free(e);
    puts("Test1-5");
}

void test_lock_null(){
    tas_init(NULL);

    int res1 = tas_lock(NULL);
    int res2 = tas_unlock(NULL);

    assert(res1==-1);
    assert(res2==-1);

    tas_destroy(NULL);
    puts("Test1-6");
}


int main(){
    
    puts("Test1 start...");
    test_lock_not_init();
    test_lock_init();
    test_lock_destory();
    test_lock_lock();
    test_lock_unlock();
    test_lock_null();
    puts("Test1 finish\n");

    return 0;
}