# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 3: Reconocimiento de escenas con modelos BOW/BOF
# Tarea 1: modelo BOW/BOF

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

# librerias y paquetes por defecto
from numpy.lib.histograms import histogram
import scipy
from scipy.spatial.distance import cdist
from p3_tests import test_p3_tarea1
import numpy as np
from sklearn.cluster import KMeans

# PARAMETRO ITER NO TIENE SENTIDO QUE VALGA 1!!
def construir_vocabulario(list_img_desc, vocab_size=10, max_iter=300):
    """   
    # Esta funcion utiliza K-Means para agrupar los descriptores en "vocab_size" clusters.
    #
    # Argumentos de entrada:
    # - list_array_desc: Lista 1xN con los descriptores de cada imagen. Cada posicion de la lista 
    #                   contiene (MxD) numpy arrays que representan UNO O VARIOS DESCRIPTORES 
    #                   extraidos sobre la imagen
    #                   - M es el numero de vectores de caracteristicas/features de cada imagen 
    #                   - D el numero de dimensiones del vector de caracteristicas/feature.    
    #   - vocab_size: int, numero de palabras para el vocabulario a construir.    
    #   - max_iter: int, numero maximo de iteraciones del algoritmo KMeans
    #
    # Argumentos de salida:
    #   - vocabulario: Numpy array de tamaño [vocab_size, D], 
    #                   que contiene los centros de los clusters obtenidos por K-Means
    #
    #
    # NOTA: se sugiere utilizar la funcion sklearn.cluster.KMeans
    # https://scikit-learn.org/stable/modules/generated/sklearn.cluster.KMeans.html     
    """
    vocabulario = np.empty(shape=[vocab_size,list_img_desc[0].shape[1]]) # iniciamos la variable de salida (numpy array)
    
    # convertimos la lista de descriptores en un array numpy
    conc = np.concatenate(list_img_desc)

    # realizamos la agrupacion con los parametros adecuados
    vocabulario = KMeans(n_clusters=vocab_size, random_state=0, max_iter=max_iter).fit(conc)

    # devolvemos los centros de las agrupaciones(clusters)
    return vocabulario.cluster_centers_

def obtener_bags_of_words(list_img_desc, vocab):
    """
    # Esta funcion obtiene el Histograma Bag of Words para cada imagen
    #
    # Argumentos de entrada:
    # - list_img_desc: Lista 1xN con los descriptores de cada imagen. Cada posicion de la lista 
    #                   contiene (MxD) numpy arrays que representan UNO O VARIOS DESCRIPTORES 
    #                   extraidos sobre la imagen
    #                   - M es el numero de vectores de caracteristicas/features de cada imagen 
    #                   - D el numero de dimensiones del vector de caracteristicas/feature.  
    #   - vocab: Numpy array de tamaño [vocab_size, D], 
    #                  que contiene los centros de los clusters obtenidos por K-Means.   
    #
    # Argumentos de salida: 
    #   - list_img_bow: Array de Numpy [N x vocab_size], donde cada posicion contiene 
    #                   el histograma bag-of-words construido para cada imagen.
    #
    """
    # iniciamos la variable de salida (numpy array)
    list_img_bow = np.empty(shape=[len(list_img_desc),len(vocab)])
    # creamos una lista auxiliar en la que se irán
    # introduciendo los histogramas
    histogramas = []

    # para cada descriptor obtenemos las distancias 
    # entre descriptor y vocabulario
    for desc in list_img_desc:
        distancias = cdist(desc, vocab)
        
        # histograma con la misma longitud al vocabulario
        histograma = np.zeros(shape=len(vocab))

        # recorremos la matriz de distancias fila a fila
        for fila in distancias:
            # sacamos las coordenadas de la matriz 
            # cuya distancia es minima para cada fila
            index = np. where(fila == min(fila))
            # incrementamos el valor del histograma para ese indice
            histograma[index[0]] += 1

        # introducimos el histograma normalizado a la lista de histogramas
        histogramas.append(histograma/sum(histograma).astype(np.float64))

    # lo transformamos al formato adecuado ('numpy ndarray')             
    list_img_bow = np.asarray(histogramas)

    return list_img_bow

if __name__ == "__main__":    
    dataset_path = './datasets/scenes15/'
    print("Practica 3 - Tarea 1 - Test autoevaluación\n")                    
    print("Tests completados = " + str(test_p3_tarea1(dataset_path,stop_at_error=False,debug=False))) #analizar todos los casos sin pararse en errores ni mostrar datos
    #print("Tests completados = " + str(test_p3_tarea1(dataset_path,stop_at_error=True,debug=True))) #analizar todos los casos, pararse en errores y mostrar datos