# CIS 3110 Assignment Three - Part 2

## STUDENT
Erick Lucena Palmeira Silva     #0905100

## ABOUT
This program simulates the memory management in a OS.

The simulated algorithms simulated are:
- First fit
- Best fit
- Worst fit
- Next fit

### REPRESENTATION
The memory is represented by a circular double linked list. There is 4 types of node:

- Head
-- Represents the starting point of the memory
- Last
-- Represents the position of the last process loaded on the memory
- Process
-- Represents a process on the memory
- Free
-- Represents a free memory block (Hole)

### ALGORITHMS

#### FIRST FIT
The algorithm iterates over the list (starting at the head) and returns the first block of free memory with enough space to accomodate the process that needs to be loaded.
If there is no space available, old processes are swapped out to free the memory.

#### BEST FIT
The algorithm iterates over the list (starting at the head) and search for the free memory block which has the lesser diference between its size and the process to be loaded size.
If there is no space available, old processes are swapped out to free the memory.

#### Worst Fit
The algorithm iterates over the list (starting at the head) and search for the free memory block which has the greater diference between its size and the process to be loaded size.
If there is no space available, old processes are swapped out to free the memory.

#### NEXT FIT
The algorithm iterates over the list (starting at the last insertion) and returns the first block of free memory with enough space to accomodate the process that needs to be loaded.
If there is no space available, old processes are swapped out to free the memory.

## COMPILING THE PROGRAM
To compile this program type "make"

## RUNNING THE PROGRAM
To run the program type "./bin/holes [input file]"

