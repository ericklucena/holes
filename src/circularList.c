/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-24 21:49:50
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 01:27:42
*/

#include "data.h"
#include "circularList.h"
#include <stdlib.h>

CircularList* newCircularList()
{
    CircularList *list = malloc(sizeof(CircularList));

    if (list != NULL)
    {
        list->head = NULL;
    }

    return list;
}

void insertOnHead(CircularList *list, Node *node)
{
    if (list->head == NULL)
    {
        list->head = node;
        node->next = node;
        node->previous = node;
    }
    else
    {
        insertBefore(list->head, node);
    }
}

void insertBefore (Node *node, Node *newNode)
{
    Node *previous;

    previous = node->previous;

    newNode->previous = previous;
    newNode->next = node;

    previous->next = newNode;
    node->previous = newNode;
}

void insertAfter (Node *node, Node *newNode)
{
    Node *next;

    next = node->next;

    newNode->previous = node;
    newNode->next = next;

    next->previous = newNode;
    node->next = newNode;
}

Node* removeNode (Node *node)
{
    node->next->previous = node->previous;
    node->previous->next = node->next;

    node->next = NULL;
    node->previous = NULL;

    return node;
}

void printCircularList(CircularList *list)
{
    Node* iterator;

    iterator = list->head;

    if (iterator != NULL)
    {
        do
        {
            printNode(iterator);
            iterator = iterator->next;
        } while(iterator != list->head);
    }
    printf("\n");
}

