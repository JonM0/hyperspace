CREATE FUNCTION point4d_in(cstring) RETURNS point4d AS 'point4d' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_out(point4d) RETURNS cstring AS 'point4d' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_recv(internal) RETURNS point4d AS 'point4d' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_send(point4d) RETURNS bytea AS 'point4d' LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE point4d (
   internallength = 32,
   input = point4d_in,
   output = point4d_out,
   receive = point4d_recv,
   send = point4d_send,
   alignment = float8
);

CREATE FUNCTION point4d_eq(point4d, point4d) RETURNS bool AS 'ops' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_neq(point4d, point4d) RETURNS bool AS 'ops' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_add(point4d, point4d) RETURNS point4d AS 'ops' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR = (
   leftarg = point4d,
   rightarg = point4d,
   PROCEDURE = point4d_eq,
   commutator = =,
   negator = <>,
   RESTRICT = eqsel,
   JOIN = eqjoinsel
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

-- BOX 4D
CREATE FUNCTION box4d_in(cstring) RETURNS box4d AS 'box4d' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION box4d_out(box4d) RETURNS cstring AS 'box4d' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION box4d_recv(internal) RETURNS box4d AS 'box4d' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION box4d_send(box4d) RETURNS bytea AS 'box4d' LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE box4d (
   internallength = 32,
   input = box4d_in,
   output = box4d_out,
   receive = box4d_recv,
   send = box4d_send,
   alignment = float8
);

CREATE FUNCTION point4d_containedin_box4d(point4d, box4d) RETURNS bool AS 'ops' LANGUAGE C IMMUTABLE STRICT;
CREATE FUNCTION box4d_contains_point4d(box4d, point4d) RETURNS bool AS 'ops' LANGUAGE C IMMUTABLE STRICT;

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