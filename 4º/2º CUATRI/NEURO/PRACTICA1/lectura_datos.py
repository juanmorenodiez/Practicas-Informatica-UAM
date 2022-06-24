import numpy as np


def datos_entrada_salida(nombre_fichero):
    file = open("bd/" + nombre_fichero, "r")

    first_line = file.readline().split(" ")
    # cogemos de la primera linea del fichero
    # los numeros que corresponden con la entrada y la salida
    numero_entradas = int(first_line[0])
    numero_salidas = int(first_line[1])

    filas_fichero = file.readlines()
    all_data_float = [list(map(float, fila.split())) for fila in filas_fichero]

    # arrays numpy con los indices correspondientes a las 
    # entradas y salidas que tengan el fichero de datos
    input_data = np.array([row[:numero_entradas] for row in all_data_float])
    output_data = np.array([row[-numero_salidas:] for row in all_data_float])

    return input_data, output_data


def leer1(fichero_de_datos, porcentaje_train):
    input_data, output_data = datos_entrada_salida(fichero_de_datos)
    
    # generamos una permutacion aleatoria de los indices de los datos de entrada
    indices = np.random.permutation(input_data.shape[0]) 
    indices_train = indices[:int(input_data.shape[0]*porcentaje_train)]
    indices_test = indices[int(input_data.shape[0]*porcentaje_train):] 

    x_train = input_data[indices_train,:]
    y_train = output_data[indices_train,:]  

    x_test = input_data[indices_test,:]
    y_test = output_data[indices_test,:]

    return x_train, y_train, x_test, y_test

def leer2(fichero_de_datos):
    input_data, output_data = datos_entrada_salida(fichero_de_datos)

    return input_data, output_data


def leer3(fichero_train, fichero_test):
    x_train, y_train = datos_entrada_salida(fichero_train)
    x_test, y_test = datos_entrada_salida(fichero_test)

    return x_train, y_train, x_test, y_test