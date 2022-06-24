from abc import ABCMeta,abstractmethod
import numpy as np
import pandas as pd
import EstrategiaParticionado
import Datos
from collections import Counter
from scipy.stats import norm
from scipy.spatial import distance
import math
from sklearn.metrics.pairwise import euclidean_distances, manhattan_distances


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
					valor = float(dato[atr])
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

class ClasificadorVecinosProximos(Clasificador):
	medias = []
	desviaciones = []
	normalized_data = np.zeros(0)
	K = 1
	distancia = "Euclidea"
	normalizado = True

	def __init__(self, K, distancia, normalizado):
		self.K = K
		self.distancia = distancia
		self.normalizado = normalizado

	def calcularMediasDesv(self,datos,nominalAtributos):
		for index, val in enumerate(nominalAtributos):
			if val is False:
				self.medias.append(np.mean(datos[:, index].astype(float)))
				self.desviaciones.append(np.std(datos[:, index].astype(float)))


	def normalizarDatos(self,datos,nominalAtributos):
		self.normalized_data = np.zeros(datos.shape)
		for index, val in enumerate(nominalAtributos[:-1]):
			if val is False:
				self.normalized_data[:,index] = (datos[:,index].astype(float) - self.medias[index])/(self.desviaciones[index] + 0.0)
			else:
				self.normalized_data[:,index] = datos[:, index].astype(float)
		self.normalized_data[:,-1] = datos[:, -1].astype(float)

	def distanciaEuclidea(self, val1, val2):
		resta = val2 - val1
		cuadrado = resta * resta
		return math.sqrt(cuadrado)
    
	def distanciaMahalanobis(self, array1, array2):
		array2np = np.array(array2)
		print(array2np)
		i,j= array1.shape
		xx = array1.reshape(i,j).T
		yy = array2np.reshape(i,j).T
		X = np.vstack([xx,yy])
		V = np.cov(X.T)
		VI = np.linalg.inv(V)
		return distance.mahalanobis(array1, array2np, iv)


	# TODO: implementar
	def entrenamiento(self,datostrain,atributosDiscretos,diccionario):
		if self.normalizado is True:
			self.calcularMediasDesv(datostrain, atributosDiscretos)
			self.normalizarDatos(datostrain, atributosDiscretos)
		else:
			self.normalized_data = datostrain

	def k_filas(self, distancias):
		aux = []

		for fila in distancias:
			aux.append(fila[0])
		sorted_indices = np.argsort(aux)

		kPrimeros = self.normalized_data[sorted_indices[0 : self.K], -1]
		return kPrimeros
	
	def calcularMediasDesvGen(self,datos,nominalAtributos):
		medias = []
		desviaciones = []
		for index, val in enumerate(nominalAtributos):
			if val is False:
				medias.append(np.mean(datos[:, index].astype(float)))
				desviaciones.append(np.std(datos[:, index].astype(float)))
		return medias, desviaciones
	
	def normalizarDatosGen(self, datos, nominalAtributos):
		norm = np.zeros(datos.shape)
		medias, desviaciones = self.calcularMediasDesvGen(datos,nominalAtributos)
		for index, val in enumerate(nominalAtributos[:-1]):
			if val is False:
				norm[:,index] = (datos[:,index].astype(float) - medias[index])/(desviaciones[index] + 0.0)
			else:
				norm[:,index] = datos[:, index].astype(float)
		norm[:,-1] = datos[:, -1].astype(float)
		return norm


	# TODO: implementar
	def clasifica(self,datostest,atributosDiscretos,diccionario):
		clases  = []
		if self.normalizado is True:
			datostestnorm = self.normalizarDatosGen(datostest, atributosDiscretos)
		else:
			datostestnorm = datostest
			
		for filaTest in datostestnorm:
			if self.distancia == "Euclidea":
				distancias = euclidean_distances(self.normalized_data[:, :-1], [filaTest[:-1]]).tolist()
			elif self.distancia == "Manhattan":
				distancias = manhattan_distances(self.normalized_data[:, :-1], [filaTest[:-1]]).tolist()
			elif self.distancia == "Mahalanobis":
				#V = np.cov(np.array([self.normalized_data[:, :-1], [filaTest[:-1]]]))
				#IV = np.linalg.inv(V)
				#distancias = distance.mahalanobis(self.normalized_data[:, :-1], [filaTest[:-1]], IV)
				distancias = self.distanciaMahalanobis(self.normalized_data[:, :-1], [filaTest[:-1]]).tolist()
			else:
				print("Distancia no conocida")
			kFilas = self.k_filas(distancias)
			clases.append(np.bincount(kFilas.tolist()).argmax())
		return clases

class ClasificadorRegresionLogistica(Clasificador):
	def __init__(self, kAprend = 1, nPasos = 50, w = None):
		self.kAprend = kAprend
		self.nPasos = nPasos
		self.w = w
		
	def sigmoidal(self, sample):
		ejemplo = np.insert(sample.astype(float), 0, 1.0, axis=0)
		prodEscalar = np.dot(ejemplo, self.w)
		sig = 1 / (1 + np.exp(- prodEscalar))
		return sig
		
	def entrenamiento(self, datostrain, atributosDiscretos, diccionario):
		numero_atributos = len(diccionario)

		self.w = np.random.uniform(low = -1.0, high = 1.0, size=numero_atributos)
		
		for epoca in range(self.nPasos):
			for fila in datostrain:
				# Calculamos el x real
				current = np.insert(fila[:-1].astype(float), 0, 1.0, axis=0)
				sigma = self.sigmoidal(fila[:-1])
				#nueva w
				self.w -= (self.kAprend * (sigma - fila[-1].astype(float)) * current)
		
	def clasifica(self, datostest, atributosDiscretos, diccionario):
		probabilidades = np.zeros(len(datostest))
		prediccion = np.zeros(len(datostest))
        # Para cada registro del dataset de clasificacion
		for indice_fila, fila in enumerate(datostest):
			probabilidades[indice_fila] = self.sigmoidal(fila[:-1])
        
		prediccion[probabilidades >= 0.5] = 1.0
		return prediccion


if __name__ == '__main__':
	errores = []
	dataset = Datos.Datos('ConjuntosDatosP2/pima-indians-diabetes.data')
	clasi = ClasificadorVecinosProximos(K = 11, distancia = "Mahalanobis", normalizado = True)
	clasi.entrenamiento(dataset.datos, dataset.nominalAtributos, dataset.diccionario)
	pred = clasi.clasifica(dataset.datos, dataset.nominalAtributos, dataset.diccionario)
	errores.append(clasi.error(dataset.datos, pred))
	print(errores)
	#dataset = Datos.Datos('tic-tac-toe.data')
	#clasi = ClasificadorRegresionLogistica(0.1, 100, None)
	#clasi.entrenamiento(dataset.datos, dataset.nominalAtributos, dataset.diccionario)
	#pred = clasi.clasifica(dataset.datos, dataset.nominalAtributos, dataset.diccionario)
	#ValidacionSimple = EstrategiaParticionado.ValidacionSimple(0.6, 3)
	#particiones = ValidacionSimple.creaParticiones(dataset.datos)
	#media_errores, std_errores = clasi.validacion(ValidacionSimple, dataset, clasi, seed=None)
	#print(media_errores)
	
	
