select '(1,1,1,1)'::fourd = '(1,1,1,1)'::fourd;
select '(1,1,1,1)'::fourd = '(2,2,2,2)'::fourd;

select '(1,1,1,1)'::fourd = '(+1,+1,+1,+1)'::fourd;

select '(1,1,1,1)'::fourd = '(2,1,1,1)'::fourd;
select '(1,1,1,1)'::fourd = '(1,2,1,1)'::fourd;
select '(1,1,1,1)'::fourd = '(1,1,2,1)'::fourd;
select '(1,1,1,1)'::fourd = '(1,1,1,2)'::fourd;

select '(1,1,1,1)'::fourd <> '(1,1,1,1)'::fourd;
select '(1,1,1,1)'::fourd <> '(2,2,2,2)'::fourd;

select '(1,1,1,1)'::fourd <> '(2,1,1,1)'::fourd;
select '(1,1,1,1)'::fourd <> '(1,2,1,1)'::fourd;
select '(1,1,1,1)'::fourd <> '(1,1,2,1)'::fourd;
select '(1,1,1,1)'::fourd <> '(1,1,1,2)'::fourd;


select '(1,2,3,4)'::fourd  + '(5,6,7,8)'::fourd = '(6,8,10,12)'::fourd;