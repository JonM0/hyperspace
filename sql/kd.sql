CREATE FUNCTION point4d_kdtree_config(internal, internal) RETURNS void AS 'kdtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdtree_choose(internal, internal) RETURNS void AS 'kdtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdtree_picksplit(internal, internal) RETURNS void AS 'kdtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdtree_inner_consistent(internal, internal) RETURNS void AS 'kdtree' LANGUAGE C IMMUTABLE STRICT;

CREATE FUNCTION point4d_kdtree_leaf_consistent(internal, internal) RETURNS bool AS 'kdtree' LANGUAGE C IMMUTABLE STRICT;

CREATE OPERATOR CLASS point4d_kd DEFAULT FOR TYPE point4d USING spgist AS 
OPERATOR 1 <-> (point4d, point4d) FOR ORDER BY float_ops,
OPERATOR 2 <@ (point4d, box4d),
OPERATOR 3 <@ (point4d, circle4d),
OPERATOR 4 = (point4d, point4d),
FUNCTION 1 point4d_kdtree_config(internal, internal),
FUNCTION 2 point4d_kdtree_choose(internal, internal),
FUNCTION 3 point4d_kdtree_picksplit(internal, internal),
FUNCTION 4 point4d_kdtree_inner_consistent(internal, internal),
FUNCTION 5 point4d_kdtree_leaf_consistent(internal, internal);