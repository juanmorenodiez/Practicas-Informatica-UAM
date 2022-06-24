# Tratamiento de Señales Visuales/Tratamiento de Señales Multimedia I @ EPS-UAM
# Practica 1: Fusion de imagenes mediante piramides
# Fichero con funciones y utilidades

import numpy as np
import cv2

def generar_kernel_suavizado(a):
    """ 
    # Esta funcion devuelve un kernel de tamaño 5x5 con parametro a
    #
    # Argumentos de entrada:
    #   a: valor de tipo double o float.  
    # Devuelve:
    #   numpy array de tamaño [5, 5] (output).
    """ 
    w_1d = np.array([0.25 - a/2.0, 0.25, a, 0.25, 0.25 - a/2.0])
    return np.outer(w_1d, w_1d)

def visualizar_gaus_piramide(gauss_pyr):
    """ 
    # Esta funcion visualiza una piramide Gaussiana 
    # y crea una sola imagen con todos los niveles
    # Cada nivel de la piramide se corresponde con un array 
    # bidimensionales, con lo cual esta funcion no procesa 
    # arrays de tres dimensiones (e.g. imagenes RGB)
    #
    # Argumentos de entrada:
    #   gauss_pyr: lista de numpy arrays creada con la funcion 'gauss_piramide'.     
    # Devuelve:
    #   output: imagen con la visualizacion de la piramide (tipo uint8)
    """     
    height = gauss_pyr[0].shape[0]
    width = gauss_pyr[0].shape[1]

    output = np.zeros((height*len(gauss_pyr), width), dtype = float)

    for idx, layer in enumerate(gauss_pyr):
        if layer.max() <= 1:
            layer = layer.copy() * 255

        output[(idx*height):((idx+1)*height),:] = cv2.resize(layer, (width, height), interpolation=cv2.INTER_AREA)

    return output.astype(np.uint8)

def visualizar_lapl_piramide(lapl_pyr):    
    """ 
    # Esta funcion visualiza una piramide Laplaciana 
    # y crea una sola imagen con todos los niveles
    # Cada nivel de la piramide se corresponde con un array 
    # bidimensionales, con lo cual esta funcion no procesa 
    # arrays de tres dimensiones (e.g. imagenes RGB)
    #
    # Argumentos de entrada:
    #   lapl_pyr: lista de numpy arrays creada con la funcion 'lapl_piramide'.     
    # Devuelve:
    #   output: imagen con la visualizacion de la piramide (tipo uint8)
    """ 
    height = lapl_pyr[0].shape[0]
    width = lapl_pyr[0].shape[1]

    output = np.zeros((height*len(lapl_pyr), width), dtype = np.uint8)

    for idx, layer in enumerate(lapl_pyr[:-1]):
        patch = cv2.resize(layer, (width, height), interpolation=cv2.INTER_AREA).astype(float)
        
        # escalar el patch al rango [0,255]
        patch = 128 + 127*patch/(np.abs(patch).max())

        output[(idx*height):((idx+1)*height),:] = patch.astype(np.uint8)

    #incluimos el ultimo nivel ultimo nivel
    patch = cv2.resize(lapl_pyr[-1], (width, height), interpolation=cv2.INTER_AREA)
    output[((len(lapl_pyr)-1)*height):(len(lapl_pyr)*height),:] = 255*patch

    return output

def visualizar_fusion(imgAgray,imgBgray,maskgray,Gpyr_imgA, Gpyr_imgB, Gpyr_mask, Lpyr_imgA, Lpyr_imgB, Lpyr_fus, Lpyr_fus_rec):
    """ 
    # Esta funcion visualiza todas las piramides involucradas en la fusion de imagenes mediante piramides Laplacianas    
    """ 
    import matplotlib.pyplot as plt

    niveles = len(Gpyr_imgA)
    # mostrar imágenes resultado
    fig, ax = plt.subplots( nrows = 2, ncols = 2, figsize = (8, 5), sharex = True , sharey = True )
    plt.gray()
    
    ax[0,0].imshow (imgAgray)
    ax[0,0].axis('off')
    ax[0,0].set_title ('Imagen 1')

    ax[0,1].imshow ( imgBgray )
    ax[0,1].axis ('off')
    ax[0,1].set_title ('Imagen 2')

    ax[1,0].imshow (maskgray)
    ax[1,0].axis('off')
    ax[1,0].set_title ('Máscara')

    ax[1,1].imshow ( Lpyr_fus_rec )
    ax[1,1].axis ('off')
    ax[1,1].set_title ('Fusión con piramides (' + str(niveles) + ' niveles)')

    fig.tight_layout()
    plt.show ( block = False )

    # mostrar piramides Gaussianas involucradas
    Gpyr_imgA_stacked = visualizar_gaus_piramide(Gpyr_imgA)
    Gpyr_imgB_stacked = visualizar_gaus_piramide(Gpyr_imgB)
    Gpyr_mask_stacked = visualizar_gaus_piramide(Gpyr_mask)

    #plt.figure(20)    
    #plt.imshow(Gpyr_imgA_stacked,cmap='gray')
    #plt.title('Piramide Gaussiana imagen A')

    plt.figure(2)
    plt.subplot(1, 3, 1)    
    plt.imshow(Gpyr_imgA_stacked,cmap='gray')
    plt.title('Pir Gaussiana A')
    plt.subplot(1, 3, 2)    
    plt.imshow(Gpyr_imgB_stacked)
    plt.title('Pir Gaussiana B')
    plt.subplot(1, 3, 3)    
    plt.imshow(Gpyr_mask_stacked)
    plt.title('Pir Gaussiana mask')        

    # mostrar piramides Laplacianas involucradas
    Lpyr_imgA_stacked = visualizar_lapl_piramide(Lpyr_imgA)
    Lpyr_imgB_stacked = visualizar_lapl_piramide(Lpyr_imgB)
    Lpyr_fus_stacked = visualizar_lapl_piramide(Lpyr_fus)

    #plt.figure(30)    
    #plt.imshow(Lpyr_imgA_stacked,cmap='gray')
    #plt.title('Piramide Laplaciana imagen A')

    plt.figure(3)
    plt.subplot(1, 3, 1)    
    plt.imshow(Lpyr_imgA_stacked,cmap='gray')
    plt.title('Pir Laplaciana A')
    plt.subplot(1, 3, 2)    
    plt.imshow(Lpyr_imgB_stacked)
    plt.title('Pir Laplaciana B')
    plt.subplot(1, 3, 3)    
    plt.imshow(Lpyr_fus_stacked)
    plt.title('Pir Laplaciana fusion')    
    plt.show()