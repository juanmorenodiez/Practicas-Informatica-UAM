# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 1: Fusion de imagenes mediante piramides
# Tarea 1: metodos reduce y expand

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

import numpy as np
import scipy.signal

from p1_tests import test_p1_tarea1
from p1_utils import generar_kernel_suavizado


def reduce(imagen):
    """
    # Esta funcion implementa la operacion "reduce" sobre una imagen
    #
    # Argumentos de entrada:
    #    imagen: numpy array de tamaño [imagen_height, imagen_width].
    # 
    # Devuelve:
    #    output: numpy array de tamaño [imagen_height/2, imagen_width/2] (output).
    #
    # NOTA: si imagen_height/2 o imagen_width/2 no son numeros enteros, 
    #        entonces se redondea al entero mas cercano por arriba 
    #        Por ejemplo, si la imagen es 5x7, la salida sera 3x4  
    """   
    output = np.empty(shape=[0, 0])  # iniciamos la variable de salida (numpy array)

    # creamos kernel de suavizado
    kernel = generar_kernel_suavizado(a=0.4)
    # convolucionamos la imagen con el kernel ya creado
    img_convolved = scipy.signal.convolve2d(imagen, kernel, 'same')
    # copiamos los indices pares en el array de salida
    output = np.array(img_convolved[::2, ::2], copy=True)

    return output


def expand(imagen):
    """  
    # Esta funcion implementa la operacion "expand" sobre una imagen
    # 
    # Argumentos de entrada:
    #    imagen: numpy array de tamaño [imagen_height, imagen_width].
    #     
    # Devuelve:
    #    output: numpy array de tamaño [imagen_height*2, imagen_width*2].
    """ 
    output = np.empty(shape=[0, 0])  # iniciamos la variable de salida (numpy array)

    # creamos la imagen expandida con dimension doble a la de la entrada
    img_expand = np.zeros((imagen.shape[0]*2, imagen.shape[1]*2))

    # copiamos la imagen de entrada en los indices pares de la imagen expandida
    img_expand[::2, ::2] = np.array(imagen)

    # creamos kernel de suavizado
    kernel = generar_kernel_suavizado(a=0.4)
    # convolucionamos la imagen con el kernel ya creado
    img_convolved = scipy.signal.convolve2d(img_expand, kernel, 'same')

    # multiplicamos por 4 para mantener el rango de la imagen de salida
    output = img_convolved*4

    return output


if __name__ == "__main__":    
    print("Practica 1 - Tarea 1 - Test autoevaluación\n")                
    print("Tests completados = " + str(test_p1_tarea1())) 