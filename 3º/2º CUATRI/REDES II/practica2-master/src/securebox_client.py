"""Fichero securebox_client.py. 
Fichero que ejecuta el parser de argumentos y nos permitirá
realizar las operaciones indicadas posteriormente en el sistema
Secure_Box.

Pareja 10:
   Juan Moreno <juan.morenod@estudiante.uam.es>
   Ines Martin <ines.martinmateos@estudiante.uam.es>
"""

import argparse
import ficheros
import usuarios
import seguridad
import config

    
"""Función cliente la cual realiza todo el parsing de argumentos
que se nos pide en la realización de la práctica.
"""
def cliente():
    # creamos el parser
    parser = argparse.ArgumentParser(description = "SecureBox Client")

    # Añadimos los argumentos necesarios al parser
    # gestion de usuarios e identidades
    parser.add_argument("--create_id", help = "Crea una nueva identidad para un usuario", nargs = "+", type = str)
    parser.add_argument("--search_id", help = "Busca un usuario dada una cadena", nargs = 1, type = str, metavar = "cadena")
    parser.add_argument("--delete_id", help = "Borra la identidad con ID id registrada en el sistema", nargs = 1, type = str, metavar = "id")

    # subida y descarga de ficheros
    parser.add_argument("--upload", help = "Envia un fichero a otro usuario", nargs = 1, type = str, metavar = "fichero")
    parser.add_argument("--source_id", help = "ID del emisor del fichero", nargs = 1, type = str, metavar = "id")
    parser.add_argument("--dest_id", help = "ID del receptor del fichero", nargs = 1, type = str, metavar = "id")
    parser.add_argument("--list_files", help = "Lista todos los ficheros pertenecientes al usuario", action = "store_true")
    parser.add_argument("--download", help = "Recupera un fichero con ID id_fichero del sistema", nargs = 1, type = str, metavar = "id_fichero")
    parser.add_argument("--delete_file", help = "Borra un fichero del sistema", nargs = 1, type = str, metavar = "id_fichero")

    # cifrado y firma de ficheros local
    parser.add_argument("--encrypt", help = "Cifra un fichero", nargs = 1, type = str, metavar = "fichero")
    parser.add_argument("--sign", help = "Firma un fichero", nargs = 1, type = str, metavar = "fichero")
    parser.add_argument("--enc_sign", help = "Cifra y firma un fichero", nargs = 1, type = str, metavar = "fichero")

    args = parser.parse_args()

    # segun el argumento que hayamos escrito hara X cosa
    if args.create_id:
        # con alias
        if len(args.create_id) == 3:
            usuarios.create_user(args.create_id[0], args.create_id[1], args.create_id[2], config.TOKEN)
        # sin alias    
        else:
             usuarios.create_user(args.create_id[0], args.create_id[1], None, config.TOKEN)   
    elif args.search_id:
        usuarios.search_user(args.search_id[0], config.TOKEN)    
    elif args.delete_id:
        usuarios.delete_user(args.delete_id[0], config.TOKEN)
    elif args.upload:
        if args.dest_id is None:
            print("Se debe incluir el ID del receptor del fichero.")
            return
        ficheros.subir_fichero(args.upload[0], args.dest_id[0], config.TOKEN)       
    elif args.list_files:
        ficheros.listar_ficheros(config.TOKEN)        
    elif args.download:
        if args.source_id is None:
            print("se debe incluir el ID del que se va a descargar el fichero")
            return
        ficheros.descargar_fichero(args.download[0], args.source_id[0], config.TOKEN)    
    elif args.delete_file:
        ficheros.borrar_fichero(args.delete_file[0], config.TOKEN)
    elif args.encrypt:
        if args.dest_id is None:
            print("Se debe incluir el ID del receptor del fichero.")
            return
        seguridad.cifrar_fichero_AES(args.encrypt[0], args.dest_id[0], config.TOKEN)
    elif args.sign:
        if args.source_id is None:
            print("se debe incluir el ID del que se va firmar el fichero")
            return
        seguridad.firmar_fichero(args.sign[0], args.source_id[0], config.TOKEN)
    elif args.enc_sign:
        seguridad.cifrar_firmar_fichero(args.enc_sign[0], args.dest_id[0], config.TOKEN)                      


"""Función main que ejecuta el cliente(parser de argumentos)
"""
if __name__ == "__main__":   
    cliente()
