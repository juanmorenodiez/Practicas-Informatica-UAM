--Consulta sin índice
explain select count (distinct customerid)
from orders
where totalamount > 100 and
date_part('month', orders.orderdate) = 04 and
date_part('year', orders.orderdate) = 2015;


--Indice month
create index i on orders(date_part('month', orders.orderdate));

explain select count (distinct customerid)
from orders
where totalamount > 100 and
date_part('month', orders.orderdate) = 04 and
date_part('year', orders.orderdate) = 2015;
drop index i;

--Indice year
create index i on orders(date_part('year', orders.orderdate));

explain select count (distinct customerid)
from orders
where totalamount > 100 and
date_part('month', orders.orderdate) = 04 and
date_part('year', orders.orderdate) = 2015;
drop index i;

--Indice year-month
create index i on orders(date_part('year', orders.orderdate), date_part('month', orders.orderdate));

explain select count (distinct customerid)
from orders
where totalamount > 100 and
date_part('month', orders.orderdate) = 04 and
date_part('year', orders.orderdate) = 2015;
drop index i;

--Indice month-year
create index i on orders(date_part('month', orders.orderdate), date_part('year', orders.orderdate));

explain select count (distinct customerid)
from orders
where totalamount > 100 and
date_part('month', orders.orderdate) = 04 and
date_part('year', orders.orderdate) = 2015;
drop index i;

--Indice customerid
create index i on orders(customerid);

explain select count (distinct customerid)
from orders
where totalamount > 100 and
date_part('month', orders.orderdate) = 04 and
date_part('year', orders.orderdate) = 2015;
drop index i;
