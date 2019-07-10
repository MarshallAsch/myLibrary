#ifndef __SEMAPHORE_H__
#define __SEMAPHORE_H__

#ifdef __APPLE__
 # include <dispatch/dispatch.h>
#else /* ifdef __APPLE__ */
 # include <semaphore.h>
#endif /* ifdef __APPLE__ */

typedef struct Semaphore {
#ifdef __APPLE__
    dispatch_semaphore_t sem;
#else /* ifdef __APPLE__ */
    sem_t sem;
#endif /* ifdef __APPLE__ */
} Semaphore;


void semInit(Semaphore *sem,
             int        count);

void semPost(Semaphore *sem);

void semWait(Semaphore *sem);

void semDestroy(Semaphore *sem);

#endif /* ifndef __SEMAPHORE_H__ */
