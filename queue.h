
#ifndef __QUEUE_H__
#define  __QUEUE_H__

struct QueueElement {
    struct QueueElement *prev;
    struct QueueElement *next;
    void                *data;
};

struct Queue
{
    struct QueueElement *first;
    struct QueueElement *last;
};


struct Queue* newQueue();
int           destroyQueue(struct Queue *queue,
                           void (       *destruct)(void *obj));

int           push(struct Queue *queue,
                   void         *data);

int           popBottem(struct Queue *queue,
                        void        **data);

#endif /* ifndef __QUEUE_H__ */
