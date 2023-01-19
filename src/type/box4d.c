#include "postgres.h"
#include "fmgr.h"
#include "libpq/pqformat.h"
#include "utils/float.h"
#include "point4d.h"

// Define packing and unpacking of four dimensinal box type

PG_FUNCTION_INFO_V1(box4d_in);
Datum box4d_in(PG_FUNCTION_ARGS)
{
    char *str = PG_GETARG_CSTRING(0);
    float8 x1, y1, z1, w1;
    float8 x2, y2, z2, w2;
    Box4D *result;

    if (sscanf(str, " ( ( %lf, %lf, %lf, %lf ), ( %lf, %lf, %lf, %lf ) ) ", &x1, &y1, &z1, &w1, &x2, &y2, &z2, &w2) != 8)
        ereport(ERROR,
                (errcode(ERRCODE_INVALID_TEXT_REPRESENTATION),
                 errmsg("invalid input syntax for type %s: \"%s\"",
                        "box4d", str)));

    result = (Box4D *)palloc(sizeof(Box4D));
    result->low.x = float8_min(x1, x2);
    result->low.y = float8_min(y1, y2);
    result->low.z = float8_min(z1, z2);
    result->low.w = float8_min(w1, w2);
    result->high.x = float8_max(x1, x2);
    result->high.y = float8_max(y1, y2);
    result->high.z = float8_max(z1, z2);
    result->high.w = float8_max(w1, w2);
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(box4d_out);
Datum box4d_out(PG_FUNCTION_ARGS)
{
    Box4D *box4d = (Box4D *)PG_GETARG_POINTER(0);
    char *result;

    result = psprintf("((%g,%g,%g,%g),(%g,%g,%g,%g))",
                      box4d->low.x, box4d->low.y, box4d->low.z, box4d->low.w,
                      box4d->high.x, box4d->high.y, box4d->high.z, box4d->high.w);
    PG_RETURN_CSTRING(result);
}

PG_FUNCTION_INFO_V1(box4d_recv);
Datum box4d_recv(PG_FUNCTION_ARGS)
{
    StringInfo buf = (StringInfo)PG_GETARG_POINTER(0);
    Box4D *result;

    result = (Box4D *)palloc(sizeof(Box4D));
    result->low.x = pq_getmsgfloat8(buf);
    result->low.y = pq_getmsgfloat8(buf);
    result->low.z = pq_getmsgfloat8(buf);
    result->low.w = pq_getmsgfloat8(buf);
    result->high.x = pq_getmsgfloat8(buf);
    result->high.y = pq_getmsgfloat8(buf);
    result->high.z = pq_getmsgfloat8(buf);
    result->high.w = pq_getmsgfloat8(buf);
    PG_RETURN_POINTER(result);
}

PG_FUNCTION_INFO_V1(box4d_send);
Datum box4d_send(PG_FUNCTION_ARGS)
{
    Box4D *box4d = (Box4D *)PG_GETARG_POINTER(0);
    StringInfoData buf;

    pq_begintypsend(&buf);
    pq_sendfloat8(&buf, box4d->low.x);
    pq_sendfloat8(&buf, box4d->low.y);
    pq_sendfloat8(&buf, box4d->low.z);
    pq_sendfloat8(&buf, box4d->low.w);
    pq_sendfloat8(&buf, box4d->high.x);
    pq_sendfloat8(&buf, box4d->high.y);
    pq_sendfloat8(&buf, box4d->high.z);
    pq_sendfloat8(&buf, box4d->high.w);
    PG_RETURN_BYTEA_P(pq_endtypsend(&buf));
}

PG_FUNCTION_INFO_V1(box4d);
Datum box4d(PG_FUNCTION_ARGS)
{
	Point4D *low = (Point4D *)PG_GETARG_POINTER(0);
	Point4D *high = (Point4D *)PG_GETARG_POINTER(1);

    Box4D *result;

    result = (Box4D *)palloc(sizeof(Box4D));
    result->low.x = float8_min(low->x, high->x);
    result->low.y = float8_min(low->y, high->y);
    result->low.z = float8_min(low->z, high->z);
    result->low.w = float8_min(low->w, high->w);
    result->high.x = float8_max(low->x, high->x);
    result->high.y = float8_max(low->y, high->y);
    result->high.z = float8_max(low->z, high->z);
    result->high.w = float8_max(low->w, high->w);
    PG_RETURN_POINTER(result);
}
