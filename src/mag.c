#include "postgres.h"
#include "fmgr.h"
PG_MODULE_MAGIC;
#include "fourd.h"


#define Mag(c) ((c)->x1 * (c)->x1 + (c)->x2 * (c)->x2 + (c)->x3 * (c)->x3 + (c)->x4 * (c)->x4)

static int
fourd_abs_cmp_internal(FourD *a, FourD *b)
{
	double amag = Mag(a),
		   bmag = Mag(b);

	if (amag < bmag)
		return -1;
	if (amag > bmag)
		return 1;
	return 0;
}

PG_FUNCTION_INFO_V1(fourd_abs_lt);

Datum fourd_abs_lt(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(fourd_abs_cmp_internal(a, b) < 0);
}

PG_FUNCTION_INFO_V1(fourd_abs_le);

Datum fourd_abs_le(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(fourd_abs_cmp_internal(a, b) <= 0);
}

PG_FUNCTION_INFO_V1(fourd_abs_eq);

Datum fourd_abs_eq(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(fourd_abs_cmp_internal(a, b) == 0);
}

PG_FUNCTION_INFO_V1(fourd_abs_neq);

Datum fourd_abs_neq(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(fourd_abs_cmp_internal(a, b) != 0);
}

PG_FUNCTION_INFO_V1(fourd_abs_ge);

Datum fourd_abs_ge(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(fourd_abs_cmp_internal(a, b) >= 0);
}

PG_FUNCTION_INFO_V1(fourd_abs_gt);

Datum fourd_abs_gt(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_BOOL(fourd_abs_cmp_internal(a, b) > 0);
}

PG_FUNCTION_INFO_V1(fourd_abs_cmp);

Datum fourd_abs_cmp(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);

	PG_RETURN_INT32(fourd_abs_cmp_internal(a, b));
}