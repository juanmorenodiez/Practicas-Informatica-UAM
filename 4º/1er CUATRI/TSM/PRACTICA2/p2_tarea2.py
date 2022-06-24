# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 2: Extraccion, descripcion y correspondencia de caracteristicas locales
# Tarea 2: Descripcion de puntos de interes mediante histogramas.

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from p2_tests import test_p2_tarea2

import numpy as np
from scipy import ndimage
from p2_tarea1 import normalizar

def descripcion_puntos_interes(imagen, coords_esquinas, vtam = 8, nbins = 16, tipoDesc='hist'):
    """
    # Esta funcion describe puntos de interes de una imagen mediante histogramas, analizando 
    # vecindarios con dimensiones "vtam+1"x"vtam+1" centrados en las coordenadas de cada punto de interes
    #   
    # La descripcion obtenida depende del parametro 'tipoDesc'
    #   - Caso 'hist': histograma normalizado de valores de gris 
    #   - Caso 'mag-ori': histograma de orientaciones de gradiente
    #
    # En el caso de que existan puntos de interes en los bordes de la imagen, el descriptor no
    # se calcula y el punto de interes se elimina de la lista <new_coords_esquinas> que devuelve
    # esta funcion. Esta lista indica los puntos de interes para los cuales existe descriptor.
    #
    # Argumentos de entrada:
    #   - imagen: numpy array con dimensiones [imagen_height, imagen_width].        
    #   - coords_esquinas: numpy array con dimensiones [num_puntos_interes, 2] con las coordenadas 
    #                      de los puntos de interes detectados en la imagen. Tipo int64
    #                      Cada punto de interes se encuentra en el formato [fila, columna]
    #   - vtam: valor de tipo entero que indica el tamaño del vecindario a considerar para
    #           calcular el descriptor correspondiente.
    #   - nbins: valor de tipo entero que indica el numero de niveles que tiene el histograma 
    #           para calcular el descriptor correspondiente.
    #   - tipoDesc: cadena de caracteres que indica el tipo de descriptor calculado
    #
    # Argumentos de salida
    #   - descriptores: numpy array con dimensiones [num_puntos_interes, nbins] con los descriptores 
    #                   de cada punto de interes (i.e. histograma de niveles de gris)
    #   - new_coords_esquinas: numpy array con dimensiones [num_puntos_interes, 2], solamente con las coordenadas 
    #                      de los puntos de interes descritos. Tipo int64  <class 'numpy.ndarray'>
    #
    # NOTA: no modificar los valores por defecto de las variables de entrada vtam y nbins, 
    #       pues se utilizan para verificar el correcto funciomaniento de esta funcion
    """   

    # creamos listas para los descriptores y las nuevas coordenadas
    descriptores = [] 
    new_coords_esquinas = []

    # normalizamos la imagen en el rango [0,1]
    img_norm = normalizar(imagen.astype(np.float64))

    if tipoDesc == 'hist':  
        for coord in coords_esquinas:
            # obtenemos las coordenadas de las esquinas de la matriz de vecindarios
            coord_x1 = coord[0] - int(vtam/2)
            coord_x2 = coord[0] + int(vtam/2) + 1
            coord_y1 = coord[1] - int(vtam/2)
            coord_y2 = coord[1] + int(vtam/2) + 1
            # print(coord_x1, coord_x2, coord_y1, coord_y2)
            if coord_x1 >= 0 and coord_x2 <= img_norm.shape[0] and coord_y1 >= 0 and coord_y2 <= img_norm.shape[1]:
                # añadimos el punto a los nuevos puntos de interés
                new_coords_esquinas.append(coord)
                # adquirimos la matriz de vecinos
                matriz = img_norm[coord_x1 : coord_x2, coord_y1 : coord_y2]
                # hallamos y añadimos el histograma actualizado a los descriptores
                histogram = np.histogram(matriz, nbins, range = (0,1))[0]
                # metemos el histograma normalizado
                descriptores.append(histogram/np.sum(histogram)) 
                    

    elif tipoDesc == 'mag-ori':
        # derivada con respecto de x al cuadrado
        d_x = ndimage.sobel(img_norm, axis=0, mode='constant')
        # derivada con respecto de y al cuadrado
        d_y = ndimage.sobel(img_norm, axis=1, mode='constant')

        # sacamos la magnitud(raiz cuadrada de las derivadas al cuadrado)
        magnitud = np.sqrt(d_x**2 + d_y**2)

        # orientacion del gradiente en grados entre [0, 360]
        orientacion = np.rad2deg(np.arctan2(d_x, d_y))
        orientacion = np.where(orientacion < 0, orientacion + 360, orientacion)
        # tomamos el 360 como 0
        orientacion %= 360

        # creamos el histograma en 'bins' niveles desde 0 hasta 360 grados
        intervalos_cuantificacion = np.linspace(0, 360, num=nbins+1)

        histograma_mag_ori = [0.0] * int(nbins)
        
        for coord in coords_esquinas:
            # obtenemos las coordenadas de las esquinas de la matriz de vecindarios
            coord_x1 = coord[0] - int(vtam/2)
            coord_x2 = coord[0] + int(vtam/2) + 1
            coord_y1 = coord[1] - int(vtam/2)
            coord_y2 = coord[1] + int(vtam/2) + 1
            if coord_x1 >= 0 and coord_x2 <= img_norm.shape[0] and coord_y1 >= 0 and coord_y2 <= img_norm.shape[1]:  
                # hallamos la magnitud y la orientacion de la matriz de vecinos
                matriz_magnitud =  magnitud[coord_x1 : coord_x2, coord_y1 : coord_y2]
                matriz_orientacion = orientacion[coord_x1 : coord_x2, coord_y1 : coord_y2]
                # añadimos el punto a los nuevos puntos de interés
                new_coords_esquinas.append(coord)

                # indices del histograma en los que tiene que ir cada valor de la matriz de magnitudes.
                # Empezamos desde el 1 de manera que los indices vayan de 0 a nbins
                indices = np.digitize(matriz_orientacion, intervalos_cuantificacion)
                  
                # recorremos los indices que sacamos en digitize
                # para poder ir sacando sus valores de la matriz de magnitudes  
                for i in range(0, indices.shape[0]):
                    for j in range(0, indices.shape[1]):
                        # metemos en el histograma la suma de las magnitudes
                        # correspondientes a cada angulo 
                        histograma_mag_ori[indices[i, j]-1] += matriz_magnitud[i, j]

                descriptores.append(histograma_mag_ori)        
    # convertimos a array ambas listas         
    return np.asarray(descriptores), np.asarray(new_coords_esquinas)

if __name__ == "__main__":    
    print("Practica 2 - Tarea 2 - Test autoevaluación\n")                

    ## tests descriptor tipo 'hist' (tarea 2a)
    print("Tests completados = " + str(test_p2_tarea2(disptime=-1,stop_at_error=False,debug=False,tipoDesc='hist'))) #analizar todas las imagenes y esquinas del test
    #print("Tests completados = " + str(test_p2_tarea2(disptime=1,stop_at_error=False,debug=False,tipoDesc='hist'))) #analizar todas las imagenes y esquinas del test, mostrar imagenes con resultados (1 segundo)
    #print("Tests completados = " + str(test_p2_tarea2(disptime=-1,stop_at_error=True,debug=True,tipoDesc='hist'))) #analizar todas las imagenes y esquinas del test, pararse en errores y mostrar datos
    #print("Tests completados = " + str(test_p2_tarea2(disptime=-1,stop_at_error=True,debug=True,tipoDesc='hist',imgIdx = 3, poiIdx = 7))) #analizar solamente imagen #2 y esquina #7    

    ## tests descriptor tipo 'mag-ori' (tarea 2b)
    #print("Tests completados = " + str(test_p2_tarea2(disptime=-1,stop_at_error=False,debug=False,tipoDesc='mag-ori'))) #analizar todas las imagenes y esquinas del test
    #print("Tests completados = " + str(test_p2_tarea2(disptime=0.1,stop_at_error=False,debug=False,tipoDesc='mag-ori'))) #analizar todas las imagenes y esquinas del test, mostrar imagenes con resultados (1 segundo)
    #print("Tests completados = " + str(test_p2_tarea2(disptime=-1,stop_at_error=True,debug=True,tipoDesc='mag-ori'))) #analizar todas las imagenes y esquinas del test, pararse en errores y mostrar datos
    #print("Tests completados = " + str(test_p2_tarea2(disptime=1,stop_at_error=True,debug=True,tipoDesc='mag-ori',imgIdx = 3,poiIdx = 7))) #analizar solamente imagen #1 y esquina #7          