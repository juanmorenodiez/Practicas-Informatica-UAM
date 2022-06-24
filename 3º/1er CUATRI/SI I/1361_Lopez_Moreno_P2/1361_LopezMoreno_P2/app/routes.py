#!/usr/bin/env python3
# -*- coding: utf-8 -*-

from app import app
from flask import render_template, request, url_for, redirect, session, make_response
from random import randrange
import json
import os
import sys
import hashlib

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

    if 'saldo' in session:
        if 'mail' in session.keys():
            return render_template('index.html', title = "Home", movies=catalogue['peliculas'], email = session['mail'], saldo = session['saldo'])
    else:
        if 'mail' in session.keys():
            session['saldo'] = '0'
            return render_template('index.html', title = "Home", movies=catalogue['peliculas'], email = session['mail'], saldo = session['saldo'])

    return render_template('index.html', title = "Home", movies=catalogue['peliculas'], email = 'Anonymous')


@app.route('/detalles/<film>', methods=['GET', 'POST'])
def detalles(film):
    list = []
    print (url_for('static', filename='estilo.css'), file=sys.stderr)
    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)

    if 'add' in request.form:
        for elemento in catalogue['peliculas']:
            if elemento.get('titulo') == film:
                return redirect(url_for('cart', id = elemento.get('titulo'), precio = elemento.get('precio')))

    for elemento in catalogue['peliculas']:
        if elemento.get('titulo') == film:
            list.append(elemento)

            return render_template('detalles.html', item = elemento)

@app.route('/elim/<film>', methods=['GET', 'POST'])
def elim(film):

    for pelicula in session['carrito'].keys():
        if pelicula == film:
            del session['carrito'][pelicula]
            return redirect(url_for('cart'))


@app.route('/cart', methods=['GET', 'POST'])
def cart():
    suma = 0
    saldo = float(session['saldo'])
    list = []
    if request.method == "GET":
        if not 'carrito' in session:
            session['carrito'] = {}
        if request.args.get('id'):
            session['carrito'].update({request.args.get('id') : request.args.get('precio')})
            session.modified = True

        for key in session['carrito']:
            suma += float(session['carrito'].get(key))

    if 'incrementar' in request.args:
        ruta = "usuarios/" + session['mail'] + "/datos.dat"
        wordList = []
        f = open(ruta, "r")
        for line in f:
            for word in line.split():
                wordList.append(word)

        if wordList[9] == request.args.get('tarjeta'):

            saldo += float(request.args['incrementar'])

            ruta = "usuarios/" + session['mail'] + "/datos.dat"
            with open(ruta, 'r') as file:
                filedata = file.read()

            filedata = filedata.replace(str(session['saldo']), str(saldo))
            with open(ruta, 'w') as file:
                file.write(filedata)

            session['saldo'] = saldo
            return redirect(url_for('index'))


    if 'purchase' in request.form:
        if 'mail' not in session:
            return redirect(url_for('login'))
        for key in session['carrito']:
            suma += float(session['carrito'].get(key))
        if saldo < suma:
            return redirect(url_for('index'))
        saldo -= suma
        ruta = "usuarios/" + session['mail'] + "/datos.dat"
        with open(ruta, 'r') as file:
            filedata = file.read()

        filedata = filedata.replace(str(session['saldo']), str(saldo))
        with open(ruta, 'w') as file:
            file.write(filedata)

        ruta = "usuarios/" + session['mail'] + "/historial.json"

        #añadimos a list los pedidos previos
        with open(ruta, "r") as fp:
            list = json.load(fp)

        history = {}
        for i in session['carrito'].keys():
            history[i] = float(session['carrito'][i])

        list['historial'].append(history)

        #metemos en "hist" lo que hay en "list"(peliculas del carrito)
        with open(ruta, "w") as fp:
            json.dump(list, fp)

        session['saldo'] = saldo
        session.pop('carrito', None)
        return redirect(url_for('cart', total = 0))

    return render_template('cart.html', movies = session['carrito'], total = suma)


@app.route('/')
@app.route('/register', methods=['GET', 'POST'])
def register():
    print (url_for('static', filename='estilo.css'), file=sys.stderr)

    if 'mail' in session:
        return redirect(url_for('index'))

    if 'mail' and 'firstname' and 'credit' and 'password' and 'password2' in request.form:
        usuario = request.form.get('mail')
        nombre = request.form.get('firstname')
        tarjeta = request.form.get('credit')
        password = request.form.get('password')
        password = hashlib.md5(password.encode())
        saldo = str(randrange(100))

        if os.path.exists("usuarios/") == False:
            os.mkdir('usuarios/')

        if os.path.exists('usuarios/' + usuario) == True:
            return render_template('login.html', flag = os.path.exists("usuarios/" + usuario))

        os.mkdir('usuarios/' + usuario)
        ruta = "usuarios/" + usuario + "/datos.dat"
        ruta2 = "usuarios/" + usuario +"/historial.json"

        history = {
            "historial" : []
        }

        open(ruta2, "x")
        os.chmod(ruta2, 0o777)
        with open(ruta2, "w") as outfile:
            json.dump(history, outfile)

        f = open(ruta, "x")
        f = open(ruta, "a")
        f.write("Nombre " + nombre + "\n")
        f.write("mail " + usuario + "\n")
        f.write("Contraseña " + password.hexdigest() + "\n")
        f.write("Tarjeta de crédito " + tarjeta + "\n")
        f.write("Saldo " + saldo + "\n")
        f.close()
        session['saldo'] = saldo
        return redirect(url_for('index'))

    else:
        return render_template('register.html')

@app.route('/history')
def history():
    if 'mail' not in session:
        return redirect(url_for('login'))
    catalogue_data = open(os.path.join(app.root_path,'../usuarios/' + session['mail'] + '/historial.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)
    return render_template('history.html', movies = catalogue['historial'])


@app.route('/')
@app.route('/login', methods=['GET', 'POST'])
def login():
    print (url_for('static', filename='estilo.css'), file=sys.stderr)
    catalogue_data = open(os.path.join(app.root_path,'catalogue/catalogue.json'), encoding="utf-8").read()
    catalogue = json.loads(catalogue_data)

    if 'mail' in session:
        return redirect(url_for('index'))

    email = request.cookies.get('email')

    if 'mail' and 'password' in request.form:
        if os.path.isdir('usuarios/' + request.form.get('mail')) == True:
            usuario = request.form.get('mail')
            ruta = "usuarios/" + usuario + "/datos.dat"
            wordList = []
            f = open(ruta, "r")
            for line in f:
                for word in line.split():
                    wordList.append(word)

            password = request.form.get('password')
            password = hashlib.md5(password.encode())

            if wordList[5] == password.hexdigest():
                session['mail'] = request.form['mail']
                session['saldo'] = wordList[11]
                session.modified = True
                session['logged'] = 1
                return render_template('index.html', title = "Home", movies=catalogue['peliculas'], email = request.form.get('mail'), saldo = session['saldo'])

            else:
                return render_template('login.html')

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
