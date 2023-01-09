#ifndef POINT4D_H
#define POINT4D_H

typedef struct Point4D
{
	float8 x1;
	float8 x2;
	float8 x3;
	float8 x4;
} Point4D;

typedef struct Box4D
{
	Point4D low;
	Point4D high;
} Box4D;

#define EQ(a, b) ((a)->x1 == (b)->x1 && (a)->x2 == (b)->x2 && (a)->x3 == (b)->x3 && (a)->x4 == (b)->x4)
#define MAG(c) ((c)->x1 * (c)->x1 + (c)->x2 * (c)->x2 + (c)->x3 * (c)->x3 + (c)->x4 * (c)->x4)

#define P4D_COMP_I(p, i) ((i) == 0	 ? (p)->x1 \
						  : (i) == 1 ? (p)->x2 \
						  : (i) == 2 ? (p)->x3 \
									 : (p)->x4)

#define DatumGetPoint4DP(X) ((Point4D *)DatumGetPointer(X))
#define Point4DPGetDatum(X) PointerGetDatum(X)

#endif