# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 1: Fusion de imagenes mediante piramides
# Tarea 2: piramide Gaussiana y piramide laplaciana

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1
import numpy as np
import scipy.signal
from scipy.signal.signaltools import _init_freq_conv_axes

from p1_tests import test_p1_tarea2
from p1_tarea1 import reduce, expand 


def gaus_piramide(imagen, niveles):
    """ 
    # Esta funcion crea una piramide Gaussiana a partir de una imagen
    #
    # Argumentos de entrada:
    #   imagen: numpy array de tamaño [imagen_height, imagen_width].
    #   niveles: entero positivo que especifica el numero de veces que se aplica la operacion 'reduce'.
    #           Si niveles=0 entonces se debe devolver una lista con la imagen de entrada
    #           Si niveles=1 entonces se debe realizar una operacion de reduccion               
    #
    # Devuelve:
    #   gauss_pyr: lista de numpy arrays con variable tamaño con "niveles+1" elementos.
    #       output[0] es la imagen de entrada
    #       output[i] es el nivel i de la piramide
    #
    # NOTA: algunas veces, la operacion 'expand' devuelve una imagen de tamaño mayor 
    # que el esperado. Entonces no coinciden las dimensiones de la imagen expandida 
    #   del nivel k+1 y las dimensiones del nivel k. Verifique si ocurre esta 
    #   situacion y en caso afirmativo, elimine los ultimos elementos de la 
    #   imagen expandida hasta coincidir las dimensiones del nivel k
    #   Por ejemplo, si el nivel tiene tamaño 5x7, tras aplicar 'reduce' y 'expand' 
    #   obtendremos una imagen de tamaño 6x8. En este caso, elimine la 6 fila y 8 
    #   columna para obtener una imagen de tamaño 5x7 donde pueda aplicar la resta        
    """ 
    gaus_pyr = []  # iniciamos la variable de salida (lista)

    # introducimos en la piramide la imagen original
    # para el primer nivel
    gaus_pyr.append(imagen)

    # si hay mas niveles reducimos la imagen tantas veces como niveles haya
    if niveles > 0:
        for k in range(0, niveles):
            gaus_pyr.append(reduce(gaus_pyr[-1]))  # reducimos la ultima imagen introducida

    return gaus_pyr


def lapl_piramide(gaus_pyr):
    """ 
    # Esta funcion crea una piramide Laplaciana a partir de una piramide Gaussiana    
    #  
    # Argumentos de entrada:
    #   gauss_pyr: lista de numpy arrays creada con la funcion 'gauss_piramide'.               
    #
    # Devuelve:
    #   lapla_pyr: lista de numpy arrays con variable tamaño con "niveles+1" elementos.    
    #       lapla_pyr[0] es el primera nivel de la piramide que contiene bordes
    #       lapla_pyr[i] es el nivel i de la piramide que contiene bordes
    #       lapla_pyr[niveles-1] es una imagen (escala de grises)    
    """ 
    lapl_pyr = [] # iniciamos la variable de salida (lista) 

    # para cada nivel de la piramide gaussiana
    # comprobamos que el numero de filas y columnas
    # sea par. Ya que la operacion expand puede devolver
    # una imagen de tamaño mayor al esperado
    for k in range(0, len(gaus_pyr)-1):
        # resta entre el nivel k de la piramide de gauss
        # y el nivel k+1 expandido
        if gaus_pyr[k].shape[0] % 2 is not 0 and gaus_pyr[k].shape[1] % 2 is not 0:
            resta = gaus_pyr[k] - expand(gaus_pyr[k+1])[:-1, :-1]
        elif gaus_pyr[k].shape[0] % 2 is not 0:
            resta = gaus_pyr[k] - expand(gaus_pyr[k+1])[:-1, :]
        elif gaus_pyr[k].shape[1] % 2 is not 0:
            resta = gaus_pyr[k] - expand(gaus_pyr[k+1])[:,:-1]
        else:
            resta = gaus_pyr[k] - expand(gaus_pyr[k+1])

        lapl_pyr.append(resta)

    # el ultimo elemento de la piramide laplaciana 
    # coincide con el ultimo de la piramide gaussiana
    lapl_pyr.append(gaus_pyr[-1])
    
    return lapl_pyr


if __name__ == "__main__":    
    print("Practica 1 - Tarea 2 - Test autoevaluación\n")                
    print("Tests completados = " + str(test_p1_tarea2())) 