# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 2: Extraccion, descripcion y correspondencia de caracteristicas locales
# Tarea 1: Deteccion de puntos de interes con Harris corner detector.

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

from p2_tests import test_p2_tarea1

import numpy as np
from scipy import ndimage
from skimage import feature


def normalizar(img):
    """Esta funcion normaliza al rango [0,1]
       la imagen que se le pase por argumento
    Args:
        img (ndarray): imagen a normalizar
    Returns:
        ndarray: devuelve la imagen normalizada
    """
    # - creamos un array que asigne a true donde haya un valor
    #   mayor a 1 en la imagen
    boolArray = img > 1

    # - si existe algun true normalizamos ya que no se encuentra en 
    #   el rango 0-1
    if boolArray.any():
        img = img/255

    return img

def detectar_puntos_interes_harris(imagen, sigma = 1.0, k = 0.05, threshold_rel = 0.2):
    """
    # Esta funcion detecta puntos de interes en una imagen con el algoritmo de Harris.
    #
    # Argumentos de entrada:
    #   - imagen: numpy array con dimensiones [imagen_height, imagen_width].  
    #   - sigma: valor de tipo double o float que determina el factor de suavizado aplicado
    #   - k: valor de tipo double o float que determina la respuesta R de Harris
    #   - threshold_rel: valor de tipo double o float que define el umbral relativo aplicado sobre el valor maximo de R
    # Argumentos de salida
    #   - coords_esquinas: numpy array con dimensiones [num_puntos_interes, 2] con las coordenadas 
    #                      de los puntos de interes detectados en la imagen. Cada punto de interes 
    #                      se encuentra en el formato [fila, columna] de tipo int64
    #
    # NOTA: no modificar los valores por defecto de las variables de entrada sigma y k, 
    #       pues se utilizan para verificar el correcto funciomaniento de esta funcion
    """
    coords_esquinas = np.empty(shape=[0,0]) # iniciamos la variable de salida (numpy array)
    
    # convertimos la imagen a float en el rango [0,1]
    img_norm = normalizar(imagen.astype(np.float64))

    # sacamos las derivadas horizontales(x) y verticales(y)
    d_x = ndimage.sobel(img_norm, axis=0)
    d_y = ndimage.sobel(img_norm, axis=1)

    # obtenemos las tres imagenes multiplicando elemento
    # a elemento las derivadas
    mult_x_y = np.multiply(d_x, d_y)
    mult_x_x = np.multiply(d_x, d_x)
    mult_y_y = np.multiply(d_y, d_y)

    # aplicamos a las imagenes producto anteriores un filtrado gaussiano
    filtered_x_y = ndimage.gaussian_filter(mult_x_y, sigma, mode='constant')
    filtered_x_x = ndimage.gaussian_filter(mult_x_x, sigma, mode='constant')
    filtered_y_y = ndimage.gaussian_filter(mult_y_y, sigma, mode='constant')

    # inicializamos las matrices m y r
    m_xy = np.empty(shape=[2,2])
    r_xy = np.empty(shape=[img_norm.shape[0],img_norm.shape[1]])

    # calculamos al matriz m de cada pixel de la imagen a raiz de las derivadas parciales 
    for i in range(0, img_norm.shape[0]):
        for j in range(0, img_norm.shape[1]):
            m_xy[0][0] = filtered_x_x[i][j]
            m_xy[0][1] = filtered_x_y[i][j]
            m_xy[1][0] = filtered_x_y[i][j]
            m_xy[1][1] = filtered_y_y[i][j]
            # calculamos el determinante de la matriz y la traza para calcular la matriz r 
            det_mxy = np.linalg.det(m_xy)
            trace = np.trace(m_xy)
            r_xy[i][j] = det_mxy - (k * (trace**2))
           
    # detectamos las esquinas
    coords_esquinas = feature.corner_peaks(r_xy, min_distance=5, threshold_rel=threshold_rel)

    return coords_esquinas

if __name__ == "__main__":    
    print("Practica 2 - Tarea 1 - Test autoevaluación\n")                
    
    print("Tests completados = " + str(test_p2_tarea1(disptime=-1,stop_at_error=False,debug=False))) #analizar todos los casos sin pararse en errores
    #print("Tests completados = " + str(test_p2_tarea1(disptime=1,stop_at_error=False,debug=False))) #analizar y visualizar todos los casos sin pararse en errores
    #print("Tests completados = " + str(test_p2_tarea1(disptime=-1,stop_at_error=True,debug=False))) #analizar todos los casos y pararse en errores 
    #print("Tests completados = " + str(test_p2_tarea1(disptime=-1,stop_at_error=True,debug=True))) #analizar todos los casos, pararse en errores y mostrar informacion