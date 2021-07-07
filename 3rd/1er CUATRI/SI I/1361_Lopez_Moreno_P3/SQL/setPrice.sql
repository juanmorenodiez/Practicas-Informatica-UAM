update
  orderdetail
set
  price = (
    cast(
      (
        products.price/(
          1.02 ^ (
              EXTRACT( year from CURRENT_DATE) - EXTRACT( year from orders.orderdate)
          ) 
        )
      ) as decimal(10, 2)
    ) * quantity
  )
from
  products,
  orders
where
  orderdetail.prod_id = products.prod_id
  and orderdetail.orderid = orders.orderid;
