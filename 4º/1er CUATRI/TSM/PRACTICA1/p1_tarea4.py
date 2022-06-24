# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 1: Fusion de imagenes mediante piramides
# Tarea 4: fusion de imagenes

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

import numpy as np
import math
import cv2
import matplotlib.pyplot as plt

from p1_tests import test_p1_tarea4
from p1_utils import visualizar_fusion
from p1_tarea2 import gaus_piramide, lapl_piramide
from p1_tarea3 import fusionar_lapl_pyr, reconstruir_lapl_pyr
from p1_utils import *

def normalizar_imagen(img):
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
        return img/255
    else:
        print("Ya está normalizado")
        return img


def run_fusion(imgA, imgB, mask, niveles):
    """ 
    # Esta funcion implementa la fusion de dos imagenes calculando las 
    # pirámides Laplacianas de las imagenes de entrada y la pirámide
    # Gausiana de una mascara.
    #  
    # Argumentos de entrada:
    #   imgA: numpy array de tamaño [imagen_height, imagen_width].
    #   imgB: numpy array de tamaño [imagen_height, imagen_width].
    #   mask: numpy array de tamaño [imagen_height, imagen_width].
    #
    # Devuelve:
    #   Gpyr_imgA: lista de numpy arrays con variable tamaño con "niveles+1" elementos 
    #               correspodientes a la piramide Gaussiana de la imagen A
    #   Gpyr_imgB: lista de numpy arrays con variable tamaño con "niveles+1" elementos 
    #               correspodientes a la piramide Gaussiana de la imagen B
    #   Gpyr_mask: lista de numpy arrays con variable tamaño con "niveles+1" elementos 
    #               correspodientes a la piramide Gaussiana de la máscara
    #   Lpyr_imgA: lista de numpy arrays con variable tamaño con "niveles+1" elementos 
    #               correspodientes a la piramide Laplaciana de la imagen A
    #   Lpyr_imgB: lista de numpy arrays con variable tamaño con "niveles+1" elementos 
    #               correspodientes a la piramide Laplaciana de la imagen B
    #   Lpyr_fus: lista de numpy arrays con variable tamaño con "niveles+1" elementos 
    #               correspodientes a la piramide Laplaciana de la fusion imagen A & B
    #   Lpyr_fus_rec:  numpy array de tamaño [imagen_height, imagen_width] correspondiente
    #               a la reconstruccion de la pirámide Lpyr_fus
    """ 
    
    # iniciamos las variables de salida    
    Gpyr_imgA = []      # Pirámide Gaussiana imagen A
    Gpyr_imgB = []      # Pirámide Gaussiana imagen B
    Gpyr_mask = []      # Pirámide Gaussiana máscara    
    Lpyr_imgA = []      # Pirámide Laplaciana imagen A
    Lpyr_imgB = []      # Pirámide Laplaciana imagen B
    Lpyr_fus = []       # Pirámide Laplaciana fusionada
    Lpyr_fus_rec = []   # Imagen reconstruida de la pirámide Laplaciana fusionada

    # comprobacion de que las dos imagenes de entrada sean bidimensionales
    if imgA.ndim != 2 or imgB.ndim != 2:
        print("Imagenes no bidimensionales")
        return

    # convertimos las imagenes y la mascara a tipo float64
    float_imageA = imgA.astype(np.float64)
    float_imageB = imgB.astype(np.float64)
    float_mask = mask.astype(np.float64)

    # normalizamos imagenes y mascara en el rango [0, 1] 
    # esta funcion se encuentra mas arriba en el fichero
    imgA_norm = normalizar_imagen(float_imageA) 
    imgB_norm = normalizar_imagen(float_imageB) 
    mask_norm = normalizar_imagen(float_mask) 

    # piramides gaussianas de las imagenes A y B y la mascara
    Gpyr_imgA = gaus_piramide(imgA_norm, niveles)
    Gpyr_imgB = gaus_piramide(imgB_norm, niveles)
    Gpyr_mask = gaus_piramide(mask_norm, niveles)

    # piramides laplacianas de sus correspondientes piramides gaussianas
    Lpyr_imgA = lapl_piramide(Gpyr_imgA)
    Lpyr_imgB = lapl_piramide(Gpyr_imgB)

    # fusionamos las piramides laplacianas con la gaussiana de la mascara
    Lpyr_fus = fusionar_lapl_pyr(Lpyr_imgA, Lpyr_imgB, Gpyr_mask)

    # reconstruimos la piramide fusionada
    Lpyr_fus_rec = reconstruir_lapl_pyr(Lpyr_fus)

    # recortamos a 1 o 0 los valor que se encuentren fuera de ese rango
    Lpyr_fus_rec = np.where(Lpyr_fus_rec > 1, 1, Lpyr_fus_rec)
    Lpyr_fus_rec = np.where(Lpyr_fus_rec < 0, 0, Lpyr_fus_rec)

    return Gpyr_imgA, Gpyr_imgB, Gpyr_mask, Lpyr_imgA, Lpyr_imgB, Lpyr_fus, Lpyr_fus_rec
    
if __name__ == "__main__":    
    
    path_imagenes = "img/"
    print("Practica 1 - Tarea 4 - Test autoevaluación\n")    
    result,imgAgray,imgBgray,maskgray,\
        Gpyr_imgA, Gpyr_imgB, Gpyr_mask, Lpyr_imgA, Lpyr_imgB, Lpyr_fus, Lpyr_fus_rec \
            = test_p1_tarea4(path_img=path_imagenes,precision=2)
    print("Tests completado = " + str(result)) 

    if result==True:
        #visualizar piramides de la fusion (puede consultar el codigo en el fichero p1_utils.py)
        visualizar_fusion(imgAgray,imgBgray,maskgray,Gpyr_imgA, Gpyr_imgB, Gpyr_mask, Lpyr_imgA, Lpyr_imgB, Lpyr_fus, Lpyr_fus_rec)