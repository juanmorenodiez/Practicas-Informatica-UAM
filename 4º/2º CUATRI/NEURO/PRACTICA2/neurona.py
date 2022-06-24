from conexion import Conexion
from enum import Enum
import numpy as np

class Tipo(Enum):
    DIRECTA = "Directa"
    SESGO = "Sesgo"
    MCCULLOCH = "McCulloch"
    PERCEPTRON = "Perceptron"
    ADALINE = "Adaline"
    PERCEPTRON_SIGMOIDE = "PerceptronSigmoide"

class Neurona:
    def __init__(self,umbral, tipo: Tipo):
        self.umbral = umbral
        self.tipo = tipo
        self.valor_entrada = 0.0
        self.valor_salida = 0.0
        self.conexiones = []

    def liberar(self):
        pass

    def inicializar(self, x):
        self.valor_entrada = x

    def conectar(self, neurona, peso):
        conn = Conexion(peso, neurona)
        self.conexiones.append(conn)

    def disparar(self):
        if self.tipo == Tipo.DIRECTA.value: 
            self.valor_salida = self.valor_entrada
        elif self.tipo == Tipo.SESGO.value:
            self.valor_salida = 1.0
        elif self.tipo == Tipo.MCCULLOCH.value:
            self.valor_salida = 1 if self.valor_entrada >= self.umbral else 0
        elif self.tipo == Tipo.PERCEPTRON.value:
            if self.valor_entrada > self.umbral:
                self.valor_salida = 1.0
            elif self.valor_entrada <= self.umbral and self.valor_entrada >= -self.umbral:
                self.valor_salida = 0.0
            else:
                self.valor_salida = -1.0  
        elif self.tipo == Tipo.ADALINE.value:
            self.valor_salida = 1 if self.valor_entrada >= 0 else -1 
        elif self.tipo == Tipo.PERCEPTRON_SIGMOIDE.value: 
            self.valor_salida = (2 / (1 + np.exp(-self.valor_entrada))) - 1

        for conexion in self.conexiones:
            conexion.propagar(self.valor_salida)  

    def propagar(self):
        for conexion in self.conexiones:
            conexion.neurona.valor_entrada += conexion.valor * conexion.peso
        
