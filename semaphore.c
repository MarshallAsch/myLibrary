#ifdef __APPLE__
 # include <dispatch/dispatch.h>
#else /* ifdef __APPLE__ */
 # include <semaphore.h>
#endif /* ifdef __APPLE__ */


#include <stdlib.h>
#include "semaphore.h"


void semInit(Semaphore *sem, int count)
{
    if (sem == NULL) {
        return;
    }

    #ifdef __APPLE__
    sem->sem = dispatch_semaphore_create(count);
    #else /* ifdef __APPLE__ */
    sem_init(&sem->sem, 0, count);
    #endif /* ifdef __APPLE__ */
}

void semPost(Semaphore *sem)
{
    if (sem == NULL) {
        return;
    }

    #ifdef __APPLE__
    dispatch_semaphore_signal(sem->sem);
    #else /* ifdef __APPLE__ */
    sem_post(&sem->sem);
    #endif /* ifdef __APPLE__ */
}

void semWait(Semaphore *sem)
{
    if (sem == NULL) {
        return;
    }

    #ifdef __APPLE__
    dispatch_semaphore_wait(sem->sem, DISPATCH_TIME_FOREVER);
    #else /* ifdef __APPLE__ */
    sem_wait(&sem->sem);
    #endif /* ifdef __APPLE__ */
}

void semDestroy(Semaphore *sem)
{
    if (sem == NULL) {
        return;
    }

    #ifdef __APPLE__
    dispatch_release(sem->sem);
    #else /* ifdef __APPLE__ */
    sem_destroy(&sem->sem);
    #endif /* ifdef __APPLE__ */
}
