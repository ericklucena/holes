/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-24 23:35:17
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 05:06:26
*/

#include "memory.h"
#include "queue.h"
#include "circularList.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[])
{
    FILE* input;
    MemoryUnit unit;
    Memory *memory;

    if (argc != 2)
    {
        printf("Wrong number of parameters\nUsage: holes [input file]");
        exit(1);
    }

    input = fopen(argv[1], "r");

    if (input == NULL)
    {
        printf("Cannot open the file.");
        exit(1);
    }

    memory = newMemory();
    initMemory(memory);

    unit.type = mt_process;
    unit.timesSwapped = 0;

    while (fscanf(input, "%c %d\n", &unit.id, &unit.size) != EOF)
    {
        enqueue(memory->swap, newNode(unit));
    }

    run(memory, f_next);

    return 0;
}