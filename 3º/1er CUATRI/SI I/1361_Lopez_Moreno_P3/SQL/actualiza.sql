-- tabla customers
ALTER TABLE customers ALTER COLUMN email SET NOT NULL;
ALTER TABLE customers ALTER COLUMN age DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN username SET NOT NULL;
ALTER TABLE customers ALTER COLUMN firstname DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN lastname DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN address1 DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN city DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN country DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN region DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN creditcardtype DROP NOT NULL;
ALTER TABLE customers ALTER COLUMN creditcardexpiration DROP NOT NULL;

-- tabla orderdetail
ALTER TABLE orderdetail ADD FOREIGN KEY(orderid) REFERENCES orders(orderid) ON DELETE CASCADE;
ALTER TABLE orderdetail ADD FOREIGN KEY(prod_id) REFERENCES products(prod_id) ON DELETE CASCADE;

-- tabla inventory
ALTER TABLE inventory DROP CONSTRAINT inventory_pkey;
ALTER TABLE inventory ADD FOREIGN KEY(prod_id) REFERENCES products(prod_id) ON DELETE CASCADE;


-- tabla orders
ALTER TABLE orders ADD FOREIGN KEY(customerid) REFERENCES customers(customerid) ON DELETE CASCADE;
ALTER TABLE orders ALTER COLUMN customerid SET NOT NULL;

-- tabla products
ALTER TABLE products DROP CONSTRAINT products_movieid_fkey;
ALTER TABLE products ADD FOREIGN KEY(movieid) REFERENCES imdb_movies(movieid) ON DELETE CASCADE;

-- tabla imdb_actormovies
ALTER TABLE imdb_actormovies ADD FOREIGN KEY(actorid) REFERENCES imdb_actors(actorid) ON DELETE CASCADE;
ALTER TABLE imdb_actormovies ADD FOREIGN KEY(movieid) REFERENCES imdb_movies(movieid) ON DELETE CASCADE;

-- tabla imdb_directormovies
DROP SEQUENCE imdb_directormovies_directorid_seq CASCADE;
DROP SEQUENCE imdb_directormovies_movieid_seq CASCADE;
ALTER TABLE imdb_directormovies DROP CONSTRAINT imdb_directormovies_pkey;
ALTER TABLE imdb_directormovies DROP CONSTRAINT imdb_directormovies_directorid_fkey;
ALTER TABLE imdb_directormovies DROP CONSTRAINT imdb_directormovies_movieid_fkey;
ALTER TABLE imdb_directormovies ADD FOREIGN KEY(directorid) REFERENCES imdb_directors(directorid) ON DELETE CASCADE;
ALTER TABLE imdb_directormovies ADD FOREIGN KEY(movieid) REFERENCES imdb_movies(movieid) ON DELETE CASCADE;

-- creamos tabla movie_countries
CREATE TABLE movie_countries AS (SELECT DISTINCT country FROM imdb_moviecountries);
ALTER TABLE movie_countries ADD PRIMARY KEY (country);

-- tabla imdb_moviecountries table
ALTER TABLE imdb_moviecountries ADD FOREIGN KEY(country) REFERENCES movie_countries(country) ON DELETE CASCADE;

-- creamos tabla movie_genres
CREATE TABLE movie_genres AS (SELECT DISTINCT genre FROM imdb_moviegenres);
ALTER TABLE movie_genres ADD PRIMARY KEY (genre);

-- tabla imdb_moviecountries table
ALTER TABLE imdb_moviegenres ADD FOREIGN KEY(genre) REFERENCES movie_genres(genre) ON DELETE CASCADE;

-- creamos tabla movie_languages
CREATE TABLE movie_languages AS (SELECT DISTINCT language FROM imdb_movielanguages);
ALTER TABLE movie_languages ADD PRIMARY KEY (language);

-- tabla imdb_languages table
ALTER TABLE imdb_movielanguages ADD FOREIGN KEY(language) REFERENCES movie_languages(language) ON DELETE CASCADE;

-- anade nuevo id a partir del ultimo usado
ALTER SEQUENCE customers_customerid_seq restart with 14094;

ALTER SEQUENCE orders_orderid_seq restart with 181791;

