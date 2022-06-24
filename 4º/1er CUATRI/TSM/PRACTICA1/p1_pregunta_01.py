# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 1: Fusion de imagenes mediante piramides
# Memoria: codigo de la pregunta 1.1

# AUTOR1: PASCUAL FRANCES, JAIME
# AUTOR2: MORENO DIEZ, JUAN
# PAREJA/TURNO: 01/1

import os
from skimage import io
import numpy as np
import  matplotlib.pyplot  as plt
from p1_tarea2 import gaus_piramide, lapl_piramide
from p1_tarea3 import fusionar_lapl_pyr, reconstruir_lapl_pyr
from p1_tarea4 import normalizar_imagen
from p1_utils import *

def run_fusion_color(imgA, imgB, mask, niveles):
    """Genera la fusion de dos imagenes con una mascara
       y devuelve la fusion en una imagen a color.
    

    Args:
        imgA (ndarray): primera imagen de entrada
        imgB (ndarray): segunda imagen de entrada
        mask (ndarray): mascara a aplicar
        niveles (int): numero de niveles

    Returns:
        ndarray: imagen fusionada a color
    """

    # convertimos a float 64 las imagenes
    float_imageA = imgA.astype(np.float64)
    float_imageB = imgB.astype(np.float64)
    float_mask = mask.astype(np.float64)

    # normalizado de imagenes y mascara
    imgA_norm = normalizar_imagen(float_imageA)
    imgB_norm = normalizar_imagen(float_imageB)
    mask_norm = normalizar_imagen(float_mask)

    # extramos los canales de color de la imagen A
    imgA_red = imgA_norm[:,:,0]
    imgA_green = imgA_norm[:,:,1]
    imgA_blue = imgA_norm[:,:,2]

    # extramos los canales de color de la imagen B
    imgB_red = imgB_norm[:,:,0]
    imgB_green = imgB_norm[:,:,1]
    imgB_blue = imgB_norm[:,:,2]

    # extramos los canales de color de la mascara
    mask_red = mask_norm[:,:,0]
    mask_green = mask_norm[:,:,1]
    mask_blue = mask_norm[:,:,2]

    # sacamos las piramides gaussianas de 
    # los canales de cada imagen y de la mascara
    Gpyr_imgA_red = gaus_piramide(imgA_red, niveles)
    Gpyr_imgA_green = gaus_piramide(imgA_green, niveles)
    Gpyr_imgA_blue = gaus_piramide(imgA_blue, niveles)

    Gpyr_imgB_red = gaus_piramide(imgB_red, niveles)
    Gpyr_imgB_green = gaus_piramide(imgB_green, niveles)
    Gpyr_imgB_blue = gaus_piramide(imgB_blue, niveles)

    Gpyr_mask_red = gaus_piramide(mask_red, niveles)
    Gpyr_mask_green = gaus_piramide(mask_green, niveles)
    Gpyr_mask_blue = gaus_piramide(mask_blue, niveles)

    # laplaciana de todos los canales para la
    # gaussiana de las dos imagenes
    Lpyr_imgA_red = lapl_piramide(Gpyr_imgA_red)
    Lpyr_imgA_green = lapl_piramide(Gpyr_imgA_green)
    Lpyr_imgA_blue = lapl_piramide(Gpyr_imgA_blue)

    Lpyr_imgB_red = lapl_piramide(Gpyr_imgB_red)
    Lpyr_imgB_green = lapl_piramide(Gpyr_imgB_green)
    Lpyr_imgB_blue = lapl_piramide(Gpyr_imgB_blue)

    # fusionamos todos los canales correspondientes de cada canal de color
    Lpyr_fus_red = fusionar_lapl_pyr(Lpyr_imgA_red, Lpyr_imgB_red, Gpyr_mask_red)
    Lpyr_fus_green = fusionar_lapl_pyr(Lpyr_imgA_green, Lpyr_imgB_green, Gpyr_mask_green)
    Lpyr_fus_blue = fusionar_lapl_pyr(Lpyr_imgA_blue, Lpyr_imgB_blue, Gpyr_mask_blue)

    # reconstruimos las piramides de cada canal de color
    Lpyr_fus_rec_red = reconstruir_lapl_pyr(Lpyr_fus_red)
    Lpyr_fus_rec_green = reconstruir_lapl_pyr(Lpyr_fus_green)
    Lpyr_fus_rec_blue = reconstruir_lapl_pyr(Lpyr_fus_blue)

    # recombiamos todos los canales en una sola imagen
    recombinedRGBImage = np.stack((Lpyr_fus_rec_red, Lpyr_fus_rec_green, Lpyr_fus_rec_blue), axis=2)

    # recortamos a 1 o 0 los valor que se encuentren fuera de ese rango
    recombinedRGBImage = np.where(recombinedRGBImage > 1, 1, recombinedRGBImage)
    recombinedRGBImage = np.where(recombinedRGBImage < 0, 0, recombinedRGBImage)

    return recombinedRGBImage


if __name__ == "__main__": 
    img_path = os.path.abspath(os.getcwd()) + '/img'

    # leemos las imagenes y la mascara
    imgA = io.imread(img_path + '/orchid.jpg')
    imgB = io.imread(img_path + '/violet.jpg')
    mask1 = io.imread(img_path + '/orchid_mask.jpg')

    imgC = io.imread(img_path + '/apple1.jpg')
    imgD = io.imread(img_path + '/orange1.jpg')
    mask2 = io.imread(img_path + '/mask_apple1_orange1.jpg')

    imgE = io.imread(img_path + '/apple2.jpg')
    imgF = io.imread(img_path + '/orange2.jpg')
    mask3 = io.imread(img_path + '/mask_apple2_orange2.jpg')

    img1 = run_fusion_color(imgA, imgB, mask1, 4)
    img2 = run_fusion_color(imgC, imgD, mask2, 4)
    img3 = run_fusion_color(imgE, imgF, mask3, 10)

    # mostramos las 3 imagenes en una sola ventana
    f, axarr = plt.subplots(nrows = 1, ncols = 3)

    plt.sca(axarr[0])
    plt.imshow(img1)

    plt.sca(axarr[1]) 
    plt.imshow(img2)

    plt.sca(axarr[2]) 
    plt.imshow(img3)

    plt.show()