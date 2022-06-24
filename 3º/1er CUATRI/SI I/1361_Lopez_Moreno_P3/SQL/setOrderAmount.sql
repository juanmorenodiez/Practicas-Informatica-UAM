create or replace function setOrderAmount() returns void AS $$
BEGIN
update orders
set netamount = orderdetail.price,
totalamount = cast(orderdetail.price + (orderdetail.price * tax / 100) as decimal(10, 2))
from orderdetail
where orders.orderid = orderdetail.orderid AND netamount is NULL;
END;
$$ LANGUAGE plpgsql VOLATILE;
