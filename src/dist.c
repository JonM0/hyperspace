#include <math.h>
#include "postgres.h"
#include "fmgr.h"
PG_MODULE_MAGIC;
#include "fourd.h"

PG_FUNCTION_INFO_V1(fourd_dist);

Datum fourd_dist(PG_FUNCTION_ARGS)
{
    FourD *a = (FourD *)PG_GETARG_POINTER(0);
    FourD *b = (FourD *)PG_GETARG_POINTER(1);

    FourD diff = {
        .x1 = a->x1 - b->x1,
        .x2 = a->x2 - b->x2,
        .x3 = a->x3 - b->x3,
        .x4 = a->x4 - b->x4,
    };

    PG_RETURN_FLOAT8(sqrt(MAG(&diff)));
}