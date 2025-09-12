select count(rating) as "films > 10.0" from movies join ratings on movies.id = ratings.movie_id where rating >= 10.0;

