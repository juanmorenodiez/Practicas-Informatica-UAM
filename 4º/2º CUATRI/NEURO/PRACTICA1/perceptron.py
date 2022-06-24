from neurona import Neurona, Tipo
from red_neuronal import RedNeuronal
from capa import Capa
import numpy as np
import os
import matplotlib.pyplot as plt

def compare_lists(list1, list2):
    """Función que comprueba que dos listas tengan
    el mismo contenido en las mismas posiciones.
    Nos sirve para comparar los valores de salida de
    la red neuronal con los valores esperados.

    Args:
        list1 (list): primera lista a comprobar
        list2 (list): segunda lista a comprobar

    Returns:
        boolean: esta función devolverá True en caso de que
        las dos listas tengan el mismo contenido en las mismas
        posiciones, sino, dvolverá False
    """
    count = 0
    for index, elem in enumerate(list1):
        if elem == list2[index]:
            count += 1

    if count == len(list1):
        return True
    else:
        return False

def check_matriz_pesos(matriz):
    """Funcion que comprueba que una matriz
    tenga el mismo contenido en todas las filas. 
    Sirve para que en cada época se compruebe
    esa condición.

    Args:
        matriz (numpy.ndarray): array numpy a comprobar

    Returns:
        boolean: devuelve True en caso de que todas las filas
        del array numpy tengan el mismo contenido, en caso contrario,
        devolverá False
    """
    return np.all(np.all(matriz == matriz[0,:], axis = 1))

def predicciones_a_fichero(fila_test, valores_salida, nombre_fichero):
    """Función que va escribiendo las predicciones de la
    red neuronal en un fichero

    Args:
        fila_test (list): ejemplo del conjunto de test
        valores_salida (list): valores predichos para el ejemplo de test
        nombre_fichero (str): nombre del fichero en el que se escribirán
        las predicciones
    """
    file = open("predicciones/" + nombre_fichero, "a+")

    for i in range(len(fila_test)):
        file.write(str(fila_test[i]) + "  ")

    for j in range(len(valores_salida)):
        file.write(str(valores_salida[j]) + "  ")   
    file.write("\n")

def obtener_grafica_ecm(list_epocas, list_ecms):
    plt.title("ECM por época para Perceptron")

    plt.xlabel('Epocas')
    plt.ylabel('ECM')
    plt.plot(list_epocas, list_ecms)

    plt.show()
    
def perceptron_entrenamiento(x_train, y_train, num_epocas=100, constante_aprendizaje = 1, umbral = 0.2, grafica=False):
    # creamos red neuronal
    perceptron = RedNeuronal()

    # creamos capas de la red
    input_layer = Capa()
    output_layer = Capa()

    # añadimos tantas neuronas de entrada como columnas haya en x_train
    for i in range(x_train.shape[1]):
        input_layer.añadir(Neurona(umbral=0, tipo="Directa"))

    # creamos el sesgo y lo metemos a la capa de entrada
    neurona_sesgo = Neurona(umbral=0, tipo="Sesgo")
    input_layer.añadir(neurona_sesgo)    

    # añadimos tantas neuronas de salida como columnas haya en y_train
    for index_salidas in range(y_train.shape[1]):
        output_layer.añadir(Neurona(umbral=umbral, tipo="Perceptron"))  
  
    # conectamos capa de entrada a la capa de salida
    # inicalizando pesos y sesgo a 0
    input_layer.conectar_capa(output_layer, 0.0, 0.0)

    # añadimos capas a la red neuronal
    perceptron.añadir(input_layer)
    perceptron.añadir(output_layer) 

    # inicializamos toda la red neuronal
    perceptron.inicializar()
  
    contador_epocas = 0
    boolean_pesos = False

    # para calculo de la grafica del ecm
    lista_epocas_grafica = []
    lista_ecms_crafica = []

    while(contador_epocas < num_epocas):
        # 1. esta es la condicion de parada
        if boolean_pesos == True:
            break
        
        # para el calculo del ecm
        lista_sumas_ecm = []
        # para guardar todos los pesos durante la epoca
        matriz_pesos_epoca = []
        print("Época nº {}".format(contador_epocas + 1))
        j = 0
        # 2. para cada par de entrenamiento
        for fila_train in x_train:
            lista_pesos = []

            # damos valor a los valores de entrada de las neuronas
            for i, neurona_entrada in enumerate(input_layer.neuronas[:-1]):
                neurona_entrada.inicializar(fila_train[i])

            # damos valor al sesgo
            input_layer.neuronas[-1].inicializar(1.0)    

            # 3. establecemos las activaciones a las neuronas de entrada
            input_layer.disparar()
            output_layer.inicializar()
            input_layer.propagar()

            # 4. calculamos las respuestas de las neuronas de salida
            output_layer.disparar()
            
            # valores a la salida de la red
            valores_salida = [neurona.valor_salida for neurona in output_layer.neuronas]
            # salidas esperadas para el dato de entrenamiento correspondiente
            valores_esperados = [salidas for salidas in y_train[j][:]]

            # cálculo previo para el ecm
            suma = 0
            for index_salidas in range(len(valores_esperados)):
                resta = valores_salida[index_salidas] - valores_esperados[index_salidas]
                resta_al_cuadrado = resta **2
                suma += resta_al_cuadrado
                lista_sumas_ecm.append(suma)

            # ajustamos pesos si la salida es distinta a lo esperado
            if compare_lists(valores_salida, valores_esperados) == False:
                for index, neurona in enumerate(input_layer.neuronas):
                    if neurona.tipo == Tipo.SESGO.value:
                        for index1, conexion in enumerate(neurona.conexiones):
                            variacion_sesgo = constante_aprendizaje*valores_esperados[index1]
                            conexion.peso += variacion_sesgo
                            conexion.peso_anterior = conexion.peso
                            lista_pesos.append(conexion.peso)
                    else:
                        for index2, conexion in enumerate(neurona.conexiones):
                            variacion_peso = constante_aprendizaje*valores_esperados[index2]*x_train[j][index]
                            conexion.peso += variacion_peso
                            conexion.peso_anterior = conexion.peso
                            lista_pesos.append(conexion.peso)
            # ajustamos pesos si la salida es la misma a lo esperado                
            else:
                for neurona in input_layer.neuronas:
                    if neurona.tipo == Tipo.SESGO.value:
                        for conexion in neurona.conexiones:
                            conexion.peso = conexion.peso_anterior
                            lista_pesos.append(conexion.peso)   
                    else:
                        for conexion in neurona.conexiones:
                            conexion.peso = conexion.peso_anterior
                            lista_pesos.append(conexion.peso)

            # metemos en esta matriz los pesos obtenidos en cada ejemplo  
            matriz_pesos_epoca.append(lista_pesos)
            j += 1
        
        # calculo del ecm
        ecm = (sum(lista_sumas_ecm) / len(lista_sumas_ecm))
        print("ECM: {}\n".format(ecm))

        lista_epocas_grafica.append(contador_epocas)
        lista_ecms_crafica.append(ecm)

        matriz_pesos_epoca_np = np.array(matriz_pesos_epoca)
        # comprobamos que todas las filas de la matriz sean iguales,
        # es decir, que los pesos sean los mismos en cada ejemplo
        boolean_pesos = check_matriz_pesos(matriz_pesos_epoca_np)
        contador_epocas += 1 

    if grafica == True:
        obtener_grafica_ecm(lista_epocas_grafica, lista_ecms_crafica)
        
    return matriz_pesos_epoca_np[-1]  

def perceptron_clasificacion(x_test, y_test, pesos_entrenamiento, umbral=0.2, predicciones=False):
    if predicciones == True:
        try:
            os.mkdir("predicciones")
            print("Carpeta predicciones creada") 
        except FileExistsError:
            print("Carpeta predicciones ya existe")
    
    # creamos red neuronal
    perceptron = RedNeuronal()

    # creamos capas de la red
    input_layer = Capa()
    output_layer = Capa()

    # añadimos tantas neuronas de entrada como columnas haya en x_test
    for i1 in range(x_test.shape[1]):
        input_layer.añadir(Neurona(umbral=0, tipo="Directa"))

    # creamos el sesgo y lo metemos a la capa de entrada
    neurona_sesgo = Neurona(umbral=0, tipo="Sesgo")
    input_layer.añadir(neurona_sesgo) 

    # añadimos tantas neuronas de salida como columnas haya en y_test
    for i2 in range(y_test.shape[1]):
        output_layer.añadir(Neurona(umbral=umbral, tipo="Perceptron"))      
  
    # conectamos capa de entrada a la capa de salida
    # inicalizando los pesos a los valores que hemos obtenido del entrenamiento
    num_conexiones_totales = 0
    for neurona_entrada in input_layer.neuronas:
        for neurona_salida in output_layer.neuronas:
            neurona_entrada.conectar(neurona_salida, pesos_entrenamiento[num_conexiones_totales])
            num_conexiones_totales += 1

    # añadimos capas a la red neuronal
    perceptron.añadir(input_layer)
    perceptron.añadir(output_layer) 

    # inicializamos toda la red neuronal
    perceptron.inicializar()

    j = 0
    aciertos = 0
    # por cada fila de test
    for fila_test in x_test:
        # damos valor a los valores de entrada de las neuronas
        for i3, neurona_entrada in enumerate(input_layer.neuronas[:-1]):
            neurona_entrada.inicializar(fila_test[i3])
            
        # damos valor al sesgo
        input_layer.neuronas[-1].inicializar(1.0)

        # 3. establecemos las activaciones a las neuronas de entrada
        input_layer.disparar()
        output_layer.inicializar()
        input_layer.propagar()
        
        # 4. calculamos las respuestas de las neuronas de salida
        output_layer.disparar()
            
        # valores a la salida de la red
        valores_salida = [neurona.valor_salida for neurona in output_layer.neuronas]
        valores_esperados = [salidas for salidas in y_test[j][:]]

        if predicciones == True:
            predicciones_a_fichero(fila_test, valores_salida, "predicciones_perceptron.txt")

        # comprobamos que todos los elementos de las dos listas 
        # sean iguales en las mismas posiciones
        if compare_lists(valores_salida, valores_esperados) == True:
            aciertos += 1

        j += 1

    porcentaje_aciertos = (aciertos/y_test.shape[0])
    return porcentaje_aciertos   
