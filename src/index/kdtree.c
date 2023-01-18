#include <math.h>
#include "postgres.h"
#include "fmgr.h"
#include "access/spgist.h"
#include "catalog/pg_type.h"
#include "utils/float.h"
PG_MODULE_MAGIC;
#include "point4d.h"
#include "kdt-stratnum.h"

// to get type from name use typenameTypeId from "parser/parse_type.h"

PG_FUNCTION_INFO_V1(point4d_kdtree_config);
Datum point4d_kdtree_config(PG_FUNCTION_ARGS)
{
    // spgConfigIn *cfgin = (spgConfigIn *)PG_GETARG_POINTER(0);
    spgConfigOut *cfg = (spgConfigOut *)PG_GETARG_POINTER(1);

    cfg->prefixType = FLOAT8OID;
    cfg->labelType = VOIDOID;
    cfg->canReturnData = true;
    cfg->longValuesOK = false;

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(point4d_kdtree_choose);
Datum point4d_kdtree_choose(PG_FUNCTION_ARGS)
{
    spgChooseIn *in = (spgChooseIn *)PG_GETARG_POINTER(0);
    spgChooseOut *out = (spgChooseOut *)PG_GETARG_POINTER(1);

    Point4D *inPoint = DatumGetPoint4DP(in->datum);
    float8 split;

    out->resultType = spgMatchNode;
    out->result.matchNode.restDatum = Point4DPGetDatum(inPoint);

    if (in->allTheSame)
    {
        out->result.matchNode.levelAdd = 0;
        /* nodeN will be set by core */
        PG_RETURN_VOID();
    }

    out->result.matchNode.levelAdd = 1;

    Assert(in->hasPrefix);
    split = DatumGetFloat8(in->prefixDatum);

    Assert(in->nNodes == 2);
    out->result.matchNode.nodeN = inPoint->_v[in->level % 4] <= split ? 0 : 1;

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(point4d_kdtree_picksplit);
Datum point4d_kdtree_picksplit(PG_FUNCTION_ARGS)
{
    spgPickSplitIn *in = (spgPickSplitIn *)PG_GETARG_POINTER(0);
    spgPickSplitOut *out = (spgPickSplitOut *)PG_GETARG_POINTER(1);

    int comp = in->level % 4;
    float8 split = 0;

    for (int i = 0; i < in->nTuples; i++)
    {
        split += DatumGetPoint4DP(in->datums[i])->_v[comp];
    }

    split /= in->nTuples;

    out->hasPrefix = true;
    out->prefixDatum = Float8GetDatum(split);

    out->nNodes = 2;
    out->nodeLabels = NULL;

    out->mapTuplesToNodes = palloc(sizeof(int) * in->nTuples);
    out->leafTupleDatums = palloc(sizeof(Datum) * in->nTuples);

    for (int i = 0; i < in->nTuples; i++)
    {
        Point4D *p = DatumGetPoint4DP(in->datums[i]);

        out->leafTupleDatums[i] = Point4DPGetDatum(p);
        out->mapTuplesToNodes[i] = p->_v[comp] <= split ? 0 : 1;
    }

    PG_RETURN_VOID();
}

static double point4d_point4d_distance(const Point4D *a, const Point4D *b)
{
    Point4D diff = DIFF(a, b);

    return sqrt(MAG(&diff));
}

static double point4d_box4d_distance(const Point4D *p, const Box4D *b)
{
    Point4D distVect;

    if (p->x < b->low.x)
        distVect.x = b->low.x - p->x;
    else if (p->x > b->high.x)
        distVect.x = p->x - b->high.x;
    else
        distVect.x = 0;

    if (p->y < b->low.y)
        distVect.y = b->low.y - p->y;
    else if (p->y > b->high.y)
        distVect.y = p->y - b->high.y;
    else
        distVect.y = 0;

    if (p->z < b->low.z)
        distVect.z = b->low.z - p->z;
    else if (p->z > b->high.z)
        distVect.z = p->z - b->high.z;
    else
        distVect.z = 0;

    if (p->w < b->low.w)
        distVect.w = b->low.w - p->w;
    else if (p->w > b->high.w)
        distVect.w = p->w - b->high.w;
    else
        distVect.w = 0;

    return sqrt(MAG(&distVect));
}

static double *distances_from_box(const Box4D *box, ScanKey orderbys, int norderbys)
{
    double *distances = (double *)palloc(norderbys * sizeof(double));

    for (int i = 0; i < norderbys; i++)
    {
        Point4D *sk_point = DatumGetPoint4DP(orderbys[i].sk_argument);

        distances[i] = point4d_box4d_distance(sk_point, box);
    }

    return distances;
}

static double *distances_from_point(const Point4D *point, ScanKey orderbys, int norderbys)
{
    double *distances = (double *)palloc(norderbys * sizeof(double));

    for (int i = 0; i < norderbys; i++)
    {
        Point4D *sk_point = DatumGetPoint4DP(orderbys[i].sk_argument);

        distances[i] = point4d_point4d_distance(sk_point, point);
    }

    return distances;
}

PG_FUNCTION_INFO_V1(point4d_kdtree_inner_consistent);
Datum point4d_kdtree_inner_consistent(PG_FUNCTION_ARGS)
{
    spgInnerConsistentIn *in = (spgInnerConsistentIn *)PG_GETARG_POINTER(0);
    spgInnerConsistentOut *out = (spgInnerConsistentOut *)PG_GETARG_POINTER(1);

    Box4D infbbox;
    Box4D *bbox = NULL;

    // need bounding boxes when ordering
    if (in->norderbys > 0)
    {
        out->distances = (double **)palloc(sizeof(double *) * in->nNodes);
        out->traversalValues = (void **)palloc(sizeof(void *) * in->nNodes);

        if (in->level == 0)
        {
            double inf = get_float8_infinity();

            infbbox.high.x = inf;
            infbbox.high.y = inf;
            infbbox.high.z = inf;
            infbbox.high.w = inf;
            infbbox.low.x = -inf;
            infbbox.low.y = -inf;
            infbbox.low.z = -inf;
            infbbox.low.w = -inf;
            bbox = &infbbox;
        }
        else
        {
            bbox = in->traversalValue;
            Assert(bbox);
        }
    }

    if (in->allTheSame)
    {
        /* Report that all nodes should be visited */
        out->nNodes = in->nNodes;
        out->nodeNumbers = (int *)palloc(sizeof(int) * in->nNodes);
        for (int i = 0; i < in->nNodes; i++)
        {
            out->nodeNumbers[i] = i;

            if (in->norderbys > 0)
            {
                MemoryContext oldCtx = MemoryContextSwitchTo(in->traversalMemoryContext);
                Box4D *newbbox = palloc(sizeof(Box4D));
                MemoryContextSwitchTo(oldCtx);

                *newbbox = *bbox;

                out->traversalValues[i] = newbbox;
                out->distances[i] = distances_from_box(newbbox, in->orderbys, in->norderbys);
            }
        }

        PG_RETURN_VOID();
    }

    Assert(in->nNodes == 2);
    out->levelAdds = palloc(sizeof(int) * 2);
    for (int i = 0; i < 2; ++i)
        out->levelAdds[i] = 1;

    // choose nodes

    Assert(in->hasPrefix);
    float8 split = DatumGetFloat8(in->prefixDatum);
    int comp = in->level % 4;

    // 0 for <= split, 1 for > split
    int which = (1 << 0) | (1 << 1);

    for (int i = 0; i < in->nkeys && which != 0; i++)
    {
        switch (in->scankeys[i].sk_strategy)
        {
        case KDTEqualStrategyNumber:
        {
            Point4D *query = DatumGetPoint4DP(in->scankeys[i].sk_argument);
            which &= query->_v[comp] <= split ? (1 << 0) : (1 << 1);
        }
        break;
        case KDTContainedByBoxStrategyNumber:
        {
            Box4D *query = DatumGetBox4DP(in->scankeys[i].sk_argument);
            if (split < query->low._v[comp])
                which &= (1 << 1);
            else if (split >= query->low._v[comp])
                which &= (1 << 0);
        }
        break;
        case KDTContainedByCircleStrategyNumber:
        {
            Circle4D *query = DatumGetCircle4DP(in->scankeys[i].sk_argument);
            if (split < query->center._v[comp] - query->radius)
                which &= (1 << 1);
            else if (split >= query->center._v[comp] + query->radius)
                which &= (1 << 0);
        }
        break;
        default:
            elog(ERROR, "unrecognized strategy number: %d",
                 in->scankeys[i].sk_strategy);
            break;
        }
    }

    // return selected nodes

    out->nodeNumbers = (int *)palloc(sizeof(int) * 2);
    out->nNodes = 0;

    for (int i = 0; i < 2; i++)
    {
        if (which & (1 << i))
        {
            out->nodeNumbers[out->nNodes] = i;

            if (in->norderbys > 0)
            {
                MemoryContext oldCtx = MemoryContextSwitchTo(in->traversalMemoryContext);
                Box4D *newbbox = palloc(sizeof(Box4D));
                MemoryContextSwitchTo(oldCtx);

                *newbbox = *bbox;

                if (i == 0)
                    newbbox->high._v[comp] = split;
                else
                    newbbox->low._v[comp] = split;

                out->traversalValues[out->nNodes] = newbbox;
                out->distances[out->nNodes] = distances_from_box(newbbox, in->orderbys, in->norderbys);
            }

            out->nNodes++;
        }
    }

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(point4d_kdtree_leaf_consistent);
Datum point4d_kdtree_leaf_consistent(PG_FUNCTION_ARGS)
{
    spgLeafConsistentIn *in = (spgLeafConsistentIn *)PG_GETARG_POINTER(0);
    spgLeafConsistentOut *out = (spgLeafConsistentOut *)PG_GETARG_POINTER(1);

    Point4D *datum = DatumGetPoint4DP(in->leafDatum);
    bool res = true;

    out->recheck = false;           // all tests are exact
    out->leafValue = in->leafDatum; // leafDatum is what it is...

    for (int i = 0; i < in->nkeys && res; i++)
    {
        switch (in->scankeys[i].sk_strategy)
        {
        case KDTEqualStrategyNumber:
            res = EQ(DatumGetPoint4DP(in->scankeys[i].sk_argument), datum);
            break;

        case KDTContainedByBoxStrategyNumber:
            res = BOX_CONT(DatumGetBox4DP(in->scankeys[i].sk_argument), datum);
            break;

        case KDTContainedByCircleStrategyNumber:
        {
            Circle4D *query = DatumGetCircle4DP(in->scankeys[i].sk_argument);
            Point4D diff = DIFF(&query->center, datum);
            res = MAG(&diff) <= query->radius * query->radius;
        }
        break;

        default:
            elog(ERROR, "unrecognized strategy number: %d",
                 in->scankeys[i].sk_strategy);
            break;
        }
    }

    if (res && in->norderbys > 0)
    {
        /* ok, it passes -> let's compute the distances */
        out->distances = distances_from_point(datum, in->orderbys, in->norderbys);
    }

    PG_RETURN_BOOL(res);
}