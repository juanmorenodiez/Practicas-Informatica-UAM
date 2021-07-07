#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from flask import render_template, request, url_for, redirect, session, make_response
from random import randrange
import json
import os
import sys
import hashlib
from app import database
import random

@app.route("/setCookie/<user>")
def setCookie(mail):
    msg = "user cookie set to: " + mail
    response = make_response(render_template('login.html', mensaje = msg))
    response.set_cookie('helloflask_user', mail)
    return response

@app.route("/getCookie")
def getCookie():
    user_id = request.cookies.get('helloflask_user')
    if user_id:
        msg = "user is: " + user_id

    else:
        msg = "no user cookie"

    return render_template('login.html', mensaje = msg)

@app.route('/')
@app.route('/index', methods=['GET', 'POST'])
def index():
    list = []
    print (url_for('static', filename='estilo.css'), file=sys.stderr)
    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)

    #mostrar al inicio las peliculas mas vendidas
    topVentas = database.getTopVentas(2008)

    if 'busqueda' in request.form:
        for elemento in catalogue['peliculas']:
            if elemento.get('titulo') == request.form['busqueda']:
                list.append(elemento)
                return render_template('index.html', title = "Home", movies=list)

    if 'categoria' in request.args:
        for elemento in catalogue['peliculas']:
            if elemento.get('categoria') == request.args['categoria']:
                list.append(elemento)
        return render_template('index.html', title = "Home", movies=list)

    if 'mail' in session.keys():
        saldo = database.getSaldo(session['mail'])
        session['saldo'] = '0'
        return render_template('index.html', title = "Home", movies_1949=topVentas, email = session['mail'], saldo = saldo)

    return render_template('index.html', title = "Home", movies_1949=topVentas, email = 'Anonymous')


@app.route('/detalles/<film>', methods=['GET', 'POST'])
def detalles(film):
    list = []
    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)
    
    dic = database.getDetalles(film)
    if 'add' in request.form:
        if 'mail' in session:
            database.addCarrito(film, session['mail'])
            return redirect(url_for('cart', id = dic['titulo'], precio = dic['precio']))
        else:
            return redirect(url_for('login'))

    return render_template('detalles.html', item = dic)

@app.route('/elim/<film>', methods=['GET', 'POST'])
def elim(film):
	if database.eliminar(session['mail'], film) == "OK":
		return redirect(url_for('cart'))

	return redirect(url_for('index'))

@app.route('/cart', methods=['GET', 'POST'])
def cart():
    suma = 0
    saldo = float(session['saldo'])
    list = []

    if 'mail' not in session:
        return redirect(url_for('login'))

    if 'incrementar' in request.args:
        database.incrementar(session['mail'], request.args['incrementar'], request.args.get('tarjeta'))
        return redirect(url_for('cart'))

    if 'purchase' in request.form:
        if 'mail' not in session:
            return redirect(url_for('login'))
        
        if database.purchase(session['mail']) is False:
            return redirect(url_for('cart'))
        else:
            return redirect(url_for('index'))

        for i in session['carrito'].keys():
            history = {}
            history[i] = float(session['carrito'][i])
            list.append(history)

        hist = {}
        hist['historial'] = list

        with open(ruta, 'w') as fp:
            json.dump(hist, fp)

        session['saldo'] = saldo
        session.pop('carrito', None)
        return redirect(url_for('cart', total = 0))

    carrito = database.view_cart(session['mail'])
    item = carrito['peliculas'].values()
    suma = carrito['total']

    return render_template('cart.html', carrito = item, total = suma)


@app.route('/')
@app.route('/register', methods=['GET', 'POST'])
def register():

    if request.method == 'POST':
        if 'mail' and 'firstname' and 'credit' and 'password' and 'password2' in request.form:
            usuario = request.form.get('mail')
            nombre = request.form.get('firstname')
            tarjeta = request.form.get('credit')
            password = request.form.get('password')
            saldo = str(randrange(100))

            if os.path.exists("usuarios/") == False:
                os.mkdir('usuarios/')

            #si el usuario ya existe
            if database.existsUser(usuario):
                return render_template('login.html', flag = os.path.exists("usuarios/" + usuario))

            database.addUser(usuario, nombre, tarjeta, password, saldo)


            return redirect(url_for('login', mail = request.form['mail']))

    else:
        return render_template('register.html')


@app.route('/history')
def history():
	if 'mail' not in session:
		return redirect(url_for('login'))
	else:
		return redirect(url_for('index'))


@app.route('/')
@app.route('/login', methods=['GET', 'POST'])
def login():
    if 'mail' in session:
        return redirect(url_for('index'))

    email = request.cookies.get('email')

    if request.method == 'POST':
        #autentificar usuario con su mail y contrasena
        if database.checkUser(request.form['mail'], request.form['password']) is True:
            session['mail'] = request.form['mail']
            session.modified = True
            return redirect(url_for('index'))
        else:
            return render_template('login.html')

    return render_template('login.html', user_name = email)


@app.route('/logout', methods=['GET', 'POST'])
def logout():
    session['logged'] = 0
    response = make_response(redirect(url_for('index')))
    response.set_cookie('email', session['mail'])
    session.pop('mail', None)
    return response
