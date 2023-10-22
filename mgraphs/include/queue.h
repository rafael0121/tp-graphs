/**
 * @brief Biblioteca de filas.
 *
 */

#ifndef QUEUE_H
#define QUEUE_H

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <mgraphs.h>

/**
 * @brief A structure to represent a queue of vertexes
 */
struct
{
    int front, rear, size;
    unsigned capacity;
    Vertex *array;
}typedef Queue;

/**
 * @brief Function to create a queue
 */
Queue *createQueue(unsigned capacity)
{
    Queue *queue = (Queue *)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->size = 0;
    queue->rear = capacity - 1;
    queue->array = (Vertex *)malloc(queue->capacity * sizeof(Vertex));
    return queue;
}

/**
 * @brief Queue is full when size becomes equal to the capacity
 */
int isFull(Queue *queue)
{
    return (queue->size == queue->capacity);
}

/**
 * @brief Queue is empty when size is 0
 */
int isEmpty(Queue *queue)
{
    return (queue->size == 0);
}

/**
 * @brief Function to add an item to the queue
 */
void enqueue(Queue *queue, Vertex item)
{
    if (isFull(queue))
        return;
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = item;
    queue->size = queue->size + 1;
}

/**
 * @brief Function to remove an item from queue
 */
Vertex dequeue(Queue *queue)
{
    Vertex invalid;
    invalid.id = -1;
    if (isEmpty(queue))
        return invalid;
    Vertex item = queue->array[queue->front];
    queue->front = (queue->front + 1) % queue->capacity;
    queue->size = queue->size - 1;
    return item;
}

/**
 * @brief Function to get front of queue
 */
/*Vertex front(Queue *queue)
{
    if (isEmpty(queue))
        return;
    return queue->array[queue->front];
}*/

/**
 * @brief Function to get rear of queue
 */
/*Vertex rear(Queue *queue)
{
    if (isEmpty(queue))
        return;
    return queue->array[queue->rear];
}*/

#endif