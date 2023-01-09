CREATE FUNCTION fourd_dist(fourd, fourd) RETURNS float8 AS 'dist' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR <-> (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_dist,
   commutator = <->
);