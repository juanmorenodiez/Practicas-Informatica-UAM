import os

"""Fichero de configuración para el uso de la aplicación en el mismo ordenador
"""

VIDEO = os.environ.get("VIDEO", "/dev/video0")
SRC_PORT1 = 6000
CONTROL_PORT1 = 5100