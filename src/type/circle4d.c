#include "postgres.h"
#include "fmgr.h"
#include "libpq/pqformat.h"
#include "utils/float.h"
#include "point4d.h"

// Define packing and unpacking of four dimensinal sphere type

PG_FUNCTION_INFO_V1(circle4d_in);

Datum circle4d_in(PG_FUNCTION_ARGS)
{
    char *str = PG_GETARG_CSTRING(0);
    float8 x, y, z, w, r;
    Circle4D *result;

    if (sscanf(str, " ( ( %lf, %lf, %lf, %lf ), %lf ) ", &x, &y, &z, &w, &r) != 5)
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid input syntax for type %s: \"%s\"",
                        "circle4d", str)));

    result = (Circle4D *)palloc(sizeof(Circle4D));
    result->center.x = x;
    result->center.y = y;
    result->center.z = z;
    result->center.w = w;
    result->radius = r < 0 ? -r : r;
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(circle4d_out);

Datum circle4d_out(PG_FUNCTION_ARGS)
{
    Circle4D *circle4d = (Circle4D *)PG_GETARG_POINTER(0);
    char *result;

    result = psprintf("((%g,%g,%g,%g),%g)",
                      circle4d->center.x, circle4d->center.y, circle4d->center.z, circle4d->center.w,
                      circle4d->radius);
    PG_RETURN_CSTRING(result);
}

PG_FUNCTION_INFO_V1(circle4d_recv);

Datum circle4d_recv(PG_FUNCTION_ARGS)
{
    StringInfo buf = (StringInfo)PG_GETARG_POINTER(0);
    Circle4D *result;

    result = (Circle4D *)palloc(sizeof(Circle4D));
    result->center.x = pq_getmsgfloat8(buf);
    result->center.y = pq_getmsgfloat8(buf);
    result->center.z = pq_getmsgfloat8(buf);
    result->center.w = pq_getmsgfloat8(buf);
    result->radius = pq_getmsgfloat8(buf);
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(circle4d_send);

Datum circle4d_send(PG_FUNCTION_ARGS)
{
    Circle4D *circle4d = (Circle4D *)PG_GETARG_POINTER(0);
    StringInfoData buf;

    pq_begintypsend(&buf);
    pq_sendfloat8(&buf, circle4d->center.x);
    pq_sendfloat8(&buf, circle4d->center.y);
    pq_sendfloat8(&buf, circle4d->center.z);
    pq_sendfloat8(&buf, circle4d->center.w);
    pq_sendfloat8(&buf, circle4d->radius);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}
