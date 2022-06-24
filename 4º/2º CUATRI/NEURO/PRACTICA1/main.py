import argparse
import mp_frio_calor
import lectura_datos
import perceptron
import adaline


if __name__ == '__main__':
    # instancia del parser de argumentos
    parser = argparse.ArgumentParser(description = "Práctica 1 NEURO")

    # se añaden los argumentos que se van a usar al parser
    parser.add_argument("--ejecuta_mp", help="Ejecución de McCulloch-Pitts", nargs = 1, type = str)
    parser.add_argument("--ejecuta_perceptron", help="Ejecución del perceptrón", nargs = 1, type = str)
    parser.add_argument("--ejecuta_adaline", help="Ejecución del Adaline", nargs = 1, type = str)

    # parseo de argumentos
    args = parser.parse_args()

    if args.ejecuta_mp:
        mp_frio_calor.mp_frio_calor(args.ejecuta_mp[0])

    elif args.ejecuta_perceptron:
        print("Probando PERCEPTRON con fichero: {}\n".format(args.ejecuta_perceptron[0]))
        x_train, y_train, x_test, y_test = lectura_datos.leer1(args.ejecuta_perceptron[0], 0.7)
        pesos_entrenamiento = perceptron.perceptron_entrenamiento(x_train, y_train, 
                                                                    num_epocas=100, 
                                                                    constante_aprendizaje=1, 
                                                                    umbral=0.01,
                                                                    grafica=True)
        porcentaje_aciertos = perceptron.perceptron_clasificacion(x_test, y_test,
                                                                    pesos_entrenamiento,
                                                                    umbral=0.01,
                                                                    predicciones=False)
        print("SCORE: {}".format(porcentaje_aciertos))

    elif args.ejecuta_adaline:
        print("Probando ADALINE con fichero: {}\n".format(args.ejecuta_adaline[0]))
        x_train, y_train, x_test, y_test = lectura_datos.leer1(args.ejecuta_adaline[0], 0.7)
        pesos_entrenamiento = adaline.adaline_entrenamiento(x_train, y_train, 
                                                                    num_epocas=100, 
                                                                    constante_aprendizaje=0.01, 
                                                                    tolerancia=0.01,
                                                                    grafica=True)
        porcentaje_aciertos = adaline.adaline_clasificacion(x_test, y_test,
                                                                    pesos_entrenamiento,
                                                                    predicciones=False)
        print("SCORE: {}".format(porcentaje_aciertos))                                                                                                                        


