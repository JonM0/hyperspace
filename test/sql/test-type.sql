select '(0,1,1,0)'::point4d;

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