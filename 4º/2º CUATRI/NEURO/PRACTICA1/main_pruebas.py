from adaline import adaline_clasificacion, adaline_entrenamiento
from perceptron import perceptron_clasificacion, perceptron_entrenamiento
import lectura_datos
    

if __name__ == '__main__':
    x_train, y_train, x_test, y_test = lectura_datos.leer3("problema_real2.txt", "problema_real2_no_etiquetados.txt")
    # x_train, y_train = lectura_datos.leer2("and.txt")

    #pesos_entrenamiento3 = perceptron_entrenamiento(x_train, y_train)
    #print("Pesos al acabar entrenamiento: {}".format(pesos_entrenamiento2))

    pesos_entrenamiento_p = perceptron_entrenamiento(x_train, y_train, 
                                                    num_epocas=100, 
                                                    constante_aprendizaje=1, 
                                                    umbral=0.01,
                                                    grafica=True)
    aciertos_p = perceptron_clasificacion(x_test, y_test,
                                            pesos_entrenamiento_p,
                                            umbral=0.01,
                                            predicciones=True) 

    pesos_entrenamiento_a = adaline_entrenamiento(x_train, y_train, 
                                                    num_epocas=100, 
                                                    constante_aprendizaje=0.01, 
                                                    tolerancia=0.01,
                                                    grafica=True)
    aciertos_a = adaline_clasificacion(x_test, y_test,
                                        pesos_entrenamiento_a,
                                        predicciones=True) 


    



    