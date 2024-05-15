
#include "secd_machine.h"
#include "secd_cell.h"
#include "secd_pair.h"
#include <stdio.h>
#include <stdlib.h>

void pop_control_push_stack(SECD_Machine* machine)
{
    SECD_Cell* to_load = pair_head(machine->control);
    machine->stack     = pair_cons(machine->stack, to_load, machine);
    machine->control   = pair_rest(machine->control);
}

SECD_Cell* pop_stack(SECD_Machine* machine)
{
    SECD_Cell* result = pair_head(machine->stack);
    machine->stack    = pair_rest(machine->stack);

    return result;
}

SECD_Cell* pop_control(SECD_Machine* machine)
{
    SECD_Cell* result   = pair_head(machine->control);
    machine->control    = pair_rest(machine->control);

    return result;
}

void dump_machine(SECD_Machine* machine, Dump_Flags flag)
{
    SECD_Machine_Dump* result = calloc(1, sizeof(result));
    SECD_Machine* dump = calloc(1, sizeof(dump));

    if ( (result != 0) && (dump != 0) )
    {
	result->next = machine->dump;
	
	if ( flag & DUMP_FLAG_STACK )
	{
	    dump->stack = machine->stack;
	}
	
	if ( flag & DUMP_FLAG_ENVIRONMENT )
	{
	    dump->environment = machine->environment;
	}

	if ( flag & DUMP_FLAG_CONTROL )
	{
	    dump->control = machine->control;
	}

	result->head = dump;
    }
}

void restore_machine(SECD_Machine* machine, Dump_Flags flag)
{
    SECD_Machine_Dump* dump = machine->dump;
    
    if ( flag & DUMP_FLAG_STACK )
    {
	machine->stack = dump->head->stack;
    }
	
    if ( flag & DUMP_FLAG_ENVIRONMENT )
    {
	machine->environment = dump->head->environment;
    }

    if ( flag & DUMP_FLAG_CONTROL )
    {
	machine->control = dump->head->control;
    }
    
    machine->dump = machine->dump->next;
    free(dump->head);
    free(dump);
}

SECD_Cell* machine_alloc_free_cell(SECD_Machine* machine, unsigned int num_cells)
{
    SECD_Cell* result = 0;

    if ( machine->next_free_cell < CELL_MAX )
    {
	result = &machine->memory[machine->next_free_cell];
	machine->next_free_cell += num_cells;
    }

    return result;
}

void machine_nil(SECD_Machine* machine)
{
    machine->stack = pair_cons(machine->stack, 0, machine);
}

void machine_load_constant(SECD_Machine* machine)
{
    pop_control_push_stack(machine);
}

void machine_halt(SECD_Machine *machine, const char *message)
{
    machine->should_halt = 1;
    fprintf(stderr, message);
}

void machine_load_value(SECD_Machine* machine)
{
    SECD_Cell* pair        = pair_head(machine->control);
    machine->control       = pair_rest(machine->control);
    int environment_index  = pair_head(pair)->data.unsigned_int;
    SECD_Cell* variable    = pair_by_index(machine->environment, environment_index);
    machine->stack         = pair_cons(machine->stack, variable, machine);
}

void machine_load_function(SECD_Machine* machine)
{
    SECD_Cell* closure = pair_cons(machine->control, machine->environment, machine);
    machine->control   = pair_rest(machine->control);
    machine->stack     = pair_cons(machine->stack, closure, machine);
}

void machine_select_branch(SECD_Machine* machine)
{
    SECD_Cell* to_evaluate = pop_stack(machine);
    SECD_Cell* branch = 0;

    if ( to_evaluate != 0 )
    {
	branch = pop_control(machine);
    }

    else
    {
	pop_control(machine); // discard 'true' branch
	branch = pop_control(machine);
    }

    dump_machine(machine, DUMP_FLAG_CONTROL);
    machine->control = branch;
}

void machine_join(SECD_Machine* machine)
{
    restore_machine(machine, DUMP_FLAG_CONTROL);
}

void machine_apply(SECD_Machine* machine)
{
    Dump_Flags flags = DUMP_FLAG_STACK | DUMP_FLAG_CONTROL | DUMP_FLAG_ENVIRONMENT;
    SECD_Cell* closure = pop_stack(machine);
    SECD_Cell* parameters = pop_stack(machine);
    dump_machine(machine, flags);
    machine->stack = 0;
    machine->environment = pair_cons(pair_rest(closure), parameters, machine);
    machine->control = pair_head(closure);
}

void machine_return(SECD_Machine* machine)
{
    Dump_Flags flags = DUMP_FLAG_STACK | DUMP_FLAG_CONTROL | DUMP_FLAG_ENVIRONMENT;
    SECD_Cell* result = pop_stack(machine);
    restore_machine(machine, flags);
    machine->stack = pair_cons(machine->stack, result, machine);
}

void machine_dummy_env(SECD_Machine* machine)
{
    SECD_Cell* empty_list = pair_cons(0, 0, machine);
    machine->environment = pair_cons(machine->environment, empty_list, machine);
}

void machine_recursive_apply(SECD_Machine* machine)
{
    Dump_Flags flags = DUMP_FLAG_STACK | DUMP_FLAG_CONTROL | DUMP_FLAG_ENVIRONMENT;
    SECD_Cell* closure = pop_stack(machine);
    SECD_Cell* parameters = pop_stack(machine);
    dump_machine(machine, flags);
    machine->stack = 0;

    // discard top
    machine->environment = pair_rest(machine->environment);
    // replace with new
    machine->environment = pair_cons(pair_rest(closure), parameters, machine);
    
    machine->control = pair_head(closure);    
}

void machine_pair_car(SECD_Machine* machine)
{
	SECD_Cell* from_stack = pop_stack(machine);
	machine->stack = pair_cons(machine->stack, pair_head(from_stack), machine);
}

void machine_pair_cdr(SECD_Machine* machine)
{
	SECD_Cell* from_stack = pop_stack(machine);
	machine->stack = pair_cons(machine->stack, pair_head(from_stack), machine);
}

void machine_atom(SECD_Machine *machine)
{
	SECD_Cell* to_test = pop_stack(machine);
	SECD_Cell* result = machine_alloc_free_cell(machine, 1);

	if ( (to_test->type == SECD_Arra) || (to_test->type == SECD_List) )
		result->data.unsigned_int = 0;

	else
		result->data.unsigned_int = 1;

	machine->stack = pair_cons(machine->stack, result, machine);
}

void machine_cons(SECD_Machine *machine)
{
	SECD_Cell* head = pop_stack(machine);
	SECD_Cell* rest = pop_stack(machine);
	SECD_Cell* pair = pair_cons(rest, head, machine);
	machine->stack  = pair_cons(machine->stack, pair, machine);
}
