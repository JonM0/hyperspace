create extension hyperspace;

select '(0,1,1,0)'::fourd;

create table t (
    a fourd
);

insert into t values
    ('(0,0,0,1)'),
    ('(0,0,2,2)'),
    ('(1,1,0.5,3)'),
    ('(3,-9,2,32)');

select sum(a) from t;