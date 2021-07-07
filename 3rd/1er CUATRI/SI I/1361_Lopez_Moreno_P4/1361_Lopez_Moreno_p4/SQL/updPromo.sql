--Creamos columna promo en la tabla customers
alter table customers add column promo decimal(5,2);

--Creamos trigger
create or replace function updPromo() RETURNS trigger as
  'begin
  update orders
  set totalamount = totalamount - (totalamount*(NEW.promo/100))
  where customerid = NEW.customerid and orders.status is NULL;
  perform pg_sleep(10);
  return new;
end;'
language plpgsql;

CREATE TRIGGER updPromoTrigger AFTER UPDATE ON customers FOR EACH ROW EXECUTE PROCEDURE updPromo();

--Creamos varios carritos
update orders
set status = NULL
where orderid = 21166;

update orders
set status = NULL
where orderid = 103353;

update orders
set status = NULL
where orderid = 28745;

update orders
set status = NULL
where orderid = 113079;
