--Consulta 1 sin índice
explain select count(*) from orders where status is null;

--Consulta 2 sin índice
explain select count(*) from orders where status ='Shipped';

--Consulta 1 con índice
create index i on orders(status);
explain select count(*) from orders where status is null;

--Consulta 2 con índice
explain select count(*) from orders where status ='Shipped';
drop index i;

--Consulta 1 sin índice y con analyze
analyze orders;
explain select count(*) from orders where status is null;

--Consulta 2 sin índice y con analyze
explain select count(*) from orders where status ='Shipped';

--Consulta 1 con índice y con analyze
create index i on orders(status);
explain select count(*) from orders where status is null;

--Consulta 2 con índice y con analyze
explain select count(*) from orders where status ='Shipped';

--Consulta 3 con índice y con analyze
explain select count(*) from orders where status ='Paid';

--Consulta 4 con índice y con analyze
explain select count(*) from orders where status ='Processed';

drop index i;

