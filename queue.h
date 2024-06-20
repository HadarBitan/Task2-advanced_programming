#ifndef QUEUE_H
#define QUEUE_H
#include <stdbool.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_THREADS 8

#define MAX_QUEUE_SIZE 10000

typedef struct task {
    int* numbers; 
    int count;     
    struct task* next;  
} task_t;


typedef struct queue {
    task_t* head; 
    task_t* tail; 
    pthread_mutex_t lock; 
    pthread_cond_t cond; 
} queue_t;

// Function declarations
void init_queue(queue_t* q);
void enqueue(queue_t* q, int* numbers, int count);
task_t* dequeue(queue_t* q);

#endif 