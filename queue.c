#include "queue.h" 

void init_queue(queue_t *q) {
    q->head = q->tail = NULL;
    pthread_mutex_init(&q->lock, NULL);
    pthread_cond_init(&q->cond, NULL);
}

void enqueue(queue_t *q, int *numbers, int count) {
     task_t *task = malloc(sizeof(task_t)); // allocate task
    if (!task) {
        perror("Failed to allocate task");
        exit(EXIT_FAILURE);
    }

    task->numbers = malloc(count * sizeof(int)); // allocate array of numbers to check in task
    if (!task->numbers) {
        perror("Failed to allocate task numbers");
        free(task);
        exit(EXIT_FAILURE);
    }
    memcpy(task->numbers, numbers, count * sizeof(int)); // copy numbers from batch to task
    task->count = count;
    task->next = NULL;

    pthread_mutex_lock(&q->lock);
    if (q->tail == NULL) {
        q->head = q->tail = task;
    } else {
        q->tail->next = task;
        q->tail = task;
    }
    pthread_cond_signal(&q->cond);
    pthread_mutex_unlock(&q->lock);
}


task_t *dequeue(queue_t *q) {
   pthread_mutex_lock(&q->lock);

    while (q->head == NULL) {
        pthread_cond_wait(&q->cond, &q->lock);
    }

    task_t *task = q->head;
    q->head = q->head->next;

    if (q->head == NULL) {
        q->tail = NULL;
    }

    pthread_mutex_unlock(&q->lock);

    return task;
}