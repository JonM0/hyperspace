#include "postgres.h"
#include "fmgr.h"
#include "libpq/pqformat.h"
#include "point4d.h"

// Define packing and unpacking of four dimensinal point type

PG_FUNCTION_INFO_V1(point4d_in);

Datum point4d_in(PG_FUNCTION_ARGS)
{
	char *str = PG_GETARG_CSTRING(0);
	float8 x, y, z, w;
	Point4D *result;

	if (sscanf(str, " ( %lf, %lf, %lf, %lf )", &x, &y, &z, &w) != 4)
		ereport(ERROR,
				(errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
				 errmsg("invalid input syntax for type %s: \"%s\"",
						"point4d", str)));

	result = (Point4D *)palloc(sizeof(Point4D));
	result->x = x;
	result->y = y;
	result->z = z;
	result->w = w;
	PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(point4d_out);

Datum point4d_out(PG_FUNCTION_ARGS)
{
	Point4D *point4d = (Point4D *)PG_GETARG_POINTER(0);
	char *result;

	result = psprintf("(%g,%g,%g,%g)", point4d->x, point4d->y, point4d->z, point4d->w);
	PG_RETURN_CSTRING(result);
}

PG_FUNCTION_INFO_V1(point4d_recv);

Datum point4d_recv(PG_FUNCTION_ARGS)
{
	StringInfo buf = (StringInfo)PG_GETARG_POINTER(0);
	Point4D *result;

	result = (Point4D *)palloc(sizeof(Point4D));
	result->x = pq_getmsgfloat8(buf);
	result->y = pq_getmsgfloat8(buf);
	result->z = pq_getmsgfloat8(buf);
	result->w = pq_getmsgfloat8(buf);
	PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(point4d_send);

Datum point4d_send(PG_FUNCTION_ARGS)
{
	Point4D *point4d = (Point4D *)PG_GETARG_POINTER(0);
	StringInfoData buf;

	pq_begintypsend(&buf);
	pq_sendfloat8(&buf, point4d->x);
	pq_sendfloat8(&buf, point4d->y);
	pq_sendfloat8(&buf, point4d->z);
	pq_sendfloat8(&buf, point4d->w);
	PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}
