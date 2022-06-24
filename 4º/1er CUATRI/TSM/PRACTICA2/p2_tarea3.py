# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 2: Extraccion, descripcion y correspondencia de caracteristicas locales
# Tarea 3:  Similitud y correspondencia de puntos de interes

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from p2_tests import test_p2_tarea3

import numpy as np

def correspondencias_puntos_interes(descriptores_imagen1, descriptores_imagen2, tipoCorr='mindist',max_distancia=25, max_nndr=0.75):
    """
    # Esta funcion determina la correspondencias entre dos conjuntos de descriptores mediante
    # el calculo de la similitud entre los descriptores.
    #
    # El parametro 'tipoCorr' determina el criterio de similitud aplicado 
    # para establecer correspondencias entre pares de descriptores:
    #   - Criterio 'mindist': minima distancia euclidea entre descriptores 
    #                         menor que el umbral 'max_distancia'
    #   - Criterio 'nndr': minima distancia euclidea entre descriptores 
    #                      menor que el umbral 'max_distancia'
    #                      y con ratio nndr menor que el umbral 'nndr'. La segunda distancia mínima no debe              
    #  
    # Argumentos de entrada:
    #   - descriptores1: numpy array con dimensiones [numero_descriptores, longitud_descriptor] 
    #                    con los descriptores de los puntos de interes de la imagen 1.        
    #   - descriptores2: numpy array con dimensiones [numero_descriptores, longitud_descriptor] 
    #                    con los descriptores de los puntos de interes de la imagen 2.        
    #   - tipoCorr: cadena de caracteres que indica el tipo de criterio para establecer correspondencias
    #   - max_distancia: valor de tipo double o float utilizado por el criterio 'mindist' y 'nndr', 
    #                    que determina si se aceptan correspondencias entre descriptores 
    #                    con distancia minima menor que 'max_distancia' 
    #   - max_nndr: valor de tipo double o float utilizado por el criterio 'nndr', que determina 
    #                    si se aceptan correspondencias entre descriptores con ratio nndr menor que 'max_nndr' 
    #
    # Argumentos de salida
    #   - correspondencias: numpy array con dimensiones [numero_correspondencias, 2] de tipo int64 
    #                       que determina correspondencias entre descriptores de imagen 1 e imagen 2.
    #                       Por ejemplo: 
    #                       correspondencias[0,:]=[5,22] significa que el descriptor 5 de la imagen 1 
    #                                                  corresponde con el descriptor 22 de la imagen 2. 
    #                       correspondencias[1,:]=[6,23] significa que el descriptor 6 de la imagen 1 
    #                                                  corresponde con el descriptor 23 de la imagen 2.
    #
    # NOTA: no modificar los valores por defecto de las variables de entrada tipoCorr y max_distancia, 
    #       pues se utilizan para verificar el correcto funciomaniento de esta funcion
    #
    # CONSIDERACIONES: 
    # 1) La funcion no debe permitir correspondencias de uno a varios descriptores. Es decir, 
    #   un descriptor de la imagen 1 no puede asignarse a multiples descriptores de la imagen 2 
    # 2) En el caso de que existan varios descriptores de la imagen 2 con la misma distancia minima 
    #    con algún descriptor de la imagen 1, seleccione el descriptor de la imagen 2 con 
    #    indice/posicion menor. Por ejemplo, si las correspondencias [5,22] y [5,23] tienen la misma
    #    distancia minima, seleccione [5,22] al ser el indice 22 menor que 23
    """     # iniciamos la variable de salida (numpy array) 

    # creamos listas para los descriptores y las nuevas coordenadas
    correspondencias = []       
    indices = []
    
    if tipoCorr == 'minDist':
        for filaIndice, fila1 in enumerate(descriptores_imagen1):
            # variable que nos indicara si se tiene que añadir algún elemento
            elemento = False
            # incializamos la lista de distancias para cada fila
            distancias = []
            for fila2 in descriptores_imagen2:
                # calculamso la distancia euclidea y la añadimos a la lista
                raiz = np.linalg.norm(fila1 - fila2)
                distancias.append(raiz)
            
            # incializamos min_distancia con el valor que nos pasan por referencia en al funcion
            # para calcular cual es la distancia mas corta siendo menor que max_distancia
            min_distancia = max_distancia
            for i, distancia in enumerate(distancias):
                # comprobamos que se cumple lo dicho anteriormente 
                if distancia < min_distancia and i not in indices:
                    # elemento a true ya que se ha encontrado una distancia optima
                    elemento = True
                    # cogemos el indice de la distancia y actualizamos la distancia minima
                    indice = i
                    min_distancia = distancia
            
            # si se ha encontrado una distancia optima añadimos la correspondencia como una tupla
            if elemento is True:
                indices.append(indice)
                correspondencias.append((filaIndice, indice))
  
    # convertimos al tupla a array
    return np.array(correspondencias)

if __name__ == "__main__":
    print("Practica 2 - Tarea 3 - Test autoevaluación\n")                

    ## tests correspondencias tipo 'minDist' (tarea 3a)
    print("Tests completados = " + str(test_p2_tarea3(disptime=-1,stop_at_error=True,debug=True,tipoDesc='hist',tipoCorr='minDist'))) #analizar todas las imagenes con descriptor 'hist' y ver errores
    #print("Tests completados = " + str(test_p2_tarea3(disptime=-1,stop_at_error=False,debug=False,tipoDesc='hist',tipoCorr='minDist'))) #analizar todas las imagenes con descriptor 'hist'
    #print("Tests completados = " + str(test_p2_tarea3(disptime=1,stop_at_error=False,debug=False,tipoDesc='mag-ori',tipoCorr='minDist'))) #analizar todas las imagenes con descriptor 'mag-ori'

    #print("Tests con hist = " + str(test_p2_tarea3(disptime=0,imgIdx=0,debug=False,tipoDesc='hist',tipoCorr='minDist')))
    #print("Tests con mag-ori = " + str(test_p2_tarea3(disptime=0,imgIdx=0,debug=False,tipoDesc='mag-ori',tipoCorr='minDist')))
    