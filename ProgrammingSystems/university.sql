--mySQL:
  --q1.
    select title from course where credits=3;

  --q2.
    select c.course_id, c.title from course c join takes t on c.course_id = t.course_id where t.ID=76543;

  --q3.
    select dept_name from instructor group by dept_name having count(*) > 2;

