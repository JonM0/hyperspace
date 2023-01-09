#include <math.h>
#include "postgres.h"
#include "fmgr.h"
PG_MODULE_MAGIC;
#include "point4d.h"

PG_FUNCTION_INFO_V1(point4d_dist);

Datum point4d_dist(PG_FUNCTION_ARGS)
{
    Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
    Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

    Point4D diff = {
        .x1 = a->x1 - b->x1,
        .x2 = a->x2 - b->x2,
        .x3 = a->x3 - b->x3,
        .x4 = a->x4 - b->x4,
    };

    PG_RETURN_FLOAT8(sqrt(MAG(&diff)));
}