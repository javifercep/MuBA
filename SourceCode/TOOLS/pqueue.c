
/* Includes ------------------------------------------------------------------*/

#include "pqueue.h"
#include "MemoryManagement.h"
#include <stddef.h>


/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

void pqueue_init(pqueue * queue)
{
  queue->queue_end = 0;
  queue->qhead = 0;
  pthread_mutex_init(&queue->queue_lock, NULL);
  pthread_cond_init(&queue->not_empty, NULL);
}

void pqueue_release(pqueue * queue)
{
  pthread_mutex_lock(&queue->queue_lock);

  // Mark the queue as ended
  queue->queue_end = 1;
  // Unblock all threads
  pthread_cond_broadcast(&queue->not_empty);

  pthread_mutex_unlock(&queue->queue_lock);
}

void pqueue_push(pqueue * queue, void * usr_data)
{
	pthread_mutex_lock(&queue->queue_lock);
	struct pqueue_elem * h = queue->qhead;
	while (h && h->next != 0)
		h = h->next;

	struct pqueue_elem * ne = (struct pqueue_elem *)MemAlloc(sizeof(pqueue_elem));
	ne->data = usr_data;
	ne->next = 0;

	if (h) h->next = ne;
	else   queue->qhead = ne;

	// Signal some other thread waiting in the queue
	pthread_cond_signal(&queue->not_empty);

	pthread_mutex_unlock(&queue->queue_lock);
}

// Push element in the front (typically used to give hi prio)
void pqueue_push_front(pqueue * queue, void * usr_data)
{
  pthread_mutex_lock(&queue->queue_lock);

  struct pqueue_elem * ne = (struct pqueue_elem *)MemAlloc(sizeof(pqueue_elem));
  ne->data = usr_data;
  ne->next = queue->qhead;

  queue->qhead = ne;

  // Signal some other thread waiting in the queue
  pthread_cond_signal(&queue->not_empty);

  pthread_mutex_unlock(&queue->queue_lock);
}

// Returns the fron element. If there is no element it blocks until there is any.
// If the writing end of the queue is closed it returns NULL
void * pqueue_pop(pqueue * queue)
{
pthread_mutex_lock(&queue->queue_lock);

void * udata = 0;
while (1)
{
  if (queue->qhead != 0) {
	  struct pqueue_elem * h = queue->qhead;
	  udata = queue->qhead->data;

	  queue->qhead = queue->qhead->next;
	  free(h);
  }

  if (udata == 0) {
	  if (queue->queue_end == 0) // No work in the queue, wait here!
		  pthread_cond_wait(&queue->not_empty,&queue->queue_lock);
	  else
		  break;  // No work and we are told to finish working
  }
  else
	  break;
}

pthread_mutex_unlock(&queue->queue_lock);

return udata;
}

// Returns the element in the front or NULL if no element is present
// It never blocks!
void * pqueue_pop_nonb(pqueue * queue)
{
  pthread_mutex_lock(&queue->queue_lock);

  void * udata = 0;
  if (queue->qhead != 0) {
      struct pqueue_elem * h = queue->qhead;
      udata = queue->qhead->data;

      queue->qhead = queue->qhead->next;
      free(h);
  }

  pthread_mutex_unlock(&queue->queue_lock);

  return udata;
}

// Returns queue size
int pqueue_size(pqueue * queue)
{
  pthread_mutex_lock(&queue->queue_lock);
  struct pqueue_elem * h = queue->qhead;

  int size = 0;
  while (h != 0) {
	  h = h->next;
	  size++;
  }

  pthread_mutex_unlock(&queue->queue_lock);

  return size;
}

// Returns whether the queue has been marked as released (writer finished)
int pqueue_released(pqueue * queue)
{
  pthread_mutex_lock(&queue->queue_lock);

  int res = queue->queue_end;

  pthread_mutex_unlock(&queue->queue_lock);

  return res;
}

// Sleeps until the queue has at least one element in it or the queue is released
void pqueue_wait(pqueue * queue)
{
  pthread_mutex_lock(&queue->queue_lock);

  while (queue->qhead == 0 && !queue->queue_end)
  {
	  pthread_cond_wait(&queue->not_empty,&queue->queue_lock);
  }

  pthread_mutex_unlock(&queue->queue_lock);
}



