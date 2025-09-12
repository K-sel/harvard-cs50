select distinct movies.title from movies
join ratings on movies.id = ratings.movie_id
join stars on stars.movie_id = movies.id
join people on stars.person_id = people.id
where people.name = "Chadwick Boseman"
order by ratings.rating desc limit 5;
