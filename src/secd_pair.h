
#ifndef SECD_PAIR
#define SECD_PAIR

#include "secd_cell.h"

typedef struct SECD_Pair SECD_Pair;

struct SECD_Pair
{
    SECD_Cell* head;
    SECD_Cell* rest;
};

SECD_Cell pair_head(SECD_Pair* pair);
SECD_Cell* pair_rest(SECD_Pair* pair);
unsigned int pair_count(SECD_Pair* pair);

#endif
