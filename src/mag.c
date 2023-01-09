#include "postgres.h"
#include "fmgr.h"
PG_MODULE_MAGIC;
#include "point4d.h"



static int
point4d_abs_cmp_internal(Point4D *a, Point4D *b)
{
	float8 amag = MAG(a),
		   bmag = MAG(b);

	if (amag < bmag)
		return -1;
	if (amag > bmag)
		return 1;
	return 0;
}

PG_FUNCTION_INFO_V1(point4d_abs_lt);

Datum point4d_abs_lt(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_abs_cmp_internal(a, b) < 0);
}

PG_FUNCTION_INFO_V1(point4d_abs_le);

Datum point4d_abs_le(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_abs_cmp_internal(a, b) <= 0);
}

PG_FUNCTION_INFO_V1(point4d_abs_eq);

Datum point4d_abs_eq(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_abs_cmp_internal(a, b) == 0);
}

PG_FUNCTION_INFO_V1(point4d_abs_neq);

Datum point4d_abs_neq(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_abs_cmp_internal(a, b) != 0);
}

PG_FUNCTION_INFO_V1(point4d_abs_ge);

Datum point4d_abs_ge(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_abs_cmp_internal(a, b) >= 0);
}

PG_FUNCTION_INFO_V1(point4d_abs_gt);

Datum point4d_abs_gt(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_abs_cmp_internal(a, b) > 0);
}

PG_FUNCTION_INFO_V1(point4d_abs_cmp);

Datum point4d_abs_cmp(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_INT32(point4d_abs_cmp_internal(a, b));
}