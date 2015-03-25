/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-21 15:46:22
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 03:26:39
*/

#include "data.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Node* newNode(MemoryUnit unit)
{
    Node* node;

    node = malloc(sizeof(Node));
    if (node != NULL)
    {
        node->info = unit;
        node->next = NULL;
        node->previous = NULL;
    }

    return node;
}

void printNode (Node* node)
{
    MemoryUnit unit = node->info;

    switch (unit.type)
    {
        case mt_head:
            printf("Head\n");
            break;
        case mt_last:
            printf("Last\n");
            break;
        case mt_free:
            printf("Free %dMB\n", unit.size);
            break;
        case mt_process:
            printf("%c %dMB | %d swaps | in: %d\n", unit.id, unit.size, unit.timesSwapped, unit.time);
            break;
    }

    //printf("%d <- %d -> %d\n", node->previous, node, node->next);
}
