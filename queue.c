

#include <stdlib.h>
#include <stdio.h>

#include "queue.h"


struct QueueElement* newQueueElement(void *data);

void                 destroyAll(struct QueueElement *element,
                                void (*destruct)(void *obj));

/**
 * This will create a new empty queue
 * @return      pointer to a created queue on success NULL on failure
 */
struct Queue* newQueue()
{
    struct Queue *queue;

    /* try allocating memory */
    queue = malloc(sizeof(struct Queue));

    if (queue == NULL) {
        return NULL;
    }

    queue->first = NULL;
    queue->last  = NULL;

    return queue;
}

/**
 * Creates a new data wraper for the queue
 * @param  data that data that is going into the queue element
 * @return      NULL on failure or a QueueElement struct on success
 */
struct QueueElement* newQueueElement(void *data)
{
    struct QueueElement *new;

    new = malloc(sizeof(struct QueueElement));

    /* make sure that malloc succeded */
    if (new == NULL) {
        return NULL;
    }

    new->prev = NULL;
    new->next = NULL;
    new->data = data;

    return new;
}

/**
 * This will free all the memory that is being used by the queue
 * @param  queue    the queue to free
 * @param  destruct the function to use to free all the memory for each element
 *                  of the queue
 *                  if it is NULL then just free() is called on the data
 * @return          -1 if the queue does not exist
 *                  0 on success
 */
int destroyQueue(struct Queue *queue, void (*destruct)(void *obj))
{
    /* check if the list exists */
    if (queue == NULL) {
        return -1;
    }

    /* make sure that a destructor function is given */
    if (destruct == NULL)
    {
        destruct = &free;
    }

    destroyAll(queue->first, destruct);
    free(queue);


    return 0;
}

/**
 * This will recursivly destroy the entire list of elements in the queue
 * @param element  the element in the queue to destroy
 * @param destruct the destroy function for the data
 *                 can not be NULL
 */
void destroyAll(struct QueueElement *element, void (*destruct)(void *obj))
{
    /* then it is done */
    if (element == NULL) {
        return;
    }

    /* This should not happen */
    if (destruct == NULL) {
        return;
    }

    (*destruct)(element->data);
    destroyAll(element->next, destruct);
    free(element);
}

/**
 * This will push the data onto the top of the queue/
 * This is not inhearitly thread safe, to make it thread save this call needs to
 * be protected with read/write protection.
 *
 * @param  queue the queue that the data is being added to
 * @param  data  the data that is being added
 * @return       0 on success
 *              -1 if the queue does not exist
 *              -2 if memory could not be allocated for the data
 */
int push(struct Queue *queue, void *data)
{
    struct QueueElement *wrapper;

    /* the queuecan not be NULL */
    if (queue == NULL) {
        return -1;
    }

    wrapper = newQueueElement(data);

    /* make sure that the wrapper was created successfully */
    if (wrapper == NULL) {
        return -2;
    }

    /* if the queue is empty */
    if (queue->last == NULL)
    {
        queue->first = wrapper;
        queue->last  = wrapper;
    }
    else
    {
        queue->last->next = wrapper;
        wrapper->prev     = queue->last;
        queue->last       = wrapper;
    }

    return 0;
}

/**
 * This will pop the bottem element off of the queue
 * @param  queue the queue that the element is being removed from
 * @param  data  where to put the data element from the queue
 *               will not get modified incase of a early exit
 * @return       0 on succes
 *              -1 if the queue does not exist
 *              -2 if the queue is empty
 */
int popBottem(struct Queue *queue, void **data)
{
    struct QueueElement *temp;

    /* the queue must exist to do this action */
    if (queue == NULL) {
        return -1;
    }

    /* return error code if the queue is empty */
    if (queue->first == NULL) {
        return -2;
    }

    temp  = queue->first;
    *data = temp->data;

    queue->first = temp->next;

    if (queue->first != NULL) {
        queue->first->prev = NULL;
    }

    /* make sure it was not the last element from the queue */
    if (queue->last == temp) {
        queue->last = NULL;
    }

    /* free the memory used by the wrapper */
    temp->prev = NULL;
    temp->next = NULL;
    temp->data = NULL;
    free(temp);

    return 0;
}
