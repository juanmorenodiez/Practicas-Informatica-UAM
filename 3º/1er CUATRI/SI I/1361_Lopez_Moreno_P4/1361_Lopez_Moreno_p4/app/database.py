# -*- coding: utf-8 -*-

import os
import sys, traceback, time

from sqlalchemy import create_engine

# configurar el motor de sqlalchemy
db_engine = create_engine("postgresql://alumnodb:alumnodb@localhost/si1", echo=False, execution_options={"autocommit":False})

def dbConnect():
    return db_engine.connect()

def dbCloseConnect(db_conn):
    db_conn.close()

def getListaCliMes(db_conn, mes, anio, iumbral, iintervalo, use_prepare, break0, niter):
    dbr=[]
    res = {}
    # TODO: implementar la consulta; asignar nombre 'cc' al contador resultante
    consultaPrepare = """PREPARE clientes (int) AS
                select count(distinct customerid) as cc
                from orders where totalamount > $1 and
                date_part('year', orders.orderdate) = $2 and
                date_part('month', orders.orderdate) = $3;"""

    if use_prepare is True:

    # TODO: ejecutar la consulta
    # - mediante PREPARE, EXECUTE, DEALLOCATE si use_prepare es True
    # - mediante db_conn.execute() si es False

    # Array con resultados de la consulta para cada umbral
        db_conn.execute(consultaPrepare)

        for ii in range(niter):

            # TODO: ...
            result = db_conn.execute("EXECUTE clientes({}, {}, {});".format(iumbral, anio, mes))
            res = result.first()

            # Guardar resultado de la query
            dbr.append({"umbral":iumbral,"contador":res['cc']})

            # TODO: si break0 es True, salir si contador resultante es cero
            if break0 and res['cc'] == 0:
                break

            # Actualizacion de umbral
            iumbral = iumbral + iintervalo
        db_conn.execute("Deallocate clientes;")

    else:
        for ii in range(niter):
            consultaExecute ="""select count(distinct customerid) as cc
                            from orders where totalamount > {} and
                            date_part('year', orders.orderdate) = {} and
                            date_part('month', orders.orderdate) = {}""".format(iumbral, anio, mes)
            result = db_conn.execute(consultaExecute)
            res = result.first()

            # Guardar resultado de la query
            dbr.append({"umbral": iumbral, "contador": res['cc']})

            if break0 and res['cc'] == 0:
                break

            # Actualizacion de umbral
            iumbral = iumbral + iintervalo

    return dbr


def getMovies(anio):
    # conexion a la base de datos
    db_conn = db_engine.connect()

    query="select movietitle from imdb_movies where year = '" + anio + "'"
    resultproxy=db_conn.execute(query)

    a = []
    for rowproxy in resultproxy:
        d={}
        # rowproxy.items() returns an array like [(key0, value0), (key1, value1)]
        for tup in rowproxy.items():
            # build up the dictionary
            d[tup[0]] = tup[1]
        a.append(d)

    resultproxy.close()

    db_conn.close()

    return a

def getCustomer(username, password):
    # conexion a la base de datos
    db_conn = db_engine.connect()

    query="select * from customers where username='" + username + "' and password='" + password + "'"
    res = db_conn.execute(query).first()

    db_conn.close()

    if res is None:
        return None
    else:
        return {'firstname': res['firstname'], 'lastname': res['lastname']}

def delCustomer(customerid, bFallo, bSQL, duerme, bCommit):
    # Array de trazas a mostrar en la página
    dbr=[]
    db_conn = db_engine.connect()

    # TODO: Ejecutar consultas de borrado
    # - ordenar consultas según se desee provocar un error (bFallo True) o no
    # - ejecutar commit intermedio si bCommit es True
    # - usar sentencias SQL ('BEGIN', 'COMMIT', ...) si bSQL es True
    # - suspender la ejecución 'duerme' segundos en el punto adecuado para forzar deadlock
    # - ir guardando trazas mediante dbr.append()

    # si bSQL es true hacemos el begin con execute, sino mediante transaccion
    if bSQL is True:
        db_conn.execute("Begin")
    else:
        transaccion = db_conn.begin()

    try:
        # TODO: ejecutar consultas
        orderid = "select orderid from orders where customerid={}".format(customerid)
        res = db_conn.execute(orderid)
        traza = "obtener orderid del customer nº: {}".format(customerid)
        dbr.append(traza)


        for elem in res:
            delete1 = "delete from orderdetail where orderid={}".format(elem[0])
            traza = "eliminar orderdetail nº: {}".format(elem[0])
            dbr.append(traza)
            db_conn.execute(delete1)

        #commit intermedio
        #si bsql es true hacemos ek commit y begin con execute, sino mediante transaccion
        if bCommit is True:
            if bSQL is True:
                dbr.append('Commit')
                db_conn.execute("Commit")
                dbr.append('Begin')
                db_conn.execute("Begin")
            else:
                transaccion.commit()
                dbr.append('Commit')
                dbr.append('Begin')
                transaccion = db_conn.begin()


        #forzamos fallo
        if bFallo is True:
            delete2 = "delete from customers where customerid={}".format(customerid)
            traza = "eliminar customer nº: {}".format(customerid)
            dbr.append(traza)
            db_conn.execute(delete2)

        delete3 = "delete from orders where customerid={}".format(customerid)
        traza = "eliminar order del customer nº: {}".format(customerid)
        dbr.append(traza)
        db_conn.execute(delete3)

        #forzamos deadlock
        time.sleep(duerme)
        delete4 = "delete from customers where customerid={}".format(customerid)
        traza = "eliminar customer nº: {}".format(customerid)
        dbr.append(traza)
        db_conn.execute(delete4)

        #si bsql es true hacemos ek commit con execute, sino mediante transaccion
        if bSQL is True:
            db_conn.execute("Commit")
            dbr.append('Commit')
        else:
            transaccion.commit()
            dbr.append('Commit')

    except Exception as e:
        # TODO: deshacer en caso de error
        #si bsql es true hacemos ek rollback con execute, sino mediante transaccion
        if bSQL is True:
            dbr.append('Rollback')
            db_conn.execute("Rollback")
        else:
            transaccion.rollback()
            dbr.append('Rollback')

    #no sirve para nada este esle
    #else:

    db_conn.close()
    return dbr
