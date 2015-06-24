#include <pthread.h>

struct pqueue_elem
{
  void * data;
  struct pqueue_elem * next;
} pqueue_elem;

typedef struct
{
  pthread_mutex_t queue_lock;
  pthread_cond_t  not_empty;
  int queue_end;
  struct pqueue_elem * qhead;
}pqueue;

void pqueue_init(pqueue * queue);

void pqueue_release(pqueue * queue);

void pqueue_push(pqueue * queue, void * usr_data) ;

// Push element in the front (typically used to give hi prio)
void pqueue_push_front(pqueue * queue, void * usr_data);

// Returns the fron element. If there is no element it blocks until there is any.
// If the writing end of the queue is closed it returns NULL
void * pqueue_pop(pqueue * queue);
// Returns the element in the front or NULL if no element is present
// It never blocks!
void * pqueue_pop_nonb(pqueue * queue);

// Returns queue size
int pqueue_size(pqueue * queue);

// Returns whether the queue has been marked as released (writer finished)
int pqueue_released(pqueue * queue);

// Sleeps until the queue has at least one element in it or the queue is released
void pqueue_wait(pqueue * queue);

