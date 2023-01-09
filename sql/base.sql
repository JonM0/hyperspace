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