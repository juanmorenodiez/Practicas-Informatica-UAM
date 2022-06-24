from abc import ABCMeta,abstractmethod
import math
import random

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

	def creaIndices(self, numTrain, numTest, num, datos): #num se usa para saber donde empezar
		i = 0
		indicesTrain = []
		indicesTest = []
		numAux = num
		vueltaLista = 0
		vueltaLista2 = 0
		flagVuelta = 0
		while i < numTrain:
			if numAux < len(datos):
				indicesTrain.append(int(numAux))
				numAux += 1
			else:
				indicesTrain.append(int(vueltaLista))
				vueltaLista += 1
				flagVuelta = 1
			i += 1


		if flagVuelta == 1: #si para train se ha vuelto al inicio de la lista datos
			i = 0
			while vueltaLista < num:
				indicesTest.append(int(vueltaLista))
				vueltaLista += 1
		else:
			i = 0
			while numAux < len(datos): #continuar desde donde lo dejo indicesTrain
				indicesTest.append(int(numAux))
				numAux += 1

			while i < num: #damos la vuelta y seguimos guardando hasta llegar al punto de partida
				indicesTest.append(int(i))
				i += 1

		return (indicesTrain, indicesTest)

	def creaParticiones(self,datos,seed=None):
		i = 0
		datosTrain = int(self.proporcionTest * len(datos))
		datosTest = len(datos) - datosTrain
		particiones = []

		while i < self.numeroEjecuciones:
			random.seed(seed)
			num = random.random()
			num *= len(datos)
			train, test = self.creaIndices(datosTrain, datosTest, num, datos)
			particiones.append(Particion(train, test))
			i += 1
		return particiones


#####################################################################################################
class ValidacionCruzada(EstrategiaParticionado):
	def __init__(self, numeroParticiones):
		self.numeroParticiones = numeroParticiones

	def creaIndices(self, num, primerIndice, lenDatos):
		i = 0
		train = []
		test = []
		ultimoIndice = num + primerIndice
		for index in range(primerIndice, ultimoIndice):
			test.append(int(index))

		if primerIndice != 0:
			for index in range(0, primerIndice):
				train.append(int(index))

		if ultimoIndice != lenDatos:
			for index in range(ultimoIndice, lenDatos):
				train.append(int(index))

		return test, train


  	# Crea particiones segun el metodo de validacion cruzada.
  	# El conjunto de entrenamiento se crea con las nfolds-1 particiones y el de test con la particion restante
  	# Esta funcion devuelve una lista de particiones (clase Particion)
  	# TODO: implementar
	def creaParticiones(self,datos,seed=None):
		particiones = []
		indicesTrain = []
		indicesTest = []
		primerIndice = 0
		i = 0
		lenDatos = len(datos)

		num = math.floor(lenDatos / self.numeroParticiones)
		
		while i < self.numeroParticiones:
			if i == self.numeroParticiones - 1:
				num = math.ceil(lenDatos / self.numeroParticiones)

			indicesTest, indicesTrain = self.creaIndices(num, primerIndice, len(datos))
			p = Particion(indicesTrain, indicesTest)
			particiones.append(p)
			primerIndice += num
			i += 1

		return particiones


#if __name__ == '__main__':
	#a = ValidacionSimple(0.3, 1)
	#a.creaParticiones([11,23,45,67,45,67,89])
	#b = ValidacionCruzada(4)
	#b.creaParticiones([0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18])