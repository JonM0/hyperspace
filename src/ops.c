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
    result->x = a->x + b->x;
    result->y = a->y + b->y;
    result->z = a->z + b->z;
    result->w = a->w + b->w;
    PG_RETURN_POINTER(result);
}

/*
 * Point equality
 */

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

/*
 * Point in Box containment
 */

PG_FUNCTION_INFO_V1(point4d_containedin_box4d);

Datum point4d_containedin_box4d(PG_FUNCTION_ARGS)
{
    Point4D *point = (Point4D *)PG_GETARG_POINTER(0);
    Box4D *box = (Box4D *)PG_GETARG_POINTER(1);

    PG_RETURN_BOOL(CONT(box, point));
}

PG_FUNCTION_INFO_V1(box4d_contains_point4d);

Datum box4d_contains_point4d(PG_FUNCTION_ARGS)
{
    Box4D *box = (Box4D *)PG_GETARG_POINTER(0);
    Point4D *point = (Point4D *)PG_GETARG_POINTER(1);

    PG_RETURN_BOOL(CONT(box, point));
}