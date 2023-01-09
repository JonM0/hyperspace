#include "postgres.h"
#include "fmgr.h"
#include "libpq/pqformat.h"
PG_MODULE_MAGIC;
#include "fourd.h"

// Define packing and unpacking of four dimensinal type

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
