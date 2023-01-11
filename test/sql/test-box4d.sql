SELECT '((0,1,1,0), (1,2,8,3))'::box4d;

SELECT '((0,5,-3,0), (1,2,8,3))'::box4d;

SELECT '((0,+inf,-3,-Inf), (1,-Inf,8,3))'::box4d;

SELECT point4d '(1,1,0,0)' <@ box4d '((0,0,0,0), (2,2,2,2))';

SELECT box4d '((0,0,0,0), (2,2,2,2))' @> point4d '(1,1,0,0)';

SELECT point4d '(1,1,0,0)' <@ box4d '((0,0,-inf,0), (2,2,2,+inf))';

SELECT point4d '(1,1,0,-1)' <@ box4d '((0,0,0,0), (2,2,2,2))';
select point4d '(1,1,3,2)' <@ box4d '((0,0,0,0), (2,2,2,2))';
