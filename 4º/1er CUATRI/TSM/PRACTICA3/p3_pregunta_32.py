# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 3: Reconocimiento de escenas con modelos BOW
# Memoria - Pregunta 3.2

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from p3_pregunta_31 import knn_pipeline

if __name__ == "__main__":
    #for x in range(1, 23, 2):
        #knn_pipeline(neighbours=x, bow_tam=75)
    # usamos el modelo knn con los parametros que han obtenido mejores
    # resultados en accuracy y habilitamos los resultados de la matriz de confusion
    knn_pipeline(neighbours=19, bow_tam=75, web_page=True)           