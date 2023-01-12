select '(0,1,1,0)'::point4d;

select p.p[0], p.p[1], p.p[2], p.p[3]
from (select '(1,2,3,4)'::point4d as p);

select ('(1,2,3,4)'::point4d)[-1];
select ('(1,2,3,4)'::point4d)[200000];

create table t (
    a point4d
);

insert into t values
    ('(0,0,0,1)'),
    ('(0,0,2,2)'),
    ('(1,1,0.5,3)'),
    ('(3,-9,2,32)');

select sum(a) from t;

drop table t;