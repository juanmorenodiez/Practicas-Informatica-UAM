import numpy as np
import matplotlib.pyplot as plt
from skimage import data

# Apartado 1
lista_img = list()

# Apartado 2
# Con las dimensiones comprobamos que es tridimensional, por lo que es a color
lista_img.append(data.astronaut())
print('Astronaut: ' + str(lista_img[0].shape))

# Apartado 3
# Con las dimensiones comprobamos que es bidimensional, por lo que es gris
lista_img.append(data.camera())
print('Camera: ' + str(lista_img[1].shape))

# Apartado 4
# Con las dimensiones comprobamos que es bidimensional, por lo que es gris
arrbid = np.zeros((10, 10))
lista_img.append(arrbid)
print('Array: ' + str(lista_img[2].shape))

# Apartado 5
print("\nBucle: ")
for i in range(0, 3):
    print(lista_img[i].dtype, lista_img[i].shape, lista_img[i].max())
    plt.imshow(lista_img[i])
    plt.show()

# Apartado 6
copylist = lista_img[:2]
print('\nLongitud lista: ' + str(len(copylist)))
