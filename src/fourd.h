#ifndef FOURD_T
#define FOURD_T

typedef struct FourD
{
	double x1;
	double x2;
	double x3;
	double x4;
} FourD;

#define EQ(a, b) ((a)->x1 == (b)->x1 && (a)->x2 == (b)->x2 && (a)->x3 == (b)->x3 && (a)->x4 == (b)->x4)
#define MAG(c) ((c)->x1 * (c)->x1 + (c)->x2 * (c)->x2 + (c)->x3 * (c)->x3 + (c)->x4 * (c)->x4)

#endif