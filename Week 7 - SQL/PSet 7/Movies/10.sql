SELECT people.name FROM people WHERE id IN
(SELECT DISTINCT(d.person_id) FROM directors AS d WHERE movie_id IN
  (SELECT id FROM movies WHERE id IN
    (SELECT ratings.movie_id FROM ratings WHERE rating >= 9.0)));