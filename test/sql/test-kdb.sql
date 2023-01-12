CREATE TABLE t (a point4d);

CREATE INDEX t_a_kdbspgist ON t USING spgist(a point4d_kdb);

INSERT INTO t
VALUES ('(0,0,0,1)'),
    ('(0,1,0,0)'),
    ('(0,0,2,2)'),
    ('(1,1,0.5,3)'),
    ('(2,1,2,4)'),
    ('(8,0,2,1)'),
    ('(0,0,2,2)'),
    ('(1,1,0.5,3)'),
    ('(3,-9,2,32)');

SET enable_seqscan = false;

EXPLAIN
SELECT a
FROM t
WHERE a <@ box4d '((0,0,0,0), (1,1,1,1))';

SELECT a
FROM t
WHERE a <@ box4d '((0,0,0,0), (1,1,1,1))';

EXPLAIN
SELECT a
FROM t
WHERE a = '(0,0,0,1)'::point4d;

SELECT a
FROM t
WHERE a = '(0,0,0,1)'::point4d;

EXPLAIN
SELECT a,
    a <->point4d '(0,0,2.34,0)' AS d
FROM t
ORDER BY d;

SELECT a,
    a <->point4d '(0,0,2.34,0)' AS d
FROM t
ORDER BY d;

EXPLAIN
SELECT a,
    a <->point4d '(0,0,0,0)' AS d1,
    a <->point4d '(0,1.12,0,0)' AS d2
FROM t
ORDER BY d1,
    d2;

SELECT a,
    a <->point4d '(0,0,0,0)' AS d1,
    a <->point4d '(0,1.12,0,0)' AS d2
FROM t
ORDER BY d1,
    d2;

EXPLAIN
SELECT a,
    a <->point4d '(0,0,0,0)' AS d1,
    a <->point4d '(0,1.12,0,0)' AS d2
FROM t
WHERE a <@ box4d '((0,0,0,0), (1,1,inf,inf))'
ORDER BY d1,
    d2;

SELECT a,
    a <->point4d '(0,0,0,0)' AS d1,
    a <->point4d '(0,1.12,0,0)' AS d2
FROM t
WHERE a <@ box4d '((0,0,0,0), (1,1,inf,inf))'
ORDER BY d1,
    d2;

SET enable_seqscan = TRUE;
DROP INDEX t_a_kdbspgist;

SELECT a,
    a <->point4d '(0,0,2.34,0)' AS d
FROM t
ORDER BY d;

SELECT a,
    a <->point4d '(0,0,0,0)' AS d1,
    a <->point4d '(0,1.12,0,0)' AS d2
FROM t
ORDER BY d1,
    d2;


DROP TABLE t;