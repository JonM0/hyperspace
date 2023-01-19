CREATE FUNCTION point4d_lex_lt(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_lex_le(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_lex_ge(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_lex_gt(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_lex_cmp(point4d, point4d) RETURNS int4 AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE OPERATOR < (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_lex_lt,
   commutator = >,
   negator = >=,
   RESTRICT = scalarltsel,
   JOIN = scalarltjoinsel
);

CREATE OPERATOR <= (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_lex_le,
   commutator = >=,
   negator = >,
   RESTRICT = scalarlesel,
   JOIN = scalarlejoinsel
);

CREATE OPERATOR >= (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_lex_ge,
   commutator = <=,
   negator = <,
   RESTRICT = scalargesel,
   JOIN = scalargejoinsel
);

CREATE OPERATOR > (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_lex_gt,
   commutator = <,
   negator = <=,
   RESTRICT = scalargtsel,
   JOIN = scalargtjoinsel
);

CREATE OPERATOR CLASS point4d_lex_ops DEFAULT FOR TYPE point4d USING btree 
AS OPERATOR 1 <,
OPERATOR 2 <=,
OPERATOR 3 =,
OPERATOR 4 >=,
OPERATOR 5 >,
FUNCTION 1 point4d_lex_cmp(point4d, point4d);