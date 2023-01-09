CREATE FUNCTION fourd_in(cstring) RETURNS fourd AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_out(fourd) RETURNS cstring AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_recv(internal) RETURNS fourd AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_send(fourd) RETURNS bytea AS 'fourd' LANGUAGE C IMMUTABLE STRICT;

CREATE TYPE fourd (
   internallength = 32,
   input = fourd_in,
   output = fourd_out,
   receive = fourd_recv,
   send = fourd_send,
   alignment = double
);

CREATE FUNCTION fourd_eq(fourd, fourd) RETURNS bool AS 'ops' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_neq(fourd, fourd) RETURNS bool AS 'ops' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION fourd_add(fourd, fourd) RETURNS fourd AS 'ops' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR = (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_eq,
   commutator = =,
   negator = <>,
   RESTRICT = eqsel,
   JOIN = eqjoinsel
);

CREATE OPERATOR <> (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_neq,
   commutator = <>,
   negator = =,
   RESTRICT = neqsel,
   JOIN = neqjoinsel
);

CREATE OPERATOR + (
   leftarg = fourd,
   rightarg = fourd,
   PROCEDURE = fourd_add,
   commutator = +
);

CREATE AGGREGATE sum (
   sfunc = fourd_add,
   basetype = fourd,
   stype = fourd,
   initcond = '(0,0,0,0)'
);