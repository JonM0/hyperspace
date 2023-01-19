create table t (
    a point4d
);

create index t_a_btree on t using btree(a);

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

explain
select a
from t
where a = '(1,0,0,0)'::point4d;

select a
from t
where a = '(1,0,0,0)'::point4d;

explain
select a
from t
where a <= '(1,0,0,0)'::point4d;

select a
from t
where a <= '(1,0,0,0)'::point4d;

drop table t;