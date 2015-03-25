/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-24 17:05:52
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 05:05:33
*/


#ifndef _ELUCENAP_MEMORY_H
#define _ELUCENAP_MEMORY_H

#include "data.h"
#include "queue.h"
#include "circularList.h"
#include <stdio.h>
#include <stdbool.h>

#define MEMORY_SIZE 128

typedef struct memory
{
    CircularList *ram;
    Queue *swap;
    Node *lastInsertion;
    int timer;
    double totalMemUsage;
} Memory;

typedef struct stats
{
    int processes;
    int holes;
    int usage;
} Stats;

typedef enum fit
{
    f_best,
    f_worst,
    f_next,
    f_first
} Fit;

Memory* newMemory();
bool initMemory(Memory *memory);
void addMemoryUnit(Memory *memory, Node *node, Fit fit);
Node* searchFreeSpace(Memory *memory, int size, Fit fit);
Node* bestFit(Memory *memory, int size);
Node* worstFit(Memory *memory, int size);
Node* nextFit(Memory *memory, int size);
Node* firstFit(Memory *memory, int size);
void defrag(Memory *memory);
void swapOut(Memory *memory);
void run(Memory *memory, Fit fit);
void printLoad(Memory *memory, char pid);
Stats getStats(Memory *memory);
void printMemory(Memory* memory);

#endif
