#include "postgres.h"
#include "fmgr.h"
#include "point4d.h"

static int
point4d_lex_cmp_internal(Point4D *a, Point4D *b)
{
	for (int c = 0; c < 4; c++)
	{
		if (a->_v[c] < b->_v[c])
			return -1;
		if (a->_v[c] > b->_v[c])
			return 1;
	}
	return 0;
}

PG_FUNCTION_INFO_V1(point4d_lex_lt);
Datum point4d_lex_lt(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_lex_cmp_internal(a, b) < 0);
}

PG_FUNCTION_INFO_V1(point4d_lex_le);
Datum point4d_lex_le(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_lex_cmp_internal(a, b) <= 0);
}

PG_FUNCTION_INFO_V1(point4d_lex_ge);
Datum point4d_lex_ge(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_lex_cmp_internal(a, b) >= 0);
}

PG_FUNCTION_INFO_V1(point4d_lex_gt);
Datum point4d_lex_gt(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(point4d_lex_cmp_internal(a, b) > 0);
}

PG_FUNCTION_INFO_V1(point4d_lex_cmp);
Datum point4d_lex_cmp(PG_FUNCTION_ARGS)
{
	Point4D *a = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *b = (Point4D *)PG_GETARG_POINTER(1);

	PG_RETURN_INT32(point4d_lex_cmp_internal(a, b));
}