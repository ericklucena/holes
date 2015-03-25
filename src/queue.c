/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-21 15:46:22
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 15:06:00
*/

#include "data.h"
#include "queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Queue* newQueue()
{
    Queue* queue;

    queue = malloc(sizeof(Queue));

    if (queue != NULL)
    {
        queue->head = NULL;
        queue->tail = NULL;
    }

    return queue;
}

void freeQueue(Queue *queue)
{
    Node *toFree;

    while (!isEmpty(queue))
    {
        toFree = dequeue(queue);
        free(toFree);
    }

    free(queue);
}

void enqueue (Queue* queue, Node* node)
{

    if (queue->tail != NULL)
    {
        queue->tail->next = node;
        queue->tail = node;
        node->next = NULL;
    }
    else
    {
        queue->head = queue->tail = node;
        node->next = NULL;
    }
}

Node* dequeue (Queue* queue)
{
    Node* node;

    node = queue->head;

    if (queue->head != NULL)
    {
        if (queue->head == queue->tail)
        {
            queue->head = queue->tail = NULL;
        }
        else
        {
            queue->head = queue->head->next;
        }

        node->next = NULL;
    }

    return node;
}

bool isEmpty(Queue *queue)
{
    return queue->head == NULL;
}

void printQueue(Queue *queue)
{
    Node* iterator;

    iterator = queue->head;

    while (iterator != NULL)
    {
        printNode(iterator);
        iterator = iterator->next;
    }
    printf("\n");

}

