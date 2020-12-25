#ifndef SPINLOCK_H
#define SPINLOCK_H

struct tas{
    int lock; //0 : UNLOCKED ; 1: LOCKED; -1 INVALID_TAS
};

/**
* @pram taslock, initialises the handle for the taslock
*/
void tas_init(struct tas * t);

/**
* Locks, operation should be successful if the lock is valid.
* If the lock is invalid, the lock operation returns a non-zero integer
* tas lock that is currently in a locked state will keep threads waiting.
* @param taslock
* @return success
*/
int tas_lock(struct tas * t);

/**
* Unlocks, operation should be successful is the lock is valid.
* If the lock is invalid, unlock operation returns a non-zero integer.
* @param taslock
* @return success
*/
int tas_unlock(struct tas * t);

/**
* Destroys the tas lock, puts it in an invalid state
* @param taslock
*/
void tas_destroy(struct tas * t);


#endif