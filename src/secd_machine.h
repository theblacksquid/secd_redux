
#ifndef SECD_MACHINE
#define SECD_MACHINE

#define MEMBLOCK 1024
#define CELL_MAX MEMBLOCK*1000

#include "secd_cell.h"
#include "secd_pair.h"

typedef struct SECD_Machine SECD_Machine;

typedef struct SECD_Machine_Dump SECD_Machine_Dump;

struct SECD_Machine
{
    SECD_Pair*         stack;
    SECD_Pair*         environment;
    SECD_Pair*         control;
    SECD_Machine_Dump* dump;
    SECD_Cell          memory[CELL_MAX];
};

struct SECD_Machine_Dump
{
    SECD_Machine head;
    SECD_Machine_Dump* next;
};

#endif
