#ifndef POINT4D_H
#define POINT4D_H

#include <assert.h>

typedef union Point4D
{
	struct
	{
		float8 x;
		float8 y;
		float8 z;
		float8 w;
	};
	float8 _v[4];
} Point4D;

static_assert(sizeof(Point4D) == sizeof(float8) * 4, "Undefined behaviour broke");

typedef struct Box4D
{
	Point4D low;
	Point4D high;
} Box4D;

typedef struct Circle4D
{
	Point4D center;
	float8 radius;
} Circle4D;

#define EQ(a, b) ((a)->x == (b)->x && (a)->y == (b)->y && (a)->z == (b)->z && (a)->w == (b)->w)
#define MAG(c) ((c)->x * (c)->x + (c)->y * (c)->y + (c)->z * (c)->z + (c)->w * (c)->w)

#define DIFF(a, b) { \
	.x = (a)->x - (b)->x, \
	.y = (a)->y - (b)->y, \
	.z = (a)->z - (b)->z, \
	.w = (a)->w - (b)->w, \
}

#define BOX_CONT(box, point) ((box)->low.x <= (point)->x && (box)->high.x >= (point)->x && \
							  (box)->low.y <= (point)->y && (box)->high.y >= (point)->y && \
							  (box)->low.z <= (point)->z && (box)->high.z >= (point)->z && \
							  (box)->low.w <= (point)->w && (box)->high.w >= (point)->w)

#define DatumGetPoint4DP(X) ((Point4D *)DatumGetPointer(X))
#define Point4DPGetDatum(X) PointerGetDatum(X)

#define DatumGetBox4DP(X) ((Box4D *)DatumGetPointer(X))
#define Box4DPGetDatum(X) PointerGetDatum(X)

#define DatumGetCircle4DP(X) ((Circle4D *)DatumGetPointer(X))
#define Circle4DPGetDatum(X) PointerGetDatum(X)

#endif