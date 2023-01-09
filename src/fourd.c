#include "postgres.h"

#include "fmgr.h"
#include "libpq/pqformat.h" /* needed for send/recv functions */

PG_MODULE_MAGIC;

typedef struct FourD
{
	double x1;
	double x2;
	double x3;
	double x4;
} FourD;

/*****************************************************************************
 * Input/Output functions
 *****************************************************************************/

PG_FUNCTION_INFO_V1(fourd_in);

Datum fourd_in(PG_FUNCTION_ARGS)
{
	char *str = PG_GETARG_CSTRING(0);
	double x1, x2, x3, x4;
	FourD *result;

	if (sscanf(str, " ( %lf, %lf, %lf, %lf )", &x1, &x2, &x3, &x4) != 4)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"fourd", str)));

	result = (FourD *)palloc(sizeof(FourD));
	result->x1 = x1;
	result->x2 = x2;
	result->x3 = x3;
	result->x4 = x4;
	PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(fourd_out);

Datum fourd_out(PG_FUNCTION_ARGS)
{
	FourD *fourd = (FourD *)PG_GETARG_POINTER(0);
	char *result;

	result = psprintf("(%g,%g,%g,%g)", fourd->x1, fourd->x2, fourd->x3, fourd->x4);
	PG_RETURN_CSTRING(result);
}

/*****************************************************************************
 * Binary Input/Output functions
 *
 * These are optional.
 *****************************************************************************/

PG_FUNCTION_INFO_V1(fourd_recv);

Datum fourd_recv(PG_FUNCTION_ARGS)
{
	StringInfo buf = (StringInfo)PG_GETARG_POINTER(0);
	FourD *result;

	result = (FourD *)palloc(sizeof(FourD));
	result->x1 = pq_getmsgfloat8(buf);
	result->x2 = pq_getmsgfloat8(buf);
	result->x3 = pq_getmsgfloat8(buf);
	result->x4 = pq_getmsgfloat8(buf);
	PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(fourd_send);

Datum fourd_send(PG_FUNCTION_ARGS)
{
	FourD *fourd = (FourD *)PG_GETARG_POINTER(0);
	StringInfoData buf;

	pq_begintypsend(&buf);
	pq_sendfloat8(&buf, fourd->x1);
	pq_sendfloat8(&buf, fourd->x2);
	pq_sendfloat8(&buf, fourd->x3);
	pq_sendfloat8(&buf, fourd->x4);
	PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}

/*****************************************************************************
 * New Operators
 *
 * A practical FourD datatype would provide much more than this, of course.
 *****************************************************************************/

PG_FUNCTION_INFO_V1(fourd_add);

Datum fourd_add(PG_FUNCTION_ARGS)
{
	FourD *a = (FourD *)PG_GETARG_POINTER(0);
	FourD *b = (FourD *)PG_GETARG_POINTER(1);
	FourD *result;

	result = (FourD *)palloc(sizeof(FourD));
	result->x1 = a->x1 + b->x1;
	result->x2 = a->x2 + b->x2;
	result->x3 = a->x3 + b->x3;
	result->x4 = a->x4 + b->x4;
	PG_RETURN_POINTER(result);
}

/*****************************************************************************
 * Operator class for defining B-tree index
 *
 * It's essential that the comparison operators and support function for a
 * B-tree index opclass always agree on the relative ordering of any two
 * data values.  Experience has shown that it's depressingly easy to write
 * unintentionally inconsistent functions.  One way to reduce the odds of
 * making a mistake is to make all the functions simple wrappers around
 * an internal three-way-comparison function, as we do here.
 *****************************************************************************/

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