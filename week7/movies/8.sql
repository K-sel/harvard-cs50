SELECT
    name
FROM
    people
    JOIN stars ON people.id = stars.person_id
    JOIN movies ON movies.id = stars.movie_id
WHERE
    movies.id = (
        SELECT
            id
        FROM
            movies
        WHERE
            title = "Toy Story"
    );
