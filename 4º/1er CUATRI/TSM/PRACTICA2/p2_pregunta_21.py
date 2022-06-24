# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 2: Extraccion, descripcion y correspondencia de caracteristicas locales
# Memoria: codigo de la pregunta 2.1

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from skimage import data
import matplotlib.pyplot as plt
from p2_tarea1 import detectar_puntos_interes_harris
from p2_tarea2 import descripcion_puntos_interes

img_camera = data.camera()
coords_esquinas = detectar_puntos_interes_harris(img_camera)

descriptor_8_16 = descripcion_puntos_interes(img_camera, coords_esquinas, vtam = 8, nbins = 16, tipoDesc='hist')
descriptor_16_16 = descripcion_puntos_interes(img_camera, coords_esquinas, vtam = 16, nbins = 16, tipoDesc='hist')
descriptor_8_32 = descripcion_puntos_interes(img_camera, coords_esquinas, vtam = 8, nbins = 32, tipoDesc='hist')
descriptor_16_32 = descripcion_puntos_interes(img_camera, coords_esquinas, vtam = 16, nbins = 32, tipoDesc='hist')

print("Descriptor hist con vecindario 8 y nbins 16: {}".format(descriptor_8_16[0][:3]))
print("Descriptor hist con vecindario 16 y nbins 16: {}".format(descriptor_16_16[0][:3]))
print("Descriptor hist con vecindario 8 y nbins 32: {}".format(descriptor_8_32[0][:3]))
print("Descriptor hist con vecindario 16 y nbins 32: {}".format(descriptor_16_32[0][:3]))
