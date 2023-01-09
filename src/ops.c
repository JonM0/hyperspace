#include "postgres.h"
#include "fmgr.h"
PG_MODULE_MAGIC;
#include "point4d.h"

PG_FUNCTION_INFO_V1(point4d_add);

Datum point4d_add(PG_FUNCTION_ARGS)
{
    Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
    Point4D *b = (Point4D *)PG_GETARG_POINTER(1);
    Point4D *result;

    result = (Point4D *)palloc(sizeof(Point4D));
    result->x1 = a->x1 + b->x1;
    result->x2 = a->x2 + b->x2;
    result->x3 = a->x3 + b->x3;
    result->x4 = a->x4 + b->x4;
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(point4d_eq);

Datum point4d_eq(PG_FUNCTION_ARGS)
{
    Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
    Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

    PG_RETURN_BOOL(EQ(a, b));
}

PG_FUNCTION_INFO_V1(point4d_neq);

Datum point4d_neq(PG_FUNCTION_ARGS)
{
    Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
    Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

    PG_RETURN_BOOL(!EQ(a, b));
}