from abc import ABCMeta,abstractmethod
import numpy as np
import pandas as pd
import EstrategiaParticionado
import Datos
from scipy.stats import norm


class Clasificador:

	# Clase abstracta
	__metaclass__ = ABCMeta
	errores = []

	# Metodos abstractos que se implementan en casa clasificador concreto
	@abstractmethod
	# TODO: esta funcion debe ser implementada en cada clasificador concreto
	# datosTrain: matriz numpy con los datos de entrenamiento
	# atributosDiscretos: array bool con la indicatriz de los atributos nominales
	# diccionario: array de diccionarios de la estructura Datos utilizados para la codificacion de variables discretas
	def entrenamiento(self,datosTrain,atributosDiscretos,diccionario):
		pass


	@abstractmethod
	# TODO: esta funcion debe ser implementada en cada clasificador concreto
	# devuelve un numpy array con las predicciones
	def clasifica(self,datosTest,atributosDiscretos,diccionario):
		pass


	# Obtiene el numero de aciertos y errores para calcular la tasa de fallo
	# TODO: implementar
	def error(self,datos,pred):
		# Aqui se compara la prediccion (pred) con las clases reales y se calcula el error
		predAux = np.array(pred)
		clases = datos[:,-1]
		return 1 - np.sum(np.equal(predAux.astype(int), clases.astype(int)))/len(pred)


	# Realiza una clasificacion utilizando una estrategia de particionado determinada
	# TODO: implementar esta funcion
	def validacion(self,particionado,dataset,clasificador,seed=None):
		# Creamos las particiones siguiendo la estrategia llamando a particionado.creaParticiones
		# - Para validacion cruzada: en el bucle hasta nv entrenamos el clasificador con la particion de train i
		# y obtenemos el error en la particion de test i
		# - Para validacion simple (hold-out): entrenamos el clasificador con la particion de train
		# y obtenemos el error en la particion test. Otra opci�n es repetir la validaci�n simple un n�mero especificado de veces, obteniendo en cada una un error. Finalmente se calcular�a la media.

        # Creamos las particiones
		particiones = particionado.creaParticiones(dataset.datos)
		errores = []

        # Calculamos los errores para cada particion
		for i, particion in enumerate(particiones):
			datosTrain = self.generaSet(dataset.datos, particion.indicesTrain)
			datosTest = self.generaSet(dataset.datos, particion.indicesTest)
			clasificador.entrenamiento(datosTrain, dataset.nominalAtributos, dataset.diccionario)
			pred = clasificador.clasifica(datosTest, dataset.nominalAtributos, dataset.diccionario)
			errores.append(self.error(datosTest, pred))

		mean = np.mean(errores)
		std = np.std(errores)

		return mean, std

	def generaSet(self, datos, indices):
		filasAux = []
		for indice in indices:
			filasAux.append(datos[indice])
		filas = np.array(filasAux)
		return filas

##############################################################################

class ClasificadorNaiveBayes(Clasificador):
	laplace = 0
	def __init__(self, laplace):
		self.laplace = laplace

	# TODO: implementar
	def entrenamiento(self,datostrain,atributosDiscretos,diccionario):
		tamano_train = len(datostrain[:, -1])
		num_atributos = len(diccionario.keys()) - 1
		lastcol = datostrain[:, -1]
		num_casos_clase = {}
		self.clases = set(lastcol)
		self.prioris = {}
		self.probabilidades = [None] * num_atributos
		self.factores = [None] * num_atributos
		self.parametros_normales = [{'media': 0, 'varianza': 0}] * num_atributos

		for clase in self.clases:
			casos_clase = (datostrain[:, -1] == clase)
			#num de datos en los que la clase coincida
			num_casos_clase[clase] = float(np.sum(casos_clase))
			#num datos de esa clase / num datos totales
			self.prioris[clase] = float(num_casos_clase[clase]) / float(tamano_train)

		#para cada atributo
		for indice_atributo in range(num_atributos):
			llaves = list(diccionario.keys())
			valores_atributo = diccionario[llaves[indice_atributo]].values()
			numero_valores_atributo = len(valores_atributo)

			self.probabilidades[indice_atributo] = {}
			self.factores[indice_atributo] = {}

			#si el atributo es continuo (porque su diccionario esta vacio)
			if numero_valores_atributo == 0:
				self.parametros_normales[indice_atributo]['media'] = np.mean(datostrain[:, indice_atributo].astype(np.float))
				self.parametros_normales[indice_atributo]['varianza'] = np.var(datostrain[:, indice_atributo].astype(np.float))

			for valor_atributo in valores_atributo:
				self.probabilidades[indice_atributo][valor_atributo] = {}
				self.factores[indice_atributo][valor_atributo] = self.getFactor(datostrain, indice_atributo, valor_atributo)

				 #si es discreto (esta comprobacion no haria falta hacerla)
				if atributosDiscretos[indice_atributo] is True:
					for clase in self.clases:
						#indices casos favorables son los datos en los que el valor del atributo esta y la clase es la deseada
						indices_favorables = self.getIndicesFavorables(datostrain, indice_atributo, valor_atributo, clase)
						numerador = indices_favorables + 1
						denominador = (num_casos_clase[clase] + 1 * numero_valores_atributo)
						probabilidad = float(numerador) / float(denominador)
						self.probabilidades[indice_atributo][valor_atributo][clase] = probabilidad

		return

	def getFactor(self, datostrain, indice_atributo, valor_atributo):
		numerador = 0
		factor = 0
		i = 0
		arraytrain = datostrain[:, indice_atributo]
		while i < len(arraytrain):
			if int(arraytrain[i]) == valor_atributo:
				numerador += 1
			i += 1
		factor = numerador / len(arraytrain)
		return factor

	def getIndicesFavorables(self, datostrain, indice_atributo, valor_atributo, clase):
		indices = 0
		i = 0
		arraytrain = datostrain[:, indice_atributo]
		last = datostrain[:, -1]
		while i < len(arraytrain):
			if int(arraytrain[i]) == valor_atributo and last[i] == clase:
				indices += 1
			i += 1
		return indices

	def probabilidadClase(self, dato, atributosDiscretos):
		probabilidades = {}
		for c in sorted(self.clases):
			probabilidades[c] = self.prioris[c]

		for c in self.clases:
			for atr, nominal in enumerate(atributosDiscretos[:-1]):
				#si discreto
				if nominal:
					valor = int(dato[atr])
					probabilidades[c] *= float(self.probabilidades[atr][valor][c])

				#si continuo
				else:
					media = self.parametros_normales[atr]['media']
					varianza = self.parametros_normales[atr]['varianza']
					if varianza != 0:
						probabilidades[c] *= float(norm.pdf(valor, media, varianza))
		#normalizar las probabilidade
		#probs = list(probabilidades.values())
		#probs /= np.sum(probs)
		return probabilidades

	def clasifica(self,datostest,atributosDiscretos,diccionario):
		indices = range(len(datostest))
		nb = []

		for dato in datostest[indices]:
			probabilidades = self.probabilidadClase(dato, atributosDiscretos)
			claseMayor = self.comparador(probabilidades)
			nb.append(claseMayor)
		return nb

	def comparador(self, diccionario):
		claves = list(diccionario.keys())
		valores = list(diccionario.values())
		maximo = max(valores)
		i = 0
		while i < len(claves):
			if diccionario[claves[i]] == maximo:
				break
			i +=1
		return claves[i]

#if __name__ == '__main__':
	#clasificador = ClasificadorNaiveBayes(0)
	#dataset = Datos.Datos('ConjuntoDatos/german.data')
	#ValidacionCruzada = EstrategiaParticionado.ValidacionCruzada(50)
	#particiones = ValidacionCruzada.creaParticiones(dataset.datos)
	#media_errores, std_errores = clasificador.validacion(ValidacionCruzada, dataset, clasificador, seed=None)
	#print(media_errores)
