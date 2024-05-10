
#include "secd_cell.h"
#include "secd_pair.h"

SECD_Cell pair_head(SECD_Pair* pair)
{
    return *pair->head;
}

SECD_Cell* pair_rest(SECD_Pair* pair)
{
    return pair->rest;
}

unsigned int pair_count(SECD_Pair* pair)
{
    unsigned int result = 0;

    for (SECD_Pair* tracker = pair; tracker->rest != 0; )
    {
	switch ( tracker->rest->type )
	{
	    case SECD_UInt:
	    case SECD_SInt:
	    case SECD_Floa:
	    case SECD_Char:
	    case SECD_Arra:
	    case SECD_Inst:
	    {
		tracker = &((SECD_Pair) { .head = 0, .rest = 0 });
	    }
	    break;
	    
	    case SECD_List:
	    {
		tracker = pair_rest(tracker)->data.pair_value;
	    }
	    break;
	}
    }

    return result;
}
