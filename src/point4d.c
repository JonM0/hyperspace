#include "postgres.h"
#include "fmgr.h"
#include "libpq/pqformat.h"
PG_MODULE_MAGIC;
#include "point4d.h"

// Define packing and unpacking of four dimensinal type

PG_FUNCTION_INFO_V1(point4d_in);

Datum point4d_in(PG_FUNCTION_ARGS)
{
	char *str = PG_GETARG_CSTRING(0);
	float8 x1, x2, x3, x4;
	Point4D *result;

	if (sscanf(str, " ( %lf, %lf, %lf, %lf )", &x1, &x2, &x3, &x4) != 4)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"point4d", str)));

	result = (Point4D *)palloc(sizeof(Point4D));
	result->x1 = x1;
	result->x2 = x2;
	result->x3 = x3;
	result->x4 = x4;
	PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(point4d_out);

Datum point4d_out(PG_FUNCTION_ARGS)
{
	Point4D *point4d = (Point4D *)PG_GETARG_POINTER(0);
	char *result;

	result = psprintf("(%g,%g,%g,%g)", point4d->x1, point4d->x2, point4d->x3, point4d->x4);
	PG_RETURN_CSTRING(result);
}

PG_FUNCTION_INFO_V1(point4d_recv);

Datum point4d_recv(PG_FUNCTION_ARGS)
{
	StringInfo buf = (StringInfo)PG_GETARG_POINTER(0);
	Point4D *result;

	result = (Point4D *)palloc(sizeof(Point4D));
	result->x1 = pq_getmsgfloat8(buf);
	result->x2 = pq_getmsgfloat8(buf);
	result->x3 = pq_getmsgfloat8(buf);
	result->x4 = pq_getmsgfloat8(buf);
	PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(point4d_send);

Datum point4d_send(PG_FUNCTION_ARGS)
{
	Point4D *point4d = (Point4D *)PG_GETARG_POINTER(0);
	StringInfoData buf;

	pq_begintypsend(&buf);
	pq_sendfloat8(&buf, point4d->x1);
	pq_sendfloat8(&buf, point4d->x2);
	pq_sendfloat8(&buf, point4d->x3);
	pq_sendfloat8(&buf, point4d->x4);
	PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}
