from neurona import Neurona
from red_neuronal import RedNeuronal
from capa import Capa

def obtener_impulsos(filename):
    with open(filename, "r") as f:
        rows = f.read().split("\n")
    
    list_impulsos = [tuple(map(int, row.split(' '))) for row in rows]

    f.close()
    return list_impulsos    


def mp_frio_calor(nombre_fichero_impulsos):
    impulsos = obtener_impulsos("bd/" + nombre_fichero_impulsos)
    f = open("salida_frio_calor.txt", "w")
    f.write("x1  x2  z1  z2  y1  y2\n")

    # creamos red neuronal
    red_neuronal = RedNeuronal()

    # creamos capas de la red
    input_layer = Capa()
    hidden_layer = Capa()
    output_layer = Capa()

    # creamos neuronas
    neurona_x1 = Neurona(umbral=0, tipo="Directa")
    neurona_x2 = Neurona(umbral=0, tipo="Directa")
    neurona_z1 = Neurona(umbral=2, tipo="McCulloch")
    neurona_z2 = Neurona(umbral=2, tipo="McCulloch")
    neurona_y1 = Neurona(umbral=2, tipo="McCulloch")
    neurona_y2 = Neurona(umbral=2, tipo="McCulloch")

    # añadimos neuronas a las capas
    input_layer.añadir(neurona_x1)
    input_layer.añadir(neurona_x2)
    hidden_layer.añadir(neurona_z1)
    hidden_layer.añadir(neurona_z2)
    output_layer.añadir(neurona_y1)
    output_layer.añadir(neurona_y2)

    # creamos conexiones entre neuronas
    neurona_x1.conectar(neurona_y1, float(2))
    neurona_x2.conectar(neurona_z1, float(-1))
    neurona_x2.conectar(neurona_z2, float(2))
    neurona_x2.conectar(neurona_y2, float(1))
    neurona_z1.conectar(neurona_y1, float(2))
    neurona_z2.conectar(neurona_z1, float(2))  
    neurona_z2.conectar(neurona_y2, float(1)) 

    # añadimos capas a la red neuronal
    red_neuronal.añadir(input_layer)
    red_neuronal.añadir(hidden_layer)
    red_neuronal.añadir(output_layer) 

    for impulso in impulsos:
        # inicializamos neuronas de entrada al
        # valor del impulso correspondiente
        neurona_x1.inicializar(impulso[0])
        neurona_x2.inicializar(impulso[1])
        # disparamos red neuronal
        red_neuronal.disparar()
        # inicializamos red neuronal
        red_neuronal.inicializar()
        # propagamos los valores de la red neuronal
        red_neuronal.propagar()
        f.write("{}   {}   {}   {}   {}   {}\n".format(
                        neurona_x1.valor_salida, neurona_x2.valor_salida,
                        neurona_z1.valor_salida, neurona_z2.valor_salida, 
                        neurona_y1.valor_salida, neurona_y2.valor_salida))

    print("Fichero {} obtenido correctamente!".format(f.name))
    f.close()
    return 