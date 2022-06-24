import argparse
import lectura_datos
import retropropagacion
from sklearn.preprocessing import StandardScaler

def normalize_data(data, method='mean'):
    if method == 'mean':
        scaler = StandardScaler(with_mean=True)
    elif method == 'std':
        scaler = StandardScaler(with_std=True)

    return scaler.fit_transform(data)

if __name__ == '__main__':
    # instancia del parser de argumentos
    parser = argparse.ArgumentParser(description = "Práctica 1 NEURO")

    # se añaden los argumentos que se van a usar al parser
    parser.add_argument("--ejecuta_problema_real2", help="Ejecución del problema real 2", nargs = 4, type = str)
    parser.add_argument("--ejecuta_problema_real6", help="Ejecución del problema real 6", nargs = 4, type = str)
    parser.add_argument("--probar_configuraciones", help="Ejecucion de retropropagacion para todos los problemas con distintas configuraciones", nargs = 2, type = str)
    parser.add_argument("--predicciones_problema_real2", help="Ejecución para predecir los valores de la clase para el problema real 2 sin etiquetar", nargs = 5, type = str)
    parser.add_argument("--ejecutar_problema_best_config", help="Ejecución de cualquier problema con la mejor configuración", nargs = 4, type = str)

    # parseo de argumentos
    args = parser.parse_args()

    if args.ejecuta_problema_real2:
        x_train, y_train, x_test, y_test = lectura_datos.leer1(args.ejecuta_problema_real2[0], 0.7)
        score = retropropagacion.algoritmo_retropropagacion(x_train, y_train, x_test, y_test,
                                                            neuronas_oculta=int(args.ejecuta_problema_real2[1]),
                                                            num_epocas=int(args.ejecuta_problema_real2[2]),
                                                            constante_aprendizaje=float(args.ejecuta_problema_real2[3]),
                                                            graficas=True)
        print("Score para {} con mejor configuracion: {}".format(args.ejecuta_problema_real2[0], score))


    elif args.ejecuta_problema_real6:
        x_train, y_train, x_test, y_test = lectura_datos.leer1(args.ejecuta_problema_real6[0], 0.7)
        x_train_normalized = normalize_data(x_train)
        x_test_normalized = normalize_data(x_test)
        score = retropropagacion.algoritmo_retropropagacion(x_train_normalized, y_train, x_test_normalized, y_test,
                                                            neuronas_oculta=int(args.ejecuta_problema_real6[1]),
                                                            num_epocas=int(args.ejecuta_problema_real6[2]),
                                                            constante_aprendizaje=float(args.ejecuta_problema_real6[3]),
                                                            graficas=True)
        print("Score para {} con con mejor configuracion: {}".format(args.ejecuta_problema_real6[0], score))

    elif args.probar_configuraciones:
        x_train, y_train, x_test, y_test = lectura_datos.leer1(args.probar_configuraciones[0], 0.7)
        epocas = [200, 500, 1000]
        neuronas_oculta = [5, 10, 15, 20]

        for ejecucion_epoca in epocas:
            for neuronas in neuronas_oculta:
                score = retropropagacion.algoritmo_retropropagacion(x_train, y_train, x_test, y_test,
                                                            neuronas_oculta=neuronas,
                                                            num_epocas=ejecucion_epoca,
                                                            constante_aprendizaje=float(args.probar_configuraciones[1]),
                                                            graficas=True)
                print("Score para {}: {}".format(args.probar_configuraciones[0], score))

    elif args.predicciones_problema_real2:
        x_train, y_train, x_test, y_test = lectura_datos.leer3(args.predicciones_problema_real2[0], args.predicciones_problema_real2[1])
        score = retropropagacion.algoritmo_retropropagacion(x_train, y_train, x_test, y_test,
                                                            neuronas_oculta=int(args.predicciones_problema_real2[2]),
                                                            num_epocas=int(args.predicciones_problema_real2[3]),
                                                            constante_aprendizaje=float(args.predicciones_problema_real2[4]),
                                                            graficas=False,
                                                            predicciones=True)
        print("Fichero de predicciones obtenido correctamente!") 

    elif args.ejecutar_problema_best_config:
        x_train, y_train, x_test, y_test = lectura_datos.leer1(args.ejecutar_problema_best_config[0], 0.7)
        score = retropropagacion.algoritmo_retropropagacion(x_train, y_train, x_test, y_test,
                                                            neuronas_oculta=int(args.ejecutar_problema_best_config[1]),
                                                            num_epocas=int(args.ejecutar_problema_best_config[2]),
                                                            constante_aprendizaje=float(args.ejecutar_problema_best_config[3]),
                                                            graficas=True)
        print("Score para {} con mejor configuracion: {}".format(args.ejecutar_problema_best_config[0], score))


        