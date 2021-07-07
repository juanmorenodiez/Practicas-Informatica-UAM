####################################################################
# Cliente de video.
#
# modulo: practica3_client.py
# Pareja 10:
#   Juan Moreno <juan.morenod@estudiante.uam.es>
#   Ines Martin <ines.martinmateos@estudiante.uam.es>
#####################################################################

# import the library
from servidor_descubrimiento import Servidor
from appJar import gui
from PIL import Image, ImageTk
from user import User, StatusUser
import numpy as np
import cv2

# Interfaz principal del cliente P2P
class VideoClient(object):
	def __init__(self, window_size, user):
		# Creamos una variable que contenga el GUI principal
		self.app = gui("Redes2 - P2P", window_size)
		self.app.setGuiPadding(10,10)

		self.user = user

		# Preparación del interfaz
		self.app.addLabel("title", "Cliente Multimedia P2P - Redes2 ")
		self.app.addImage("video", "webcam.gif")

		# Registramos la función de captura de video
		# Esta misma función también sirve para enviar un vídeo
		self.cap = cv2.VideoCapture(0)
		self.app.setPollTime(20)
		self.app.registerEvent(self.capturaVideo)

		# Añadir los botones
		self.app.addButtons(["Conectar", "Colgar", "Salir"], self.buttonsCallback)

		# Barra de estado
		# Debe actualizarse con información útil sobre la llamada (duración, FPS, etc...)
		self.app.addStatusbar(fields=2)

	def start(self):
		self.app.go()

	# Función que captura el frame a mostrar en cada momento
	def capturaVideo(self):
		# Capturamos un frame de la cámara o del vídeo
		ret, frame = self.cap.read()
		frame = cv2.resize(frame, (640,480))
		cv2_im = cv2.cvtColor(frame,cv2.COLOR_BGR2RGB)
		img_tk = ImageTk.PhotoImage(Image.fromarray(cv2_im))

		# Lo mostramos en el GUI
		self.app.setImageData("video", img_tk, fmt = 'PhotoImage')

		# Aquí tendría que el código que envia el frame a la red
		# ...

	# Establece la resolución de la imagen capturada
	def setImageResolution(self, resolution):
		# Se establece la resolución de captura de la webcam
		# Puede añadirse algún valor superior si la cámara lo permite
		# pero no modificar estos
		if resolution == "LOW":
			self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 160)
			self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 120)
		elif resolution == "MEDIUM":
			self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
			self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
		elif resolution == "HIGH":
			self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 640)
			self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 480)

	# Función que gestiona los callbacks de los botones
	def buttonsCallback(self, button):
		"""Método que indica algunas acciones a realizar por botones
		definidos en este fichero.

		Args:
			button (button): botón previamente pulsado.
		"""
		if button == "Salir":
			# Salimos de la aplicación
			self.app.stop()
		elif button == "Conectar":
			try:
				self.app.startSubWindow("window1", modal = True)
				self.app.addLabelOptionBox("Usuarios", self.user.server.list_users())
				self.app.addLabelEntry("Usuario")
				self.app.addButtons(["Aceptar", "Cancelar"], self.connectCallback)
			except Exception:
				pass

			self.app.showSubWindow("window1", hide = False)

	def connectCallback(self, button):
		"""Método que define las acciones a realizar cuando se 
		procede a intentar conectarse con un usuario.

		Args:
			button (button): botón de conectar previamente pulsado
		"""
		if button == "Aceptar":
			nick_conn = self.app.getEntry("Usuario")
			if nick_conn == '':
				nick_conn = self.app.getOptionBox("Usuarios")
			if nick_conn is None:
				self.app.warningBox("Info", "Debe seleccionar un usuario o introducir su nick")
			else:
				self.user.connect_with(nick_conn)
				return
		elif button == "Cancelar":
			self.app.hideSubWindow("window1")
					

if __name__ == '__main__':
	user = User()
	# Accedemos primero a la pagina de registro
	user.registerWindow("640x520")

	# Si se ha logueado correctamente accedemos
	if user.state == StatusUser.REGISTERED:
		vc = VideoClient("640x520", user)

		# Crear aquí los threads de lectura, de recepción y,
		# en general, todo el código de inicialización que sea necesario
		# ...


		# Lanza el bucle principal del GUI
		# El control ya NO vuelve de esta función, por lo que todas las
		# acciones deberán ser gestionadas desde callbacks y threads
		vc.start()
