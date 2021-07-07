"""Fichero ficheros.py. 
Este es el módulo fuente que incluirá la funcionalidad
para el manejo y gestión de ficheros del sistema SecureBox

Pareja 10:
   Juan Moreno <juan.morenod@estudiante.uam.es>
   Ines Martin <ines.martinmateos@estudiante.uam.es>
"""

import requests
import seguridad
import config

def subir_fichero(fichero, id_receptor, token):
    """Método que sube un fichero firmado y cifrado
    al sistema Secure_Box

    Args:
        fichero (file): fichero a subir
        id_receptor (str): id del receptor del fichero
        token (str): token activo
    """
    cabecera = {'Authorization': 'Bearer ' + token}
    print("Solicitando envio de fichero a SecureBox")

    # firmamos y ciframos fichero
    mensaje_cifrado_firmado = seguridad.cifrar_firmar_fichero(fichero, id_receptor, token)

    with open(fichero, 'wb') as fp:
        fp.write(mensaje_cifrado_firmado)

    try:
        with open(fichero, "rb") as fp:
            peticion  = requests.post(url = config.urlUPLOAD, headers = cabecera, files = {'ufile': fp})
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 
    
    # si se ha realizado la petición correctamente
    if peticion.status_code == 200:
        #firmar y cifrar fichero
        print("-> Subiendo fichero a servidor...OK")
        print("Subida realizada correctamente, ID del fichero: {}, con tamaño: {}"
        .format(peticion.json()['file_id'], peticion.json()['file_size']))
        return
    else:
        print("Error {}".format(peticion.status_code))
        print("No se ha podido subir el fichero")  

    return      

def listar_ficheros(token):
    """Función que lista el número de ficheros subidos 
    por tí mismo a Secure_Box e incluye ciertas propiedades
    de estos ficheros

    Args:
        token (str): token activo
    """
    cabecera = {'Authorization': 'Bearer ' + token}
    print("Listando los ficheros...OK")

    try:
        peticion = requests.post(url = config.urlLIST, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado la petición correctamente
    if peticion.status_code == 200:
        print("{} ficheros encontrados".format(peticion.json()['num_files']))
        for fichero in peticion.json()['files_list']:
            print("ID: {}".format(fichero['fileID']))
        return 

    else:
        print("Error {}".format(peticion.status_code))
        print("No se han podido listar los ficheros")

    return     


def descargar_fichero(id_fichero, id_origen, token):
    """Función que se encarga de descargar y descifrar un fichero
    dado su identificador

    Args:
        id_fichero (str): id del fichero que se quiere descargar
        id_origen (str): id del usuario que ha subido el fichero
        token (str): token activo
    """
    cabecera = {'Authorization': 'Bearer ' + token}
    argumentos = {'file_id': id_fichero}

    print("Descargando fichero de SecureBox...OK")

    try:
        peticion = requests.post(url = config.urlDOWNLOAD, json = argumentos, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado la petición correctamente
    if peticion.status_code == 200:
        print("{} bytes descargados correctamente".format(peticion.headers['Content-Length']))
        mensaje_descifrado = seguridad.descifrar_mensaje_AES(peticion.content, id_origen, token)
        with open(peticion.headers['Content-Disposition'][22:-1], 'wb') as file:
            file.write(mensaje_descifrado)
        print("Fichero descargado y verificado correctamente")
        return
    else:
        print("Error {}".format(peticion.status_code))
        print("No se ha podido descargar el fichero")   

    return
        
    
def borrar_fichero(id_fichero, token):
    """Función que se encarga de borrar un fichero
    del sistema Secure_Box dada su identificación

    Args:
        id_fichero (str): id del fichero a borrar
        token (str): token activo
    """
    cabecera = {'Authorization': 'Bearer ' + token}
    argumentos = {'file_id': id_fichero}

    print("Borrando fichero...OK")

    try:
        peticion = requests.post(url = config.urlDELF, json = argumentos, headers = cabecera)
    except requests.exceptions.RequestException:
        print("No se ha podido realizar la peticion")
        return 

    # si se ha realizado la petición correctamente
    if peticion.status_code == 200:
        print("Fichero con ID: {} borrado correctamente."
        .format(peticion.json()['file_id']))    
        return 
    else:
        print("Error {}".format(peticion.status_code))
        print("No se ha podido borrar el fichero")   

    return      

