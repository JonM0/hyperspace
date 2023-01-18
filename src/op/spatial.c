#include "postgres.h"
#include "fmgr.h"
#include "math.h"
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

PG_FUNCTION_INFO_V1(point4d_dist);
Datum point4d_dist(PG_FUNCTION_ARGS)
{
    Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
    Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

    Point4D diff = DIFF(a, b);

    PG_RETURN_FLOAT8(sqrt(MAG(&diff)));
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

    PG_RETURN_BOOL(BOX_CONT(box, point));
}

PG_FUNCTION_INFO_V1(box4d_contains_point4d);

Datum box4d_contains_point4d(PG_FUNCTION_ARGS)
{
    Box4D *box = (Box4D *)PG_GETARG_POINTER(0);
    Point4D *point = (Point4D *)PG_GETARG_POINTER(1);

    PG_RETURN_BOOL(BOX_CONT(box, point));
}

/*
 * Point in Circle containment
 */

PG_FUNCTION_INFO_V1(point4d_containedin_circle4d);

Datum point4d_containedin_circle4d(PG_FUNCTION_ARGS)
{
    Point4D *point = (Point4D *)PG_GETARG_POINTER(0);
    Circle4D *circle = (Circle4D *)PG_GETARG_POINTER(1);

    Point4D diff = DIFF(&circle->center, point);

    PG_RETURN_BOOL(MAG(&diff) <= circle->radius * circle->radius);
}

PG_FUNCTION_INFO_V1(circle4d_contains_point4d);

Datum circle4d_contains_point4d(PG_FUNCTION_ARGS)
{
    Circle4D *circle = (Circle4D *)PG_GETARG_POINTER(0);
    Point4D *point = (Point4D *)PG_GETARG_POINTER(1);

    Point4D diff = DIFF(&circle->center, point);

    PG_RETURN_BOOL(MAG(&diff) <= circle->radius * circle->radius);
}