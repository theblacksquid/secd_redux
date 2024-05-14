
#ifndef SECD_MACHINE
#define SECD_MACHINE

#define MEMBLOCK 1024
#define CELL_MAX MEMBLOCK*1000

#include "secd_cell.h"

typedef struct SECD_Machine SECD_Machine;

typedef struct SECD_Machine_Dump SECD_Machine_Dump;

typedef enum Dump_Flags
{
    DUMP_FLAG_STACK,
    DUMP_FLAG_ENVIRONMENT,
    DUMP_FLAG_CONTROL
} Dump_Flags;

struct SECD_Machine
{
    SECD_Cell*         stack;
    SECD_Cell*         environment;
    SECD_Cell*         control;
    SECD_Machine_Dump* dump;
    SECD_Cell          memory[CELL_MAX];
    unsigned int       next_free_cell;
    int                should_halt;
};

struct SECD_Machine_Dump
{
    SECD_Machine* head;
    SECD_Machine_Dump* next;
};

SECD_Cell* machine_alloc_free_cell(SECD_Machine* machine, unsigned int num_cells);
void machine_halt(SECD_Machine* machine, const char* message);
void machine_load_constant(SECD_Machine* machine);
void machine_load_value(SECD_Machine* machine);
void machine_load_function(SECD_Machine* machine);
void machine_select_branch(SECD_Machine* machine);
void machine_join(SECD_Machine* machine);
void machine_apply(SECD_Machine* machine);
void machine_return(SECD_Machine* machine);
void machine_dummy_env(SECD_Machine* machine);
void machine_recursive_apply(SECD_Machine* machine);
void machine_pair_car(SECD_Machine* machine);
void machine_pair_cdr(SECD_Machine* machine);
void machine_atom(SECD_Machine* machine);
void machine_cons(SECD_Machine* machine);
void machine_equal(SECD_Machine* machine);
void machine_add(SECD_Machine* machine);
void machine_subtract(SECD_Machine* machine);
void machine_divide(SECD_Machine* machine);
void machine_multiply(SECD_Machine* machine);
void machine_remainder(SECD_Machine* machine);
void machine_less_than_or_equal(SECD_Machine* machine);
void machine_greater_then(SECD_Machine* machine);
void machine_array_index(SECD_Machine* machine);
#endif
