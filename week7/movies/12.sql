select distinct movies.title from movies
join stars on stars.movie_id = movies.id
join people on stars.person_id = people.id
where people.name IN ('Jennifer Lawrence', 'Bradley Cooper')
group by movies.title having count(distinct people.name) = 2;
