# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 3: Reconocimiento de escenas con modelos BOW
# Memoria - Pregunta 3.1

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from p3_tarea1 import obtener_bags_of_words
from p3_tarea1 import construir_vocabulario
from p3_tarea2 import obtener_features_hog
from p3_utils import load_image_dataset, create_results_webpage

from sklearn.model_selection import train_test_split
from sklearn.neighbors import KNeighborsClassifier

def traducir_etiquetas(lista, data):
    """Esta funcion traduce una lista dada
    al numero de clases del problema. Es decirm transforma
    los números de la clase a su etiqueta correspondiente.

    Args:
        lista (list): lista a transformar
        data (list): lista la cual pasamos para poder transformar
        en ese formato

    Returns:
        [list]: lista transformada
    """
    lista_traducida = []
    
    for num in lista:
        lista_traducida.append(data[num]) 

    return lista_traducida

def knn_pipeline(neighbours, bow_tam, web_page = False):
    # lectura del dataset
    dataset_path ='./datasets/scenes15'
    data = load_image_dataset(container_path=dataset_path, shuffle=True, 
                load_content=True, resize_shape=(200,200), max_per_category=200)
    # incluimos las categorias abreviadas
    abbr_categories = ['Bed','Cst','For','HWy','Ind','Cty','Kit','Liv','Mnt','Off','OC','Sto','St','Sub','Bld']            

    # division de datos entre train y test
    train_data, test_data, etiquetas_train, etiquetas_test = train_test_split(
                        data['filenames'], data['target'], test_size=0.2)

    # obtencion de las carcateristicas HOG de train
    caracteristicas_train = obtener_features_hog(train_data, tamano=100)

    # obtencion de las carcateristicas HOG de test
    caracteristicas_test = obtener_features_hog(test_data, tamano=100)

    # construir vocabulario con datos de entrenamiento
    vocabulario = construir_vocabulario(caracteristicas_train, max_iter=10, vocab_size=bow_tam)

    # obtener descriptores BOW para train/test
    descriptores_train = obtener_bags_of_words(caracteristicas_train, vocabulario)
    descriptores_test = obtener_bags_of_words(caracteristicas_test, vocabulario)

    # creamos el modelo
    model = KNeighborsClassifier(n_neighbors=neighbours)
    # ajustamos el modelo a los datos
    model.fit(descriptores_train, etiquetas_train)

    # evaluamos clasificador con los datos de test
    score = model.score(descriptores_test, etiquetas_test)
    predicciones = model.predict(descriptores_test)
    
    # traducimos todas las listas para poder analizar el problema
    # pasandole los parametros correctamente a create_results_webpage
    lista_predicciones = traducir_etiquetas(predicciones, data['target_names'])
    lista_etiquetas_train = traducir_etiquetas(etiquetas_train, data['target_names'])
    lista_etiquetas_test = traducir_etiquetas(etiquetas_test, data['target_names'])

    # si queremos analizar los resultados con dicha funcion
    if web_page is True:
        matriz_confusion = create_results_webpage(train_data, test_data, lista_etiquetas_train,
                         lista_etiquetas_test, data['target_names'], abbr_categories,
                         lista_predicciones, 'HOG_BOW_KNN')
     
    print("Score con {} vecinos y vocab_size {}: {}".format(neighbours, bow_tam, score))

if __name__ == "__main__":
    for x in range(25, 225, 25):
        knn_pipeline(neighbours=5, bow_tam=x)
    