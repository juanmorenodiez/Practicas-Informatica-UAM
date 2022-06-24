# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 3: Reconocimiento de escenas con modelos BOW
# Memoria - Pregunta 3.4

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from math import gamma
from p3_tarea1 import obtener_bags_of_words
from p3_tarea1 import construir_vocabulario
from p3_tarea2 import obtener_features_hog
from p3_utils import load_image_dataset, create_results_webpage
from p3_pregunta_31 import traducir_etiquetas

from sklearn.model_selection import train_test_split
from sklearn import svm
from sklearn.model_selection import GridSearchCV
from sklearn.svm import SVC

def non_linear_svm_pipeline(bow_tam, web_page=False):
    # lectura del dataset
    dataset_path ='./datasets/scenes15'
    data = load_image_dataset(container_path=dataset_path, shuffle=True, 
                load_content=True, resize_shape=(200,200), max_per_category=200)

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

    # creamos los modelos con kernels no lineales
    svm_rbf = svm.SVC(kernel='rbf')
    svm_poly = svm.SVC(kernel='poly')

    # ajustamos el modelo a los datos
    svm_rbf.fit(descriptores_train, etiquetas_train)
    svm_poly.fit(descriptores_train, etiquetas_train)

    # evaluamos clasificador con los datos de test
    score_svm_rbf = svm_rbf.score(descriptores_test, etiquetas_test)
    score_svm_poly = svm_poly.score(descriptores_test, etiquetas_test)

    predicciones_1 = svm_rbf.predict(descriptores_test)
    predicciones_2 = svm_poly.predict(descriptores_test)

    # traducimos todas las listas para poder analizar el problema
    # pasandole los parametros correctamente a create_results_webpage
    lista_predicciones_1 = traducir_etiquetas(predicciones_1, data['target_names'])
    lista_predicciones_2 = traducir_etiquetas(predicciones_2, data['target_names'])
    lista_etiquetas_train = traducir_etiquetas(etiquetas_train, data['target_names'])
    lista_etiquetas_test = traducir_etiquetas(etiquetas_test, data['target_names'])

    # si queremos analizar los resultados con dicha funcion
    if web_page is True:
        matriz_confusion_1 = create_results_webpage(train_data, test_data, lista_etiquetas_train,
                         lista_etiquetas_test, data['target_names'], abbr_categories,
                         lista_predicciones_1, 'HOG_BOW_SVM_RBF')
        matriz_confusion_2 = create_results_webpage(train_data, test_data, lista_etiquetas_train,
                         lista_etiquetas_test, data['target_names'], abbr_categories,
                         lista_predicciones_2, 'HOG_BOW_SVM_POLY')                 

    print("Score para la SVM con kernel no-lineal rbf: {}".format(score_svm_rbf))
    print("Score para la SVM con kernel no-lineal poly: {}".format(score_svm_poly))

if __name__ == "__main__":
    # 75 de vocab size es el mejor resultado para svm lineal
    non_linear_svm_pipeline(bow_tam=75, web_page=True) 