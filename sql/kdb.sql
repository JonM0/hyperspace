CREATE FUNCTION point4d_kdbtree_config(internal, internal) RETURNS void AS 'kdbtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdbtree_choose(internal, internal) RETURNS void AS 'kdbtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdbtree_picksplit(internal, internal) RETURNS void AS 'kdbtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdbtree_inner_consistent(internal, internal) RETURNS void AS 'kdbtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdbtree_leaf_consistent(internal, internal) RETURNS bool AS 'kdbtree' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR CLASS point4d_kdb DEFAULT FOR TYPE point4d USING spgist AS 
OPERATOR 18 = (point4d, point4d),
OPERATOR 8 <@ (point4d, box4d),
OPERATOR 15 <-> (point4d, point4d) FOR ORDER BY float_ops,
FUNCTION 1 point4d_kdbtree_config(internal, internal),
FUNCTION 2 point4d_kdbtree_choose(internal, internal),
FUNCTION 3 point4d_kdbtree_picksplit(internal, internal),
FUNCTION 4 point4d_kdbtree_inner_consistent(internal, internal),
FUNCTION 5 point4d_kdbtree_leaf_consistent(internal, internal);