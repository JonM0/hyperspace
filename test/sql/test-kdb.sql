create table t (
    a point4d
);

create index t_a_kdbspgist on t using spgist(a point4d_kdb);

insert into t values
    ('(0,0,0,1)'),
    ('(0,0,1,0)'),
    ('(0,0,2,2)'),
    ('(1,1,0.5,3)'),
    ('(2,1,2,4)'),
    ('(8,0,2,1)'),
    ('(0,0,2,2)'),
    ('(1,1,0.5,3)'),
    ('(3,-9,2,32)');

set enable_seqscan=false;

explain
select a
from t
where a <@ box4d '((0,0,0,0), (1,1,1,1))';

select a
from t
where a <@ box4d '((0,0,0,0), (1,1,1,1))';


explain
select a
from t
where a = '(0,0,0,1)'::point4d;

select a
from t
where a = '(0,0,0,1)'::point4d;

explain
select a, a <-> point4d '(0,0,0,0)' as d
from t
order by d;

select a, a <-> point4d '(0,0,0,0)' as d
from t
order by d;



set enable_seqscan=true;

drop table t;