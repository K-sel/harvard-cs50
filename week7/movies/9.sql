select distinct name from people
join stars on people.id = stars.person_id
join movies on movies.id = stars.movie_id
where movies.id in (
    select id from movies where year = 2004
) order by people.birth asc ;
