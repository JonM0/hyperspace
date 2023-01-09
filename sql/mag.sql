CREATE FUNCTION fourd_abs_lt(fourd, fourd) RETURNS bool AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_abs_le(fourd, fourd) RETURNS bool AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_abs_eq(fourd, fourd) RETURNS bool AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_abs_ge(fourd, fourd) RETURNS bool AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_abs_gt(fourd, fourd) RETURNS bool AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR |<| (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_abs_lt,
   commutator = |>|,
   negator = |>=|,
   RESTRICT = scalarltsel,
   JOIN = scalarltjoinsel
);

CREATE OPERATOR |<=| (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_abs_le,
   commutator = |>=|,
   negator = |>|,
   RESTRICT = scalarlesel,
   JOIN = scalarlejoinsel
);

CREATE OPERATOR |=| (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_abs_eq,
   commutator = |=|,
   negator = |<>|,
   RESTRICT = eqsel,
   JOIN = eqjoinsel
);

CREATE OPERATOR |<>| (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_abs_eq,
   commutator = |<>|,
   negator = |=|,
   RESTRICT = neqsel,
   JOIN = neqjoinsel
);

CREATE OPERATOR |>=| (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_abs_ge,
   commutator = |<=|,
   negator = |<|,
   RESTRICT = scalargesel,
   JOIN = scalargejoinsel
);

CREATE OPERATOR |>| (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_abs_gt,
   commutator = |<|,
   negator = |<=|,
   RESTRICT = scalargtsel,
   JOIN = scalargtjoinsel
);

CREATE FUNCTION fourd_abs_cmp(fourd, fourd) RETURNS int4 AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR CLASS fourd_abs_ops DEFAULT FOR TYPE fourd USING btree 
AS OPERATOR 1 |<|,
OPERATOR 2 |<=|,
OPERATOR 3 |=|,
OPERATOR 4 |>=|,
OPERATOR 5 |>|,
FUNCTION 1 fourd_abs_cmp(fourd, fourd);