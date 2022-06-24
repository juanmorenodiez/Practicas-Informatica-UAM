import random
from neurona import Neurona


class Capa:
    def __init__(self):
        self.neuronas = []

    def liberar(self):
        pass

    def inicializar(self):
        for neurona in self.neuronas:
            neurona.inicializar(0)

    def añadir(self, neurona):
        self.neuronas.append(neurona) 

    def conectar_capa(self, capa, peso_min, peso_max):
        for neurona_origen in self.neuronas:
            for neurona_dest in capa.neuronas:
                random_float = random.uniform(peso_min, peso_max)
                neurona_origen.conectar(neurona_dest, random_float)

    def conectar_neurona(self, neurona, peso_min, peso_max):
        for neurona in self.neuronas:
            random_float = random.uniform(peso_min, peso_max)
            neurona.conectar(neurona, random_float)

    def disparar(self):
        for neurona in self.neuronas:
            neurona.disparar()

    def propagar(self):
        for neurona in self.neuronas:
            neurona.propagar()        

    