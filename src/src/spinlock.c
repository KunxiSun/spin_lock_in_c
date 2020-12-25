#include <stdatomic.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "spinlock.h"

#define LOCKED (1)
#define UNLOCKED (0)
#define INVALID_TAS (-1)

void tas_init(struct tas * t){
    //check null lock
    if(t==NULL){
        return;
    }
    
    t->lock=UNLOCKED;
}

int tas_lock(struct tas * t){
    //check null lock
    if(t==NULL){
        return INVALID_TAS;
    }

    //check invalid statue of lock
    if(t->lock<=INVALID_TAS || t->lock>LOCKED){
        return INVALID_TAS;
    }

    //waiting
    int expected = UNLOCKED;
    while(!__atomic_compare_exchange_n(&(t->lock),&expected,LOCKED,true,__ATOMIC_SEQ_CST,__ATOMIC_SEQ_CST)){
        expected = UNLOCKED;
    }

    //return success
    return 0;
}

int tas_unlock(struct tas * t){
    //check null lock
    if(t==NULL){
        return INVALID_TAS;
    }

    //check invalid statue of lock
    if(t->lock<=INVALID_TAS || t->lock>LOCKED){
        return INVALID_TAS;
    }

    //change statue to UNLOCKED
    __atomic_store_n(&(t->lock),UNLOCKED,__ATOMIC_SEQ_CST);

    //return success
    return 0;
}

void tas_destroy(struct tas * t){
    //check null lock
    if(t==NULL){
        return;
    }

    //change statue of lock to invalid
    t->lock = INVALID_TAS; 
}