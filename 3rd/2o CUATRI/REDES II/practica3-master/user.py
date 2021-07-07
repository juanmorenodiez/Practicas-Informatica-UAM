####################################################################
# Fichero que gestiona el estado e informacion de un usuario.
#
# modulo: user.py
# Pareja 10:
#   Juan Moreno <juan.morenod@estudiante.uam.es>
#   Ines Martin <ines.martinmateos@estudiante.uam.es>
#####################################################################
from servidor_descubrimiento import Servidor
from appJar import gui
from PIL import Image, ImageTk
from enum import Enum
import socket
import struct
import threading

"""Enumeracion con los diferentes estados del usuario
en el sistema.
"""
class StatusUser(Enum):
    ACCESS_DENIED = 0
    REGISTERED = 1
    BUSY = 2

"""
Clase usuario con sus principales atributos , interfaz gráfica e 
intento de conexión con otros usuarios.
"""
class User(object):
    def __init__(self):
        self.server = Servidor()
        self.ip = self.server.my_ip()
        self.state = StatusUser.ACCESS_DENIED
        self.protocols = ["V0"]
        self.port = 5100
        self.port_listen = 6000

        # creamos socket de escucha TCP
        self.socket_escucha = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
        try:
            # a espera de un connect
            self.socket_escucha.bind((self.server.my_ip(), self.port_listen))
            self.socket_escucha.listen(1)

        except socket.error:
            self.socket_escucha.close()

        # creamos hilo que ejecuta recibir_llamada() al instanciar el usuario
        self.thread = threading.Thread(target = self.recibir_llamada)
        self.thread.start()


    def registerWindow(self, window_size):
        """Método que muestra la interfaz gráfica del registro
        de un usuario.

        Args:
            window_size (int): tamaño de la ventana
        """
        self.app = gui("Redes2 - P2P", window_size)
        self.app.setGuiPadding(10,10)

        # Preparación del interfaz
        self.app.addLabel("title", "Registrar")

        self.app.addLabelEntry("Nick")
        self.app.addLabelSecretEntry("Contraseña")
        # Añadir los botones
        self.app.addButtons(["Aceptar", "Cancelar"], self.registerButtonsCallback)
        self.app.go()


    def registerButtonsCallback(self, button):
        """ Método que define las acciones de cuando se procede
        a registrar o iniciar sesión con el usuario.

        Args:
            button (button): boton que se ha pulsado para
            iniciar sesión/registrar
        """
        
        if button == "Cancelar":
            self.app.stop()
        elif button == "Aceptar":
            nick = self.app.getEntry("Nick")
            password = self.app.getEntry("Contraseña")

            if nick == "" or password == "":
                self.app.warningBox("Info", "Usuario o contraseña obligatorios")
            else:
                # registro del usuario
                ret = self.server.register_user(nick, self.server.my_ip(), str(self.port), password, "#".join(self.protocols))

                if ret is None:
                    self.app.errorBox("Error", "Contraseña incorrecta para el usuario introducido")
                else:
                    self.state = StatusUser.REGISTERED
                    self.app.stop()

    def create_connection_calling(self, ip, port):
        """Método que crea la conexión para establecer la llamada
        entre dos usuarios del sistema.

        Args:
            ip (int): ip destino a conectarse
            port (int): puerto destino a conectarse

        Returns:
            [type]: [description]
        """
        # creamos socket TCP
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
       
        # en este connect se nos queda bloqueada la aplicacion
        # no hemos conseguido probarlo de forma correcta
        """
        try:
            s.connect((ip, port))
        except socket.error:
            print("Conexión no establecida.\n")
            return None
        return s
        """
        

    def call(self, nick, ip, port):
        """Método que realiza el comando de llamada

        Args:
            nick (str): usuario a llamar
            ip (int): ip destino a llamar
            port (int): puerto destino a llamat

        Returns:
            [None]: none si se produce algún error
        """
        # iniciamos conexion
        conn = self.create_connection_calling(ip, port)
        call = "CALLING " + nick + " " + str(self.port)
        
        try:
            conn.send(bytes(call, encoding = 'ascii'))
        except:
            print("Mensaje no enviado.\n")
            return None  
           

    def connect_with(self, user):
        """Método que conecta un usuario con otro con el 
        objetivo de poder llamarle.

        Args:
            user (str): nick del usuario con el que se
            quiere establecer la conexión.
        """
        ip_port = self.server.query(user)

        if ip_port is not None:
            ip, port = ip_port
            struct.unpack("!I", socket.inet_aton(ip))[0]
            self.call(user, ip, int(port))

        return

    def recibir_llamada(self):
        """Método que entra en un bucle infinito que se queda esperando
        hasta que se recibe una llamada. Bastante incompleto y no se han podido
        realizar demasiadas pruebas.
        """
        while True:
            try:
                tcp, address = self.socket_escucha.accept()
            except:
                break

            rcv = tcp.recv(2048)
            msg = rcv.decode().split(" ")

            if self.state != StatusUser.BUSY:
                self.state = StatusUser.BUSY
                print("Recibiendo llamada...")
            else:
                print("Usuario Ocupado...")
