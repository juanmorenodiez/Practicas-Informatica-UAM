# -*- coding: utf-8 -*-

import os
import sys, traceback
from sqlalchemy import create_engine
from sqlalchemy import Table, Column, Integer, String, MetaData, ForeignKey, text
from sqlalchemy.sql import select
from random import randrange
from datetime import datetime

# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False)
db_meta = MetaData(bind=db_engine)
# cargar una tabla
db_table_movies = Table('imdb_movies', db_meta, autoload=True, autoload_with=db_engine)

def db_listOfMovies1949():
    try:
        # conexion a la base de datos
        db_conn = None
        db_conn = db_engine.connect()

        # Seleccionar las peliculas del anno 1949
        db_movies_1949 = select([db_table_movies]).limit("20")
        db_result = db_conn.execute(db_movies_1949)
        #db_result = db_conn.execute("Select * from imdb_movies where year = '1949'")

        db_conn.close()

        return list(db_result)
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def checkUser(mail, psw):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        req = "select * from public.customers where email = " + "'" + mail + "'" + ";"
        
        db_result = db_conn.execute(req)

        # si existe un usuario
        if db_result.fetchone() is not None:
            #comprobar contrasena
            req = "select customerid from customers where email = '" + mail + "' and password = '" + psw + "';"
            db_result = db_conn.execute(req)

            res = db_result.fetchone()
            db_conn.close()

            if res:
                return True
            else:
                return False
        else:
            return False

        return list(db_result)
    except:
        if db_conn is not None:
            db_conn.close()
        return 'Something is broken'

def addUser(usuario, nombre, tarjeta, password, saldo):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        insert = "insert into customers (username, email, password, creditcard, income) values ('{}', '{}', '{}', {}, {})".format(
            nombre, usuario, password, tarjeta, saldo)
        db_conn.execute(insert)
        db_conn.close()
        return True
    except:
        if db_conn is not None:
            db_conn.close()
        return 'Something is broken'

def addCarrito(film, user):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        movieid = "Select movieid from imdb_movies where movietitle = '{}'".format(film)
        movieid = db_conn.execute(movieid).fetchone()[0]
        
        prodid = "Select prod_id from products where movieid = '{}'".format(movieid)
        prodid = db_conn.execute(prodid).fetchone()[0]
        
        query = "Select price from products where prod_id={}".format(prodid)
        price = db_conn.execute(query).fetchone()[0]
        

        customerid = "Select customerid from customers where email = '{}'".format(user)
        customerid = db_conn.execute(customerid).fetchone()[0]

        orderid = "Select orderid from orders where status = 'NULL' and customerid = {}".format(customerid)
        
        orderid = db_conn.execute(orderid).fetchone()
        
        #crear un order si no existe
        if orderid is None:
            
            datenow = datetime.date(datetime.now())

            create = "Insert into orders (orderdate, customerid, status, totalamount) values('{}', {}, '{}', {}) ".format(datenow, customerid, "NULL", price)
            res = db_conn.execute(create)

            orderid = "Select orderid from orders where customerid = '{}' and status = 'NULL'".format(customerid)
            orderid = db_conn.execute(orderid).fetchone()
            
        else:
            total = "Select totalamount from orders where orderid = {}".format(orderid[0])
            total = db_conn.execute(total).fetchone()[0]
            total += price
            update = "Update orders set totalamount = {} where orderid = {}".format(total, orderid[0])
            db_conn.execute(update)
        
        
        create = "Insert into orderdetail (prod_id, orderid, price, quantity) values({}, {}, {}, {}) ".format(prodid, orderid[0], price, 1)
        
        res = db_conn.execute(create)

        db_conn.close()

        return True
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def existsUser(username):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        db_user_exists = "select customerid from customers where username = '" + username + "'"

        db_result = db_conn.execute(db_user_exists)

        db_conn.close()

        if db_result.fetchone() is not None:
            return True
        else:
            return False
    except:
        if db_conn is not None:
            db_conn.close()
        return 'Something is broken'

def getTopVentas(anio):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        query = "select * from gettopventas({})".format(int(anio))

        db_result = db_conn.execute(query)
        db_conn.close()

        tabla = []

        for row in db_result:
            tabla.append({
                'year': row[0],
                'titulo': row[1],
                'ventas': row[2]
            })

        return tabla
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def getDetalles(film):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        movieid = "select movieid from imdb_movies where movietitle = '{}'".format(film)
        movieid = db_conn.execute(movieid).fetchone()[0]

        prodid = "select prod_id from products where movieid = '{}'".format(movieid)
        prodid = db_conn.execute(prodid).fetchone()[0]

        precio = "select price from products where prod_id = '{}'".format(prodid)
        precio = db_conn.execute(precio).fetchone()[0]

        db_conn.close()

        dic = {
            'titulo' : film,
            'precio' : precio
        }

        return dic
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def getSaldo(usuario):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        query = "select income from customers where email = '{}'".format(usuario)

        db_result = db_conn.execute(query)
        db_conn.close()

        for row in db_result:
            saldo = row[0]

        return saldo
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def view_cart(user):
    try:
        db_conn = None
        db_conn = db_engine.connect()
        customerid = "Select customerid from customers where email = '{}'".format(user)
        customerid = db_conn.execute(customerid).fetchone()[0]
        
        orderid = "Select orderid from orders where customerid = {} and status = 'NULL'".format(customerid)
        
        orderid = db_conn.execute(orderid).fetchone()[0]
        
        
        prodid = "Select prod_id from orderdetail where orderid = {}".format(orderid)
        prodid = db_conn.execute(prodid)

        total = "Select totalamount from orders where orderid = {} ".format(orderid)
        total = db_conn.execute(total).fetchone()[0]

        carrito = {
            'peliculas': {},
            'total' : total
        }

        for row in prodid:
            movies = "Select movieid from products where prod_id = {}".format(row[0])
            movies = db_conn.execute(movies).fetchone()[0]

            movieTitles = "Select movietitle from imdb_movies where movieid = {}".format(movies)
            movieTitles = db_conn.execute(movieTitles).fetchone()[0]
            
            prices = "Select price from products where prod_id = {}".format(row[0])
            prices = db_conn.execute(prices).fetchone()[0]
            

            carrito['peliculas'][movies] = {
                'prod_id': movies,
                'titulo': movieTitles,
                'precio': round(float(prices), 2)
            }

        db_conn.close()

        return carrito
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def purchase(user):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        customerid = "Select customerid from customers where email = '{}'".format(user)
        customerid = db_conn.execute(customerid).fetchone()[0]

        orderid = "Select orderid from orders where customerid = {} and status = 'NULL'".format(customerid)
        orderid = db_conn.execute(orderid).fetchone()[0]

        saldo = "Select income from customers where customerid = {}".format(customerid)
        saldo = db_conn.execute(saldo).fetchone()[0]

        total = "Select totalamount from orders where orderid = {}".format(orderid)
        total = db_conn.execute(total).fetchone()[0]

        if total > saldo:
            return False
        resta = saldo - total
        updateSaldo = "Update customers set income = {} where customerid = {}".format(resta, customerid)
        db_conn.execute(updateSaldo)

        update = "Update orders set status = 'paid' where orderid = {} and customerid = {}".format(orderid, customerid)
        db_conn.execute(update)
        db_conn.close()

        return True
    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'

def eliminar(user, film):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        movieid = "Select movieid from imdb_movies where movietitle = '{}'".format(film)
        movieid = db_conn.execute(movieid).fetchone()[0]
        
        prodid = "Select prod_id from products where movieid = '{}'".format(movieid)
        prodid = db_conn.execute(prodid).fetchone()[0]

        delete = "delete from orderdetail where prod_id = {}".format(prodid)
        db_conn.execute(delete)

        customerid = "Select customerid from customers where email = '{}'".format(user)
        customerid = db_conn.execute(customerid).fetchone()[0]

        orderid = "Select orderid from orders where status = 'NULL' and customerid = {}".format(customerid)
        orderid = db_conn.execute(orderid).fetchone()

        query = "Select price from products where prod_id={}".format(prodid)
        price = db_conn.execute(query).fetchone()[0]

        total = "Select totalamount from orders where orderid = {}".format(orderid[0])
        total = db_conn.execute(total).fetchone()[0]
        total -= price

        update = "Update orders set totalamount = {} where orderid = {}".format(total, orderid[0])
        db_conn.execute(update)

        return "OK"

    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'


def incrementar(user, precio, card):
    try:
        db_conn = None
        db_conn = db_engine.connect()

        tarjeta = "Select creditcard from customers where email = '{}'".format(user)
        tarjeta = db_conn.execute(tarjeta).fetchone()[0]

        if card != tarjeta:
            print("targgggsiuaed")
            return "error"

        saldo = getSaldo(user)
        saldo += int(precio)
        
        update = "Update customers set income = {} where email = '{}'".format(saldo, user)
        update = db_conn.execute(update)
        print(saldo)
        return "OK"

    except:
        if db_conn is not None:
            db_conn.close()

        return 'Something is broken'