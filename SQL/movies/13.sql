-- To list the names of all people who starred in a movie in which Kevin Bacon also starred.
SELECT DISTINCT p2.name
FROM movies m
JOIN stars s1 ON m.id = s1.movie_id
JOIN people p1 ON p1.id = s1.person_id
JOIN stars s2 ON m.id = s2.movie_id
JOIN people p2 ON p2.id = s2.person_id
WHERE p1.name = 'Kevin Bacon'
  AND p1.birth = 1958
  AND p2.name != 'Kevin Bacon';
