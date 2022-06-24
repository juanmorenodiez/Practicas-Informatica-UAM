# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 1: Fusion de imagenes mediante piramides
# Tarea 3: fusion de piramides y reconstruccion

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

import numpy as np
from p1_tests import test_p1_tarea3
from p1_tarea1 import expand


def fusionar_lapl_pyr(lapl_pyr_imgA, lapl_pyr_imgB, gaus_pyr_mask):
    """ 
    # Esta funcion realiza la fusion entre dos piramides laplacianas de distintas imagenes.
    #   La fusion esta determinada por una mascara de la cual se utiliza su correspondiente
    #   piramide Gaussiana para combinar las dos piramides laplacianas.
    #
    # Argumentos de entrada:
    #   lapl_pyr_imgA: lista de numpy arrays obtenida con la funcion 'lapl_piramide' sobre una imagen img2
    #   lapl_pyr_imgB: lista de numpy arrays obtenida con la funcion 'lapl_piramide' sobre otra imagen img1
    #   gaus_pyr_mask: lista de numpy arrays obtenida con la funcion 'gaus_piramide' 
    #                  sobre una mascara para combinar ambas imagenes. 
    #                  Esta mascara y la piramide tiene valores en el rango [0,1]
    #                  Para los pixeles donde gaus_pyr_mask==1, se coge la piramide de img1
    #                  Para los pixeles donde gaus_pyr_mask==0, se coge la piramide de img2
    #    
    # Devuelve:
    #   fusion_pyr: piramide fusionada
    #       lista de numpy arrays con variable tamaño con "niveles+1" elementos.    
    #       fusion_pyr[i] es el nivel i de la piramide que contiene bordes
    #       fusion_pyr[niveles] es una imagen (RGB o escala de grises)
    """ 
    fusion_pyr = [] # iniciamos la variable
    
    # comprobacion de que ambas piramides tengan el mismo nivel
    if len(lapl_pyr_imgA) != len(lapl_pyr_imgB):
        print("Pirámides de distinto nivel")
        return 

    # recorremos hasta el nivel de cualquiera de las dos piramides
    for k in range(0, len(lapl_pyr_imgA)):
        # realizamos la operacion y la metemos en la piramide resultante
        sum1 = lapl_pyr_imgA[k] * gaus_pyr_mask[k]
        sum2 = lapl_pyr_imgB[k] * (1-gaus_pyr_mask[k])
        fusion_pyr.append(sum1 + sum2)
    
    return fusion_pyr


def reconstruir_lapl_pyr(lapl_pyr):
    """ 
    # Esta funcion reconstruye la imagen dada una piramide laplaciana.
    #
    # Argumentos de entrada:
    #   lapl_pyr: lista de numpy arrays obtenida con la funcion 'lapl_piramide' sobre una imagen img
    #    
    # Devuelve:
    #   output: numpy array con dimensiones iguales al primer nivel de la piramide lapl_pyr[0]
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
    output = np.empty(shape=[0,0]) # iniciamos la variable de salida (numpy array)

    # metemos en output la imagen del ultimno nivel de la piramide
    output = lapl_pyr[-1]

    # iteramos desde arriba hacia abajo, -1 como tercer
    # argumento en el bucle para que recorra de forma
    # descendente
    for k in range(len(lapl_pyr)-1, 0, -1):
        # comprobamos que el numero de filas y columnas
        # sea par. Ya que la operacion expand puede devolver
        # una imagen de tamaño mayor al esperado
        if lapl_pyr[k-1].shape[0] % 2 is not 0 and lapl_pyr[k-1].shape[1] % 2 is not 0:
            expanded = expand(output)[:-1, :-1]
        elif lapl_pyr[k-1].shape[0] % 2 is not 0:
            expanded = expand(output)[:-1, :]
        elif lapl_pyr[k-1].shape[1] % 2 is not 0:
            expanded = expand(output)[:,:-1]
        else:
            expanded = expand(output)

        # sumamos la imagen expandida con el nivel k-1 
        output = expanded + lapl_pyr[k-1]
    
    return output


if __name__ == "__main__":    
    print("Practica 1 - Tarea 3 - Test autoevaluación\n")                
    print("Tests completados = " + str(test_p1_tarea3(precision=2))) 