
#ifndef SECD_PAIR
#define SECD_PAIR

#include "secd_cell.h"

typedef struct SECD_Machine SECD_Machine;
typedef struct SECD_Pair SECD_Pair;

SECD_Cell pair_head(SECD_Cell* pair);
SECD_Cell* pair_rest(SECD_Cell* pair);
SECD_Cell* pair_cons(SECD_Cell* pair, SECD_Cell* value, SECD_Machine* context);
unsigned int pair_count(SECD_Cell* pair);

#endif
