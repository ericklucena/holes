/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-21 15:46:01
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 00:23:59
*/

#ifndef _ELUCENAP_DATA_H
#define _ELUCENAP_DATA_H

typedef enum memoryType
{
    mt_head,
    mt_last,
    mt_free,
    mt_process
} MemoryType;

typedef struct memoryUnit
{
    MemoryType type;
    char id;
    int size;
    int time;
    int timesSwapped;
} MemoryUnit;

typedef struct node
{
    MemoryUnit info;
    struct node *next;
    struct node *previous;
} Node;

Node* newNode (MemoryUnit process);
void printNode (Node *node);

#endif
