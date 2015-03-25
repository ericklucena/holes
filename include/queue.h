/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-21 15:46:01
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 15:05:06
*/

#ifndef _ELUCENAP_QUEUE_H
#define _ELUCENAP_QUEUE_H

#include <stdbool.h>

typedef struct queue
{
    Node *head;
    Node *tail;
} Queue;

Queue* newQueue();
void freeQueue(Queue *queue);
void enqueue (Queue* queue, Node* node);
Node* dequeue (Queue* queue);
bool isEmpty(Queue *queue);
void printQueue(Queue *queue);

#endif
