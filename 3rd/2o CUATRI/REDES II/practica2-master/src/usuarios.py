"""Fichero usuarios.py. 
Este es el módulo fuente que incluirá la funcionalidad
para el manejo y creación de usuarios del sistema SecureBox

Pareja 10:
   Juan Moreno <juan.morenod@estudiante.uam.es>
   Ines Martin <ines.martinmateos@estudiante.uam.es>
"""

import requests
import os
from Crypto.PublicKey import RSA
import datetime
import config

def generar_claves():
    """Genera las claves pública y privada
    en formato PEM 

    Returns:
        tuble: tubla con las claves públiva y privada
    """
    key = RSA.generate(2048) 

    print("Generando par de claves RSA de 2048 bits...OK")  

    # formato PEM para las dos claves
    public_key = key.publickey().export_key("PEM").decode("utf-8")
    private_key = key.export_key("PEM").decode("utf-8")

    return public_key, private_key


def create_user(nombre, email, alias, token):
    """Crea un usuario en el sistema Secure_Box

    Args:
        nombre (str): nombre del usuario
        email (str): email del usuario
        alias (str): alias del usuario
        token (str): token activo
    """

    # generacion de claves publica y privada, esto se debería de hacer en el cliente?
    public_key, private_key = generar_claves()

    # cabecera y argumentos de la peticion HTTP
    if alias is None:
        argumentos = {'nombre': nombre, 'email': email, 'publicKey': public_key}

    argumentos = {'nombre': nombre, 'email': email, 'alias': alias, 'publicKey': public_key}
    cabecera = {'Authorization': 'Bearer ' + token}

    # realizamos la peticion (POST)
    try:
        peticion = requests.post(url = config.urlREGISTER, json = argumentos, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado bien la peticion
    if peticion.status_code == 200:
        print("Identidad con ID#{} creada correctamente. Con marca de tiempo: {}"
        .format(peticion.json()['userID'], peticion.json()['ts']))
        # generamos un directorio para las claves privadas de cada usuario
        if not os.path.exists('clave'):
            os.makedirs('clave')
        else:
            print("El directorio ya existe")    

        # guardamos la clave privada del usuario en el directorio
        f = open('./clave/private_key.pem', 'w+')
        f.write(private_key)

        return
    # si se ha producido algun error    
    else:
        print("No se ha podido realizar el registro")    

    return  

def getPublicKey(id, token):
    """Devuelve la clave pública de un usuario
    dado su id

    Args:
        id (str): id del que se quiere la clave pública
        token (str): token activo

    Returns:
        str: cadena con la clave pública
    """
    argumentos = {'userID': id}
    cabecera = {'Authorization': 'Bearer ' + token}

    # realizamos la peticion (POST)
    try:
        peticion = requests.post(url = config.urlKEY, json = argumentos, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado bien la peticion
    if peticion.status_code == 200:
        return peticion.json()['publicKey']
    # si se ha producido algun error
    else:
        print("Error {}".format(peticion.status_code))
        print("El ID  de usuario proporcionado no existe")
    return None

def search_user(cadena, token):
    """Busca los usuarios del sistema Secure_Box
    dada una cadena

    Args:
        cadena (str): cadena por la que filtra la búsqueda
        token (str): token activo
    """
    argumentos = {'data_search': cadena}
    cabecera = {'Authorization': 'Bearer ' + token}

    print("Buscando usuario " + cadena +" en el servidor...OK")

    # realizamos la peticion (POST)
    try:
        peticion = requests.post(url = config.urlSEARCH, json = argumentos, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado bien la peticion
    if peticion.status_code == 200:
        print(str(len(peticion.json())) + " usuarios encontrados:")
        numUsuarios = 0
        for usuario in peticion.json():
            print("[{}] {}, {}, ID: {}" .format(numUsuarios + 1, usuario['nombre'],
            usuario['email'], usuario['userID']))
            numUsuarios += 1
        return 
    # si se ha producido algun error    
    else:
        print("No se ha podido encontrar al usuario")    

    return    

def delete_user(id, token):
    """Elimina un usuario del sistema Secure_Box
    dado un id

    Args:
        id (str): id del usuario a eliminar
        token (str): token activo
    """
    argumentos = {'userID': id}
    cabecera = {'Authorization': 'Bearer ' + token}

    print("Solicitando borrado de la identidad #{}...OK" .format(id))

    # realizamos la peticion (POST)
    try:
        peticion = requests.post(url = config.urlDELU, json = argumentos, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado bien la peticion
    if peticion.status_code == 200:
        print("Identidad con ID#{} borrada correctamente".format(peticion.json()['userID']))
        return 
    # si se ha producido algun error    
    else:
        print("Error {}".format(peticion.status_code))
        print("No se ha podido eliminar el usuario")    

    return     
