CREATE FUNCTION point4d_dist(point4d, point4d) RETURNS float8 AS 'dist' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR <-> (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_dist,
   commutator = <->
);