#include "postgres.h"
#include "fmgr.h"
PG_MODULE_MAGIC;
#include "fourd.h"


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