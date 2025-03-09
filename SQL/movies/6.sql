-- To determine the average rating of all movies released in 2012.
SELECT AVG(rating) AS avg_rating
FROM ratings
JOIN movies ON ratings.movie_id = movies.id
WHERE movies.year = 2012;
