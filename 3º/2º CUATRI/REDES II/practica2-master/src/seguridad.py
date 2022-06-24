"""Fichero seguridad.py. 
Este es el módulo fuente que incluirá la funcionalidad
para el cifrado, firmado y descifrado de ficheros y mensajes.

Pareja 10:
   Juan Moreno <juan.morenod@estudiante.uam.es>
   Ines Martin <ines.martinmateos@estudiante.uam.es>
"""

import usuarios
from base64 import b64encode
from Crypto.Cipher import AES
from Crypto.Cipher import PKCS1_OAEP
from Crypto.Hash import SHA256
from Crypto.PublicKey import RSA
from Crypto.Random import get_random_bytes
from Crypto.Signature import pkcs1_15
from Crypto.Util.Padding import pad
import Crypto.Util.Padding as Padding


def sobre_digital(key, id_receptor, token):
    """Función que genera el sobre digital (clave simétrica con
    la clave pública del receptor)

    Args:
        key (bytes): clave aleatoria de 256 bits
        id_receptor (str): id del receptor del fichero
        token (str): token activo

    Returns:
        bytes: sobre digital
    """
    # recuperamos la clave publica del receptor
    print("-> Recuperando clave publica de ID {}...OK".format(id_receptor))
    public_key = usuarios.getPublicKey(id_receptor, token)
    
    # creamos el RSA de la clave publica
    rsakey = RSA.import_key(public_key)
    
    # creamos el cifrador RSA
    encryptor = PKCS1_OAEP.new(rsakey)

    # ciframos la clave
    encrypted = encryptor.encrypt(key)

    return encrypted


def cifrar_mensaje_AES(mensaje, id_receptor, token):
    """Función que cifra un mensaje mediante AES(simétrico)

    Args:
        mensaje (str): mensaje a cifrar
        id_receptor (str): id del receptor del fichero
        token (str): token activo

    Returns:
        bytes: mensaje cifrado + sobre + iv
    """
    # longitud de clave de 256 bits
    key = get_random_bytes(32)

    # IV de 16 bytes
    iv = get_random_bytes(16)
    
    # modo de encadenamiento CBC
    cipher = AES.new(key, AES.MODE_CBC, iv)

    # generamos el sobre digital
    sobre = sobre_digital(key, id_receptor, token)

    # cifrado simetrico AES
    print("-> Cifrando mensaje...OK")
    encrypted = cipher.encrypt(Padding.pad(mensaje, 16)) 

    return iv + sobre + encrypted

     
def cifrar_fichero_AES(fichero, id_receptor, token):
    """Función que cifra un fichero mediante AES(simétrico)

    Args:
        fichero (file): fichero a cifrar
        id_receptor (str): id del receptor del fichero
        token (str): token activo

    Returns:
        bytes: mensaje cifrado del fichero
    """
    # obtenemos los datos del fichero
    with open(fichero, 'rb') as pf:
        file_data = pf.read()   

    print("-> Cifrando fichero...OK")
    # ciframos los datos
    encrypted_message = cifrar_mensaje_AES(file_data, id_receptor, token) 

    with open(fichero, 'wb') as f:
        f.write(encrypted_message)
    
    return encrypted_message  


def firmar_fichero(fichero, id_receptor, token):
    """Función que firma un fichero mediante RSA(asimétrico)

    Args:
        fichero (file): fichero a firmar
        id_receptor (str): id del receptor del fichero
        token (str): token activo

    Returns:
        bytes: datos del fichero más la firma
    """
    with open(fichero, 'rb') as pf:
        file_data = pf.read()

    # creamos el hash del mensaje
    h = SHA256.new()
    h.update(file_data)

    # obtenemos la clave privada del fichero en el que la hemos guardado
    private_key = RSA.import_key(open('clave/private_key.pem').read())
    
    # firmamos
    print("-> Firmando fichero...OK")
    signature = pkcs1_15.new(private_key).sign(h)

    with open(fichero, 'wb') as f:
        f.write(signature) 

    return file_data + signature


def cifrar_firmar_fichero(fichero, id_receptor, token):
    """Función que cifra y firma un fichero

    Args:
        fichero (file): fichero a firmar y cifrar
        id_receptor (str): id del receptor del fichero
        token (str): token activo

    Returns:
        bytes: menjaje del fichero firmado y cifrado
    """
    # obtenemos el fichero firmado (mensaje + firma digital)
    signed_file = firmar_fichero(fichero, id_receptor, token)

    # ciframos el mensaje que hemos firmado previamente
    encrypted_message = cifrar_mensaje_AES(signed_file, id_receptor, token)

    with open(fichero, 'wb') as f:
        f.write(encrypted_message) 

    # devolvemos el mensaje completo(IV + SOBRE DIGITAL + MENSAJE FIRMADO Y CIFRADO)
    return encrypted_message


def verificar_firma(firma, mensaje, id_emisor, token):
    """Función que verifica la firma del fichero
    que se quiere descargar

    Args:
        firma (bytes): firma a verificar
        mensaje (bytes): mensaje a obtener
        id_emisor (str): id del emisor del fichero
        token (str): token activo

    Returns:
        bool: True si ha sido verificada correctamente la firma,
        False si no
    """
    # recuperamos la clave publica del emisor
    public_key = usuarios.getPublicKey(id_emisor, token)
    rsakey = RSA.import_key(public_key)

    # obtenemos el hash del mensaje
    h = SHA256.new(mensaje)

    # verificacion
    try:
        pkcs1_15.new(rsakey).verify(h, firma)
        return True
    except (ValueError, TypeError):
        return False

    return True  


def descifrar_sobre_digital(sobre):
    """Función que descifra el sobre digital 
    creado previamente

    Args:
        sobre (bytes): sobre digital a descifrar

    Returns:
        bytes: clave del sobre
    """
    # obtenemos la clave privada del fichero en el que la hemos guardado
    private_key = RSA.import_key(open('clave/private_key.pem').read())

    # creamos el cifrador RSA
    RSAcipher = PKCS1_OAEP.new(private_key)

    # desciframos la clave del sobre
    key = RSAcipher.decrypt(sobre)

    return key

def descifrar_mensaje_AES(mensaje, id_receptor, token):
    """Función que descifra un mensaje previamente firmado y cifrado

    Args:
        mensaje (bytes): mensaje a descifrar
        id_receptor (str): id del receptor del fichero
        token (str): token activo

    Returns:
        bytes: datos del mensaje original
    """
    # longitud de IV (16)
    iv = mensaje[0:16]
    # la longitud del sobre son de 32 bytes (256 bits)
    sobre = mensaje[16:272]
    #resto del mensaje desde 272 hasta el final
    resto = mensaje[272:]

    # sacamos la clave simetrica
    key = descifrar_sobre_digital(sobre)

    # creamos el cifrador
    AEScipher = AES.new(key, AES.MODE_CBC, iv)

    # desciframos el mensaje
    print("-> Descifrando mensaje...OK")
    mensaje_descifrado = AEScipher.decrypt(resto)
    # ajustamos al tamaño adecuado
    fitted = Padding.unpad(mensaje_descifrado, 16)

    # índices que tienen la información que queremos
    firma = fitted[len(fitted)-256:]
    datos = fitted[0:len(fitted)-256]

    if verificar_firma(firma, datos, id_receptor, token) is True:
        print("-> Verificando firma...OK")
        return datos
    else:
        print("Firma no válida")
        return 

def descifrar_fichero_AES(fichero, id_receptor, token):
    """Función que descifra un fichero dado

    Args:
        fichero (file): fichero a descifrar
        id_receptor (str): id del receptor del fichero
        token (str): token activo
    """
    print("-> Descifrando fichero...OK")
    with open(fichero, 'rb') as pf:
        file_data = pf.read()

    mensaje_descifrado = descifrar_mensaje_AES(file_data, id_receptor, token) 

    with open(fichero, 'wb') as f:
        f.write(mensaje_descifrado)

    return
