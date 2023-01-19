select circle4d '((0,0,0,0), 1)';
select circle4d '((0,1,2,3), 2)';
select circle4d '((0,0,0,0), -0.8)';

select point4d '(0,0,0,0)' <@ circle4d '((0,0,0,0), 1)';
select point4d '(0,1,1,0)' <@ circle4d '((0,0,0,0), 1)';
select point4d '(0,0,1,0)' <@ circle4d '((0,0,0,0), 1)';

select point4d '(0.707,0.707,0,0)' <@ circle4d '((0,0,0,0), 1)';
select point4d '(0.708,0.708,0,0)' <@ circle4d '((0,0,0,0), 1)';

select circle4d('(0,0,0,0)', 1);
select circle4d('(0,0,0,0)', -23.9);