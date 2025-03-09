-- To list the titles of all movies in which both Bradley Cooper and Jennifer Lawrence starred
SELECT title
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN people p1 ON p1.id = s1.person_id
JOIN stars s2 ON m.id = s2.movie_id
JOIN people p2 ON p2.id = s2.person_id
WHERE p1.name = 'Bradley Cooper' AND p2.name = 'Jennifer Lawrence';
