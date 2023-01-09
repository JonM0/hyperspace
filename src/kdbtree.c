#include <math.h>
#include "postgres.h"
#include "fmgr.h"
#include "access/spgist.h"
#include "catalog/pg_type.h"
PG_MODULE_MAGIC;
#include "point4d.h"

// to get type from name use typenameTypeId from "parser/parse_type.h"

PG_FUNCTION_INFO_V1(point4d_kdbtree_config);
Datum point4d_kdbtree_config(PG_FUNCTION_ARGS)
{
    spgConfigIn *cfgin = (spgConfigIn *)PG_GETARG_POINTER(0);
    spgConfigOut *cfg = (spgConfigOut *)PG_GETARG_POINTER(1);

    cfg->prefixType = FLOAT8OID;
    cfg->labelType = VOIDOID;
    cfg->canReturnData = true;
    cfg->longValuesOK = false;

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(point4d_kdbtree_choose);
Datum point4d_kdbtree_choose(PG_FUNCTION_ARGS)
{
    spgChooseIn *in = (spgChooseIn *)PG_GETARG_POINTER(0);
    spgChooseOut *out = (spgChooseOut *)PG_GETARG_POINTER(1);

    Point4D *inPoint = DatumGetPoint4DP(in->datum);
    float8 split;

    out->resultType = spgMatchNode;
    out->result.matchNode.levelAdd = 1;
    out->result.matchNode.restDatum = Point4DPGetDatum(inPoint);

    if (in->allTheSame)
    {
        /* nodeN will be set by core */
        PG_RETURN_VOID();
    }

    Assert(in->hasPrefix);
    split = DatumGetFloat8(in->prefixDatum);

    Assert(in->nNodes == 2);
    out->result.matchNode.nodeN = P4D_COMP_I(inPoint, in->level % 4) <= split ? 0 : 1;

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(point4d_kdbtree_picksplit);
Datum point4d_kdbtree_picksplit(PG_FUNCTION_ARGS)
{
    spgPickSplitIn *in = (spgPickSplitIn *)PG_GETARG_POINTER(0);
    spgPickSplitOut *out = (spgPickSplitOut *)PG_GETARG_POINTER(1);

    int n = in->level % 4;
    float8 split;

    for (int i = 0; i < in->nTuples; i++)
    {
        split += P4D_COMP_I(DatumGetPoint4DP(in->datums[i]), n);
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
        out->mapTuplesToNodes[i] = P4D_COMP_I(p, n) <= split ? 0 : 1;
    }

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(point4d_kdbtree_inner_consistent);
Datum point4d_kdbtree_inner_consistent(PG_FUNCTION_ARGS)
{
    spgInnerConsistentIn *in = (spgInnerConsistentIn *)PG_GETARG_POINTER(0);
    spgInnerConsistentOut *out = (spgInnerConsistentOut *)PG_GETARG_POINTER(1);

    PG_RETURN_VOID();
}

PG_FUNCTION_INFO_V1(spg_quad_leaf_consistent);
Datum spg_quad_leaf_consistent(PG_FUNCTION_ARGS)
{
    spgLeafConsistentIn *in = (spgLeafConsistentIn *)PG_GETARG_POINTER(0);
    spgLeafConsistentOut *out = (spgLeafConsistentOut *)PG_GETARG_POINTER(1);

    PG_RETURN_BOOL(false);
}