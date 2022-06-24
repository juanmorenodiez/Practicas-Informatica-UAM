CREATE OR REPLACE FUNCTION getTopVentas(anio int) 
RETURNS Table(
  ANYO integer,
  PELICULA text,
  VENTAS integer
) AS $$ 

BEGIN 
  return QUERY
    SELECT distinct
        ON (anno) date_part ('year', orderdate)::integer AS anno, movietitle :: text as pelicula, sum (quantity)::integer AS ventas
    FROM orderdetail
    INNER JOIN products
        ON products.prod_id  = orderdetail.prod_id
    NATURAL JOIN imdb_movies
    NATURAL JOIN orders 
    WHERE date_part ('year', orderdate)::integer >= anio
    GROUP BY  anno, movietitle
    ORDER BY  anno asc, ventas desc;
END;

$$ LANGUAGE plpgsql STABLE; 
