CREATE FUNCTION point4d_eq(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_dist(point4d, point4d) RETURNS float8 AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_neq(point4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_add(point4d, point4d) RETURNS point4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR = (
    leftarg = point4d,
    rightarg = point4d,
    PROCEDURE = point4d_eq,
    commutator = =,
    negator = <>,
    RESTRICT = eqsel,
    JOIN = eqjoinsel
);

CREATE OPERATOR <->(
    leftarg = point4d,
    rightarg = point4d,
    PROCEDURE = point4d_dist,
    commutator = <->
);

CREATE OPERATOR <> (
    leftarg = point4d,
    rightarg = point4d,
    PROCEDURE = point4d_neq,
    commutator = <>,
    negator = =,
    RESTRICT = neqsel,
    JOIN = neqjoinsel
);

CREATE OPERATOR + (
    leftarg = point4d,
    rightarg = point4d,
    PROCEDURE = point4d_add,
    commutator = +
);

CREATE AGGREGATE sum (
    sfunc = point4d_add,
    basetype = point4d,
    stype = point4d,
    initcond = '(0,0,0,0)'
);

-- CONTAINMENT
CREATE FUNCTION point4d_containedin_box4d(point4d, box4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION box4d_contains_point4d(box4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR <@ (
    leftarg = point4d,
    rightarg = box4d,
    PROCEDURE = point4d_containedin_box4d,
    commutator = @>,
    JOIN = contjoinsel
);

CREATE OPERATOR @> (
    leftarg = box4d,
    rightarg = point4d,
    PROCEDURE = box4d_contains_point4d,
    commutator = <@,
    JOIN = contjoinsel
);

CREATE FUNCTION point4d_containedin_circle4d(point4d, circle4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION circle4d_contains_point4d(circle4d, point4d) RETURNS bool AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR <@ (
    leftarg = point4d,
    rightarg = circle4d,
    PROCEDURE = point4d_containedin_circle4d,
    commutator = @>,
    JOIN = contjoinsel
);

CREATE OPERATOR @> (
    leftarg = circle4d,
    rightarg = point4d,
    PROCEDURE = circle4d_contains_point4d,
    commutator = <@,
    JOIN = contjoinsel
);