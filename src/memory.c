/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-23 19:33:54
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 05:05:11
*/

#include "data.h"
#include "queue.h"
#include "memory.h"
#include "circularList.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

Memory* newMemory ()
{
    Memory *memory;

    memory = malloc(sizeof(Memory));

    memory->totalMemUsage = 0;
    memory->timer = 0;

    if (memory != NULL)
    {
        memory->ram = newCircularList();
        if (memory->ram != NULL)
        {
            memory->swap = newQueue();
            if (memory->swap == NULL)
            {
                free(memory->ram);
                free(memory);
                memory = NULL;
            }
        }
        else
        {
            free(memory);
            memory = NULL;
        }
    }

    return memory;
}

bool initMemory(Memory *memory)
{
    bool success = true;
    
    Node *headNode;
    Node *lastNode;
    Node *emptyNode;

    MemoryUnit head;
    MemoryUnit last;
    MemoryUnit emptyMemory;
    

    head.type = mt_head;
    last.type = mt_last;
    emptyMemory.type = mt_free;
    emptyMemory.size = MEMORY_SIZE;

    headNode = newNode(head);

    if (headNode != NULL)
    {
        insertOnHead(memory->ram, headNode);

        lastNode = newNode(last);

        if (lastNode != NULL)
        {
            insertOnHead(memory->ram, lastNode);
            memory->lastInsertion = lastNode;

            emptyNode = newNode(emptyMemory);

            if (emptyNode != NULL)
            {
                insertOnHead(memory->ram, emptyNode);
            }
            else
            {
                free(headNode);
                free(lastNode);
                memory->ram->head = NULL;
                success = false;
            }
        }
        else
        {
            free(headNode);
            memory->ram->head = NULL;
            success = false;
        }
    }
    else
    {
        success = false;
    }

    return success;
}

void addMemoryUnit (Memory *memory, Node *node, Fit fit)
{
    char pid = node->info.id;
    Node *freeSpace = NULL;

    freeSpace = searchFreeSpace(memory, node->info.size, fit);

    while (freeSpace == NULL)
    {
        swapOut(memory);
        freeSpace = searchFreeSpace(memory, node->info.size, fit);
    }


    if (freeSpace != NULL)
    {
        node->info.time = memory->timer++;
        insertBefore(freeSpace, node);
        insertBefore(node, removeNode(memory->lastInsertion));
        freeSpace->info.size -= node->info.size;
        if (freeSpace->info.size == 0)
        {
            removeNode(freeSpace);
        }
    }
    printLoad(memory, pid);

}

Node* searchFreeSpace(Memory *memory, int size, Fit fit)
{
    Node *freeSpace;
    switch (fit)
    {
        case f_first:
            freeSpace = firstFit(memory, size);
            break;

        case f_worst:
            freeSpace = worstFit(memory, size);
            break;

        case f_next:
            freeSpace = nextFit(memory, size);
            break;

        case f_best:
            freeSpace = bestFit(memory, size);
            break;
    }

    return freeSpace;
}

Node* bestFit (Memory *memory, int size)
{
    Node *iterator = memory->ram->head->next;
    Node *best = firstFit(memory, size);

    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_free && iterator->info.size >= size && iterator->info.size < best->info.size)
        {
            best = iterator;
            break;
        }

        iterator = iterator->next;
    }

    return best;
}

Node* worstFit (Memory *memory, int size)
{
    Node *iterator = memory->ram->head->next;
    Node *worst = firstFit(memory, size);

    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_free && iterator->info.size >= size && iterator->info.size > worst->info.size)
        {
            worst = iterator;
            break;
        }

        iterator = iterator->next;
    }

    return worst;
}

Node* nextFit (Memory *memory, int size)
{
    Node *iterator = memory->lastInsertion->next;
    Node *memPos = NULL;

    while (iterator != memory->lastInsertion)
    {
        if (iterator->info.type == mt_free && iterator->info.size >= size)
        {
            memPos = iterator;
            break;
        }

        iterator = iterator->next;
    }

    return memPos;
}

Node* firstFit (Memory *memory, int size)
{
    Node *iterator = memory->ram->head->next;
    Node *memPos = NULL;

    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_free && iterator->info.size >= size)
        {
            memPos = iterator;
            break;
        }

        iterator = iterator->next;
    }

    return memPos;
}

void defrag(Memory *memory)
{
    Node *iterator;
    Node *toFree;

    iterator = memory->ram->head->next;

    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_free)
        {
            if (iterator->next->info.type == mt_free)
            {
                iterator->info.size += iterator->next->info.size;
                toFree = iterator->next;
                removeNode(iterator->next);
                free(toFree);
            }
            else if (iterator->next->info.type == mt_last)
            {
                if (iterator->next->next->info.type == mt_free)
                {
                    iterator->next->next->info.size += iterator->info.size;
                    toFree = iterator;
                    iterator = iterator->next;
                    removeNode(iterator->previous);
                    free(toFree);
                }   
            }
        }

        iterator = iterator->next;
    }
}

void swapOut(Memory *memory)
{
    Node *oldest = NULL;
    Node *iterator;
    Node *newFree;

    iterator = memory->ram->head->next;

    // Search for the first process
    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_process)
        {
            oldest = iterator;
            break;
        }
        iterator = iterator->next;
    }

    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_process && iterator->info.time < oldest->info.time)
        {
            oldest = iterator;
        }
        iterator = iterator->next;
    }

    if (oldest != NULL)
    {
        if (oldest->previous->info.type == mt_free)
        {
            oldest->previous->info.size += oldest->info.size;
        }
        else if (oldest->next->info.type == mt_free)
        {
            oldest->next->info.size += oldest->info.size;
        }
        else
        {
            newFree = newNode(oldest->info);
            newFree->info.type = mt_free;
            insertBefore(oldest, newFree);
        }

        removeNode(oldest);
        oldest->info.timesSwapped++;
        if (oldest->info.timesSwapped < 3)
        {
            enqueue(memory->swap, oldest);
        }
        else
        {
            free(oldest);
        }

        defrag(memory);
    }
}

void run(Memory *memory, Fit fit)
{
    while (!isEmpty(memory->swap))
    {
        //printMemory(memory);
        addMemoryUnit(memory, dequeue(memory->swap), fit);
    }
}

void printLoad(Memory *memory, char pid)
{
    Stats stats;

    stats = getStats(memory);
    memory->totalMemUsage+= (double) stats.usage/MEMORY_SIZE*100;
    printf("%c loaded, #processes = %d, #holes = %d, %%memusage = %.1lf, cumulative %%mem = %.1lf\n", pid, stats.processes, stats.holes, (double) stats.usage/MEMORY_SIZE*100, (double)memory->totalMemUsage/memory->timer);
}

Stats getStats(Memory *memory)
{
    Stats stats;
    Node *iterator;

    stats.processes = 0;
    stats.holes = 0;
    stats.usage = 0;
    iterator = memory->ram->head->next;

    // Search for the first process
    while (iterator != memory->ram->head)
    {
        if (iterator->info.type == mt_process)
        {
            stats.processes++;
            stats.usage += iterator->info.size;
        }
        else if (iterator->info.type == mt_free)
        {
            stats.holes++;
        }
        iterator = iterator->next;
    }

    return stats;
}

void printMemory(Memory* memory)
{
    printf("RAM\n");
    printCircularList(memory->ram);
    printf("SWAP\n");
    printQueue(memory->swap);
}
