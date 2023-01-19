SELECT '((0,1,1,0), (1,2,8,3))'::box4d;

SELECT '((0,5,-3,0), (1,2,8,3))'::box4d;

SELECT ('((1,2,3,4), (6,7,8,9))'::box4d)[0];
SELECT ('((1,2,3,4), (6,7,8,9))'::box4d)[1];

SELECT (('((1,2,3,4), (6,7,8,9))'::box4d)[0])[2];

select box4d('(1,2,3,4)', '(-2,4,-4.12, 12)');
select box4d(point4d(1,2,34,2), point4d(2,3,1,6));

SELECT '((0,+inf,-3,-Inf), (1,-Inf,8,3))'::box4d;

SELECT point4d '(1,1,0,0)' <@ box4d '((0,0,0,0), (2,2,2,2))';

SELECT box4d '((0,0,0,0), (2,2,2,2))' @> point4d '(1,1,0,0)';

SELECT point4d '(1,1,0,0)' <@ box4d '((0,0,-inf,0), (2,2,2,+inf))';

SELECT point4d '(1,1,0,-1)' <@ box4d '((0,0,0,0), (2,2,2,2))';
select point4d '(1,1,3,2)' <@ box4d '((0,0,0,0), (2,2,2,2))';
