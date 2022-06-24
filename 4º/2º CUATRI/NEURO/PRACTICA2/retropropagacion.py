from neurona import Neurona
from red_neuronal import RedNeuronal
from capa import Capa
import matplotlib.pyplot as plt

def derivada_sigmoide_bipolar(salida):
    """Función que devuelve el cáculo de la derivada
    de la sigmoide bipolar

    Args:
        salida (float): valor a calcular

    Returns:
        float: valor calculado
    """
    return 0.5 * (1 + salida) * (1 - salida)


def calcular_salida_real(salida_red):
    """Función de test para la salida
    de la red neuronal. Asigna 1.0 al valor
    más alto de las salidas de la red y al resto
    le asigna -1.0

    Args:
        salida_red (list): lista con valores de salida de la red neuronal

    Returns:
        list: lista con valores de salida una vez pasados por la función de test
    """
    lista_salida = []
    
    if len(salida_red) == 1:
        if salida_red[0] >= 0:
            lista_salida.append(1.0)
        else:
            lista_salida.append(-1.0)
    else:
        max_index = salida_red.index(max(salida_red))
        for i, salida in enumerate(salida_red):
            if i == max_index:
                lista_salida.append(1.0)
            else:
                lista_salida.append(-1.0)

    return lista_salida

def calcular_acierto(salida_real, valores_esperados):
    """Función que compara la salida de la red con lo esperado
    y devuelve 1 en caso de que la red haya acertado. Si no acierta,
    devolverá 0.

    Args:
        salida_real (list): salida de la red neuronal
        valores_esperados (list): valores que deberían salir

    Returns:
        int: 1 si ha acertado, 0 si no
    """
    contador = 0
    for i, num in enumerate(salida_real):
        if valores_esperados[i] == num:
            contador += 1
    
    if contador == len(valores_esperados):
        return 1
    else:
        return 0

def obtener_grafica_ecm(list_epocas, list_ecms):
    """Función que muestra la gráfica con la evolución del
    error cuadrático medio para cada época

    Args:
        list_epocas (list): lista de epocas
        list_ecms (list): lista de errores cuadráticos medios
    """
    plt.title('ECM por época para Retropropagación')

    plt.xlabel('Epocas')
    plt.ylabel('ECM')
    plt.plot(list_epocas, list_ecms)

    plt.show()

def obtener_grafica_aciertos(list_epocas, list_aciertos):
    """Función que muestra la gráfica con la evolución del
    porcentaje de acierto para cada época

    Args:
        list_epocas (list): lista de epocas
        list_aciertos (list): lista de porcentajes de acierto
    """
    plt.title('Porcentaje de aciertos por época para Retropropagación')

    plt.xlabel('Epocas')
    plt.ylabel('Porcentaje Aciertos')
    plt.plot(list_epocas, list_aciertos)

    plt.show()

def predicciones_a_fichero(fila_test, valores_salida, nombre_fichero):
    """Función que va escribiendo las predicciones de la
    red neuronal en un fichero

    Args:
        fila_test (list): ejemplo del conjunto de test
        valores_salida (list): valores predichos para el ejemplo de test
        nombre_fichero (str): nombre del fichero en el que se escribirán
        las predicciones
    """
    file = open(nombre_fichero, "a+")

    for i in range(len(fila_test)):
        file.write(str(fila_test[i]) + "  ")

    for j in range(len(valores_salida)):
        file.write(str(valores_salida[j]) + "  ")   
    file.write("\n")

def algoritmo_retropropagacion(x_train, y_train, x_test, y_test, neuronas_oculta, num_epocas=100, constante_aprendizaje=1, graficas=False, predicciones=False):
    # creamos red neuronal
    perceptron = RedNeuronal()

    # creamos capas de la red
    input_layer = Capa()
    hidden_layer = Capa()
    output_layer = Capa()

    # añadimos tantas neuronas de entrada como columnas haya en x_train
    for i in range(x_train.shape[1]):
        input_layer.añadir(Neurona(umbral=0, tipo="Directa"))

    # creamos el sesgo y lo añadimos a la capa de entrada
    neurona_sesgo_entrada = Neurona(umbral=0, tipo="Sesgo")
    input_layer.añadir(neurona_sesgo_entrada)

    # añadimos las neuronas de la capa oculta
    for i in range(neuronas_oculta):
        hidden_layer.añadir(Neurona(0, tipo="PerceptronSigmoide"))

    # creamos el sesgo y lo añadimos a la capa oculta
    neurona_sesgo_oculta = Neurona(umbral=0, tipo="Sesgo")
    hidden_layer.añadir(neurona_sesgo_oculta)

    # añadimos tantas neuronas de salida como columnas haya en y_train
    for index_salidas in range(y_train.shape[1]):
        output_layer.añadir(Neurona(umbral=0, tipo="PerceptronSigmoide"))  

    # conectamos capa de entrada a la capa oculta
    # inicalizando pesos y sesgo a valores aleatorios pequeños
    input_layer.conectar_capa(hidden_layer, -0.5, 0.5)

    # conectamos capa oculta a la capa de salida
    # inicalizando pesos y sesgo a valores aleatorios pequeños
    hidden_layer.conectar_capa(output_layer, -0.5, 0.5)
    
    # añadimos capas a la red neuronal
    perceptron.añadir(input_layer)
    perceptron.añadir(hidden_layer)
    perceptron.añadir(output_layer)

    # inicializamos toda la red neuronal
    perceptron.inicializar()
  
    lista_epocas_grafica = []
    lista_ecms_crafica = []
    lista_porcentajes_acierto_grafica = []
    contador_epocas = 0
    while(contador_epocas < num_epocas):
        print("Época nº {}".format(contador_epocas + 1))
        j = 0

        lista_sumas_ecm = []
        lista_aciertos = []
        for fila_train in x_train:
            # damos valor a los valores de entrada de las neuronas
            for i, neurona_entrada in enumerate(input_layer.neuronas[:-1]):
                neurona_entrada.inicializar(fila_train[i])

            # damos valor al sesgo de la capa de entrada
            input_layer.neuronas[-1].inicializar(1.0) 

            # 3. establecemos las activaciones a las neuronas de entrada
            input_layer.disparar()
            hidden_layer.inicializar()

            # damos valor al sesgo de la capa oculta
            hidden_layer.neuronas[-1].inicializar(1.0)

            # 4. calculamos la respuesta de las neuronas de la capa oculta
            input_layer.propagar()
            hidden_layer.disparar()  

            # 5. calculamos la respuesta de las neuronas de salida
            output_layer.inicializar()
            hidden_layer.propagar()

            # valores a la salida de la capa oculta
            f_z_in = [neurona.valor_salida for neurona in hidden_layer.neuronas]
            
            # pasamos la salida por su funcion de activacion correspondiente
            output_layer.disparar()

            # valores a la salida de la capa de salida
            f_y_in = [neurona.valor_salida for neurona in output_layer.neuronas]
            # salidas esperadas para el dato de entrenamiento correspondiente
            valores_esperados = [salidas for salidas in y_train[j][:]]

            # inicializamos lista de errores de la capa oculta
            deltas_in = [0 for i in range(0, len(hidden_layer.neuronas)-1)]

            # calculamos la salida real de la red
            salida_real = calcular_salida_real(f_y_in)

            valor_acierto = calcular_acierto(salida_real, valores_esperados)
            lista_aciertos.append(valor_acierto)

            # cálculo previo para el ecm
            suma = 0
            for index_salidas in range(len(valores_esperados)):
                resta = f_y_in[index_salidas] - valores_esperados[index_salidas]
                resta_al_cuadrado = resta **2
                suma += resta_al_cuadrado
            
            # para el ecm sacamos los errores al cuadrado de cada neurona de salida
            # y los sumamos y asi tenemos un ecm para cada ejemplo de entrenamiento
            lista_sumas_ecm.append(suma)
            
            # 6. retropropagacion del error
            for index, neurona_salida in enumerate(output_layer.neuronas):
                # calculamos el error
                resta = valores_esperados[index] - f_y_in[index]
                derivada = derivada_sigmoide_bipolar(f_y_in[index])
                error_salida = resta * derivada
               
                # calculamos correcciones de los pesos y actualizamos
                for index1, neurona_oculta in enumerate(hidden_layer.neuronas[:-1]):
                    for conexion in neurona_oculta.conexiones:
                        if conexion.neurona == neurona_salida:
                            deltas_in[index1] += conexion.peso * error_salida
                            correccion_peso_salida = constante_aprendizaje * error_salida * f_z_in[index1]
                            conexion.peso += correccion_peso_salida
                # calculamos correccion del sesgo y actualizamos
                for conexion_sesgo in hidden_layer.neuronas[-1].conexiones:
                    if conexion_sesgo.neurona == neurona_salida:
                        correccion_sesgo_salida = constante_aprendizaje * error_salida
                        conexion_sesgo.peso += correccion_sesgo_salida

            # cálculo de los errores de la capa oculta       
            deltas = [(num * derivada_sigmoide_bipolar(f_z_in[i])) for i, num in enumerate(deltas_in)]
            
            # retropropagacion del error a la siguiente capa 
            for index2, neurona_oculta in enumerate(hidden_layer.neuronas[:-1]):
                # calculamos correccciones de los pesos y actuakizamos
                for index3, neurona_entrada in enumerate(input_layer.neuronas[:-1]):
                    for conexion in neurona_entrada.conexiones:
                        if conexion.neurona == neurona_oculta:
                            correccion_peso_oculta = constante_aprendizaje * neurona_entrada.valor_salida * deltas[index2]
                            conexion.peso += correccion_peso_oculta   
                # calculamos correccion del sesgo y actualizamos    
                for conexion in input_layer.neuronas[-1].conexiones:
                    if conexion.neurona == neurona_oculta:
                        correccion_sesgo_oculta = constante_aprendizaje * deltas[index2]
                        conexion.peso += correccion_sesgo_oculta                    
            j += 1
        
        ecm = sum(lista_sumas_ecm)/len(lista_sumas_ecm)
        porcentaje_aciertos = sum(lista_aciertos)/y_train.shape[0]
        print("ECM: {}".format(ecm))
        print("Porcentaje de acierto: {}\n".format(porcentaje_aciertos))

        lista_porcentajes_acierto_grafica.append(porcentaje_aciertos)
        lista_ecms_crafica.append(ecm)
        lista_epocas_grafica.append(contador_epocas)

        contador_epocas += 1 

    if graficas == True:
        obtener_grafica_ecm(lista_epocas_grafica, lista_ecms_crafica)  
        obtener_grafica_aciertos(lista_epocas_grafica, lista_porcentajes_acierto_grafica)
    
    # nos quedamos con los pesos una vez finalizado el entrenamiento y clasificamos
    lista_aciertos_test = []
    # proceso de clasificacion
    j = 0
    for fila_test in x_test:
        # damos valor a los valores de entrada de las neuronas
        for i3, neurona_entrada in enumerate(input_layer.neuronas[:-1]):
            neurona_entrada.inicializar(fila_test[i3])
        
        # damos valor al sesgo
        input_layer.neuronas[-1].inicializar(1.0)

        # 3. establecemos las activaciones a las neuronas de entrada
        input_layer.disparar()
        hidden_layer.inicializar()

        # damos valor al sesgo de la capa oculta
        hidden_layer.neuronas[-1].inicializar(1.0)

        # 4. calculamos la respuesta de las neuronas de la capa oculta
        input_layer.propagar()
        hidden_layer.disparar()  

        # 5. calculamos la respuesta de las neuronas de salida
        output_layer.inicializar()
        hidden_layer.propagar()

        output_layer.disparar()

        # valores a la salida de la red
        valores_salida = [neurona.valor_salida for neurona in output_layer.neuronas]
        valores_esperados = [salidas for salidas in y_test[j][:]]

        # calculamos la salida real de la red
        salida_real = calcular_salida_real(valores_salida)

        valor_acierto = calcular_acierto(salida_real, valores_esperados)
        lista_aciertos_test.append(valor_acierto)

        if predicciones == True:
            predicciones_a_fichero(fila_test, salida_real, "prediccion_problema_real2.txt")

        j+= 1

    porcentaje_aciertos = sum(lista_aciertos_test)/y_test.shape[0]
    return porcentaje_aciertos

    





    
