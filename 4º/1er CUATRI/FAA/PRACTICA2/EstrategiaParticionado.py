from abc import ABCMeta,abstractmethod
import math
import random
import Datos as Datos
import numpy as np

class Particion():

	# Esta clase mantiene la lista de �ndices de Train y Test para cada partici�n del conjunto de particiones
	def __init__(self, indicesTrain, indicesTest):
		self.indicesTrain = indicesTrain
		self.indicesTest = indicesTest

#####################################################################################################

class EstrategiaParticionado:

  # Clase abstracta
	__metaclass__ = ABCMeta

  # Atributos: deben rellenarse adecuadamente para cada estrategia concreta. Se pasan en el constructor
	@abstractmethod
	def __init__(self, particiones):
		self.particiones = particiones

	@abstractmethod
  # TODO: esta funcion deben ser implementadas en cada estrategia concreta
	def creaParticiones(self,datos,seed=None):
		pass


#####################################################################################################

class ValidacionSimple(EstrategiaParticionado):
	def __init__(self, proporcionTest, numeroEjecuciones):
		self.proporcionTest = proporcionTest
		self.numeroEjecuciones = numeroEjecuciones

	# Crea particiones segun el metodo tradicional de division de los datos segun el porcentaje deseado y el n�mero de ejecuciones deseado
	# Devuelve una lista de particiones (clase Particion)
	# TODO: implementar

	def creaIndices(self, datos, seed):
		random.seed(seed)
		filas = datos.shape[0]
		index = list(range(0, filas))
		random.shuffle(index)
		numTrain = int(math.ceil(filas * self.proporcionTest))
		indicesTrain = index[0: numTrain]
		indicesTest = index[numTrain + 1:]

		return (indicesTrain, indicesTest)

	def creaParticiones(self,datos,seed=None):
		i = 0
		particiones = []

		while i < self.numeroEjecuciones:
			train, test = self.creaIndices(datos, seed)
			particiones.append(Particion(train, test))
			i += 1
		return particiones


#####################################################################################################
class ValidacionCruzada(EstrategiaParticionado):
	def __init__(self, numeroParticiones):
		self.numeroParticiones = numeroParticiones

	def creaIndices(self, numDatos, seed):
		random.seed(seed)
		bloques = int(numDatos/self.numeroParticiones)
		indices = np.arange(numDatos)
		random.shuffle(indices)
		return indices, bloques


  	# Crea particiones segun el metodo de validacion cruzada.
  	# El conjunto de entrenamiento se crea con las nfolds-1 particiones y el de test con la particion restante
  	# Esta funcion devuelve una lista de particiones (clase Particion)
  	# TODO: implementar
	def creaParticiones(self,datos,seed=None):
		particiones = []
		indicesTrain = []
		indicesTest = []
		lenDatos = len(datos)
		
		i = 0
		while i < self.numeroParticiones:
			indices, bloques = self.creaIndices(lenDatos, seed)
			indicesTrain = np.delete(indices, range(i*bloques,(i+1)*bloques))
			indicesTest =  indices[i*bloques:(i+1)*bloques-1]
			p = Particion(indicesTrain, indicesTest)
			particiones.append(p)
			i += 1

		return particiones


#if __name__ == '__main__':
	#dataset = Datos.Datos('ConjuntosDatosP2/german.data')
	#validacionCruzada = ValidacionCruzada(4)
	#particiones = validacionCruzada.creaParticiones(dataset.datos)
	#for particion in particiones:
		#print("Indices Entrenamiento:", particion.indicesTrain)
		#print("\n")
		#print("Indices Prueba:", particion.indicesTest)
