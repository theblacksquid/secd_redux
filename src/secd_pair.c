
#include "secd_cell.h"
#include "secd_pair.h"
#include "secd_machine.h"

SECD_Cell pair_head(SECD_Cell* pair)
{
    return *pair->data.pair_value.head;
}

SECD_Cell* pair_rest(SECD_Cell* pair)
{
    return pair->data.pair_value.rest;
}

SECD_Cell* pair_cons(SECD_Cell* pair, SECD_Cell* value, SECD_Machine* context)
{
    SECD_Cell* new_cell = machine_alloc_free_cell(context, 1);
    new_cell->type = SECD_List;
    new_cell->data.pair_value.head = value;
    new_cell->data.pair_value.rest = pair;

    return new_cell;
}

unsigned int pair_count(SECD_Cell* pair)
{
    unsigned int result = 0;

    for (SECD_Cell* tracker = pair; pair != 0; )
    {
	if ( tracker->type == SECD_List )
	{
	    tracker = tracker->data.pair_value.rest;
	}

	else
	{
	    tracker = 0;
	}

	result++;
    }

    return result;
}
