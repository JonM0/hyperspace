CREATE FUNCTION point4d_abs_lt(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_abs_le(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_abs_eq(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_abs_neq(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_abs_ge(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_abs_gt(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_abs_cmp(point4d, point4d) RETURNS int4 AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR |<| (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_abs_lt,
   commutator = |>|,
   negator = |>=|,
   RESTRICT = scalarltsel,
   JOIN = scalarltjoinsel
);

CREATE OPERATOR |<=| (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_abs_le,
   commutator = |>=|,
   negator = |>|,
   RESTRICT = scalarlesel,
   JOIN = scalarlejoinsel
);

CREATE OPERATOR |=| (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_abs_eq,
   commutator = |=|,
   negator = |<>|,
   RESTRICT = eqsel,
   JOIN = eqjoinsel
);

CREATE OPERATOR |<>| (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_abs_neq,
   commutator = |<>|,
   negator = |=|,
   RESTRICT = neqsel,
   JOIN = neqjoinsel
);

CREATE OPERATOR |>=| (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_abs_ge,
   commutator = |<=|,
   negator = |<|,
   RESTRICT = scalargesel,
   JOIN = scalargejoinsel
);

CREATE OPERATOR |>| (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_abs_gt,
   commutator = |<|,
   negator = |<=|,
   RESTRICT = scalargtsel,
   JOIN = scalargtjoinsel
);

CREATE OPERATOR CLASS point4d_abs_ops DEFAULT FOR TYPE point4d USING btree 
AS OPERATOR 1 |<|,
OPERATOR 2 |<=|,
OPERATOR 3 |=|,
OPERATOR 4 |>=|,
OPERATOR 5 |>|,
FUNCTION 1 point4d_abs_cmp(point4d, point4d);