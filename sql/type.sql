-- POINT 4D
CREATE FUNCTION point4d_in(cstring) RETURNS point4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_out(point4d) RETURNS cstring AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_recv(internal) RETURNS point4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION point4d_send(point4d) RETURNS bytea AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE TYPE point4d (
   internallength = 32,
   input = point4d_in,
   output = point4d_out,
   receive = point4d_recv,
   send = point4d_send,
   alignment = double,
   element = float8
);

-- BOX 4D
CREATE FUNCTION box4d_in(cstring) RETURNS box4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION box4d_out(box4d) RETURNS cstring AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION box4d_recv(internal) RETURNS box4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION box4d_send(box4d) RETURNS bytea AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE TYPE box4d (
   internallength = 64,
   input = box4d_in,
   output = box4d_out,
   receive = box4d_recv,
   send = box4d_send,
   alignment = double,
   element = point4d
);

-- CIRCLE 4D
CREATE FUNCTION circle4d_in(cstring) RETURNS circle4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION circle4d_out(circle4d) RETURNS cstring AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION circle4d_recv(internal) RETURNS circle4d AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE FUNCTION circle4d_send(circle4d) RETURNS bytea AS '$libdir/hyperspace' LANGUAGE C IMMUTABLE STRICT PARALLEL SAFE;

CREATE TYPE circle4d (
   internallength = 40,
   input = circle4d_in,
   output = circle4d_out,
   receive = circle4d_recv,
   send = circle4d_send,
   alignment = double
);