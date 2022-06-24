####################################################################
# Servidor que contiene los comandos para el registro y descubrimiento
# de usuarios.
#
# modulo: servidor_descubrimiento.py
# Pareja 10:
#   Juan Moreno <juan.morenod@estudiante.uam.es>
#   Ines Martin <ines.martinmateos@estudiante.uam.es>
#####################################################################
import socket

class Servidor:
    port = None
    ip = None
    host = None
    buff = None

    def __init__(self):
        self.port = 8000
        self.host = "vega.ii.uam.es"
        self.ip = self.my_ip()
        self.buff = 2048

    def create_connection(self):
        """Método que crea una conexión TCP a un host y puerto
        especificado

        Returns:
            socket: conexión con la que posteriormente se trabajará
        """
        # creamos socket TCP
        s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

        try:
            s.connect((self.host, self.port))
        except socket.error:
            print("Conexión no establecida.\n")
            return None
        return s

    def register_user(self, nick, ip_address, port, password, protocol):
        """Método que registra/inicia sesión(si se ha creado)
        en el sistema.

        Args:
            nick (str): nick del usuario
            ip_address (str): ip origen desde donde el usuario llamará(ip local)
            port (str): puerto origen desde donde el usuario llamará
            password (str): contraseña del usuario registrado
            protocol (list): lista de protocolos que soportará el usuario

        Returns:
            tuple: tupla con el ts y nick del usuario
        """
        # creamos una conexion
        conn = self.create_connection()
        if conn is None:
            return None

        register = "REGISTER " + nick + " " + ip_address + " " + port + " " + password + " " + protocol

        # enviamos el mensaje register
        try:
            conn.send(bytes(register, encoding = 'ascii'))
            # rcv contiene el mensaje en encoding
            # luego tendremos que cambiar su formato para hacer las comprobaciones
            rcv = conn.recv(self.buff)
        except:
            print("Mensaje no enviado.\n")
            self.quit(conn)
            return None

        msg = rcv.decode(encoding = 'ascii')

        if msg == "NOK WRONG_PASS":
            print("El nick es válido, pero la contraseña proporcionada es errónea.\n")
            self.quit(conn)
            return None
        else:
            print("El registro o actualización del nick se ha realizado correctamente.\n")
            cadena = msg.split()
            nick = cadena[2]
            ts = cadena[3]
            print("Bienvenido {}, ts = {}".format(nick, ts))

        return nick, ts

    def query(self, nick):
        """Método que busca un usuario en el sistema dado su nick.

        Args:
            nick (str): nick del usuario a buscar

        Returns:
            tuple: tupla con la ip y puerto del usuario que buscamos
        """
        # creamos una conexion
        conn = self.create_connection()
        query = "QUERY " + nick

        # enviamos el mensaje query
        try:
            conn.send(bytes(query, encoding = 'ascii'))
            # rcv contiene el mensaje en encoding
            # luego tendremos que cambiar su formato para hacer las comprobaciones
            rcv = conn.recv(self.buff)
        except:
            print("Mensaje no enviado.\n")
            self.quit(conn)
            return None

        msg = rcv.decode(encoding = 'ascii')

        if msg == "NOK USER_UNKNOWN":
            print("Usuario desconocido.\n")
            self.quit(conn)
            return None
        else:
            cadena = msg.split()
            ip = cadena[3]
            port = cadena[4]

        return ip, port

    def list_users(self):
        """Método que lista los usuarios del sistema. Con limitación del buffer
        que incluimos en el constructor de la clase.

        Returns:
            list: lista de usuarios
        """
        # creamos una conexion
        conn = self.create_connection()
        if conn is None:
            return None

        l_users = "LIST_USERS"

        try:
            conn.send(bytes(l_users, encoding = 'ascii'))
            # rcv contiene el mensaje en encoding
            # luego tendremos que cambiar su formato para hacer las comprobaciones
            rcv = conn.recv(self.buff)
        except:
            print("Mensaje no enviado.\n")
            # close connection ?
            return None

        msg = rcv.decode(encoding = 'ascii')

        if msg == "NOK USER_UNKNOWN":
            print("No hay usuarios en el sistema.\n")
            self.quit(conn)
            return None
        else:
            cadena = msg.split()
            list_of_users = [cadena[3]]
            for element in cadena:
                if '#' in element:
                    index = element.index('#')
                    list_of_users.append(element[index+1:])

        return list_of_users

    def quit(self, conn):
        """Método que indica el cierre de conexión.

        Args:
            conn (socket): conexión con el socket a cerrar.

        Returns:
            str: mensaje cierre de conexión 
        """
        quit = "QUIT"

        try:
            conn.send(bytes(quit, encoding = 'ascii'))
            rcv = conn.recv(self.buff)
        except:
            print("Mensaje no enviado.\n")
            return

        msg = rcv.decode(encoding = 'ascii')
        print(msg)

        if msg == "BYE":
            print("Conexión con el servidor cerrada.\n")

        conn.close()
        return msg

    def my_ip(self):
        """Método que devuelve la ip local del ordenador
        con el que se está trabajando.

        Returns:
            str: ip local
        """
        s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        s.connect(("8.8.8.8", 80))
        local_ip = s.getsockname()[0]
        s.close()
        return local_ip
