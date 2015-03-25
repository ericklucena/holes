/* 
* @Author: Erick Lucena Palmeira Silva
* @Date:   2015-03-24 23:35:17
* @Last Modified by:   Erick Lucena Palmeira Silva
* @Last Modified time: 2015-03-25 15:33:28
*/

#include "memory.h"
#include "queue.h"
#include "circularList.h"
#include <stdio.h>
#include <stdlib.h>

#define FIT 4

int main(int argc, char* argv[])
{
    int i;
    FILE* input;
    MemoryUnit unit;
    Memory* memory[4];

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

    for(i=0; i<FIT; i++)
    {
        memory[i] = newMemory();
        initMemory(memory[i]);
    }

    unit.type = mt_process;
    unit.timesSwapped = 0;

    while (fscanf(input, "%c %d\n", &unit.id, &unit.size) != EOF)
    {
        for(i=0; i<FIT; i++)
        {
            enqueue(memory[i]->swap, newNode(unit));
        }
    }

    for(i=0; i<FIT; i++)
    {
        run(memory[i], i);
        freeMemory(memory[i]);
    }


    fclose(input);

    return 0;
}