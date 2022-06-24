# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 2: Extraccion, descripcion y correspondencia de caracteristicas locales
# Memoria: codigo de la pregunta 2.3

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from skimage import io
from skimage.feature import plot_matches
import matplotlib.pyplot as plt
from skimage.color import rgb2gray
from p2_tarea1 import detectar_puntos_interes_harris
from p2_tarea2 import descripcion_puntos_interes
from p2_tarea3 import correspondencias_puntos_interes
import os

img_path = os.path.abspath(os.getcwd()) + '/img'

imgA1 = io.imread(img_path + '/EGaudi_1.jpg')
imgA2 = io.imread(img_path + '/EGaudi_2.jpg')

imgB1 = io.imread(img_path + '/Mount_Rushmore1.jpg')
imgB2 = io.imread(img_path + '/Mount_Rushmore2.jpg')

imgC1 = io.imread(img_path + '/NotreDame1.jpg')
imgC2 = io.imread(img_path + '/NotreDame2.jpg')

coords_esquinasA1 = detectar_puntos_interes_harris(rgb2gray(imgA1))
coords_esquinasA2 = detectar_puntos_interes_harris(rgb2gray(imgA2))

coords_esquinasB1 = detectar_puntos_interes_harris(rgb2gray(imgB1))
coords_esquinasB2 = detectar_puntos_interes_harris(rgb2gray(imgB2))

coords_esquinasC1 = detectar_puntos_interes_harris(rgb2gray(imgC1))
coords_esquinasC2 = detectar_puntos_interes_harris(rgb2gray(imgC2))

dA1 = descripcion_puntos_interes(imgA1, coords_esquinasA1)
dA2 = descripcion_puntos_interes(imgA2, coords_esquinasA2)

dB1 = descripcion_puntos_interes(imgB1, coords_esquinasB1)
dB2 = descripcion_puntos_interes(imgB2, coords_esquinasB2)

dC1 = descripcion_puntos_interes(imgC1, coords_esquinasC1)
dC2 = descripcion_puntos_interes(imgC2, coords_esquinasC2)

correspondecias_img1 = correspondencias_puntos_interes(dA1[0], dA2[0])
correspondecias_img2 = correspondencias_puntos_interes(dB1[0], dB2[0])
correspondecias_img3 = correspondencias_puntos_interes(dC1[0], dC2[0])

fig, ax = plt.subplots(nrows=3, ncols=1)

plot_matches(ax[0], imgA1, imgA2, coords_esquinasA1, coords_esquinasA2, correspondecias_img1)
ax[0].axis('off')
ax[0].set_title("Original Image vs. Transformed Image")

plot_matches(ax[1], imgB1, imgB2, coords_esquinasB1, coords_esquinasB2, correspondecias_img2)
ax[1].axis('off')
ax[1].set_title("Original Image vs. Transformed Image")

plot_matches(ax[1], imgC1, imgC2, coords_esquinasC1, coords_esquinasC2, correspondecias_img3)
ax[1].axis('off')
ax[1].set_title("Original Image vs. Transformed Image")

plt.show()