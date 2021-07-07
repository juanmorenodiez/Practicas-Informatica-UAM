import numpy as np
import Datos
from sklearn.preprocessing import LabelEncoder
from sklearn.preprocessing import OneHotEncoder
from sklearn import preprocessing
from random import seed
import random
from collections import Counter
import itertools as it
import operator
import math
import EstrategiaParticionado
import matplotlib.pyplot as plt


class AlgoritmoGenetico:

	def __init__(self, probabilidad_cruce = 0.5, probabilidad_mutacion = 0.01, porcentaje_elitismo = 0.05, tamano_poblacion = 50, max_generaciones = 10, max_fitness = 0.8, max_reglas = 6, flagGrafica = False):
		self.mejorIndividuo = None
		self.probabilidad_cruce = probabilidad_cruce
		self.probabilidad_mutacion = probabilidad_mutacion
		self.porcentaje_elitismo = porcentaje_elitismo
		self.tamano_poblacion = tamano_poblacion
		self.max_generaciones = max_generaciones
		self.max_fitness = max_fitness
		self.max_reglas = max_reglas
		self.flagGrafica = flagGrafica

	def graficaIndividuosFitness(self, mejoresFitness):
		plt.title('Fitness del mejor individuo de la población')
		plt.xlabel('Generación del Mejor Individuo')
		plt.ylabel('Fitness')
		plt.plot(range(0, len(mejoresFitness)), mejoresFitness, 'go-')
		plt.show()

	def graficaFitnessMedio(self, fitnessMedio):
		plt.title('Fitness medio de la población')
		plt.xlabel('Generación del fitness medio')
		plt.ylabel('Fitness Medio')
		plt.plot(range(0, len(fitnessMedio)), fitnessMedio, 'bo-')
		plt.show()

	def validacion(self, particionado, dataset,seed = None):
		particiones = particionado.creaParticiones(dataset.datos)

		for i, particion in enumerate(particiones):
			poblacion = self.entrenamiento(dataset, particion.indicesTrain)
			proporcionAciertos = self.clasifica(dataset, poblacion, particion.indicesTest)
			break

		mean = np.mean(proporcionAciertos)
		return mean

	def entrenamiento(self, dataset, indicesTrain):
		generacion = 0
		fitness = []
		fitnessMedio = 0
		poblacion = []
		mejoresFitness = []
		fitsMedios = []
		poblacion = self.generaPoblacion(dataset)

		while fitnessMedio < self.max_fitness and generacion < self.max_generaciones:
			poblacionElite = []
			poblacionRestante = []
			poblacionCruzada = []
			fitnessRestante = []
			fitness = self.fitness(poblacion, dataset, indicesTrain)
			mejoresFitness.append(max(fitness))

			fitnessMedio = sum(fitness)/len(fitness)
			fitsMedios.append(fitnessMedio)
			numeroElites = math.floor(self.porcentaje_elitismo * len(poblacion))
			#Sacamos los indices de la elite
			elite = sorted(range(len(fitness)), key=lambda i: fitness[i])[-numeroElites:]
			#obtenemos los individuos de elite
			for num in elite:
				poblacionElite.append(poblacion[num])
			#Sacamos los indices restantes
			indicesRestante = []
			for i, num in enumerate(fitness):
				if i not in elite:
					indicesRestante.append(i)
			#obtenemos los individuos restantes
			for i in indicesRestante:
				fitnessRestante.append(fitness[i])
				poblacionRestante.append(poblacion[i])

			poblacionCruzada = self.cruzarPoblacion(poblacionRestante, fitnessRestante)
			poblacionMutada = self.mutarPoblacion(poblacionCruzada, fitnessRestante)
			poblacion = poblacionElite + poblacionMutada
			generacion += 1
		self.mejorIndividuo = poblacion[fitness.index(max(fitness))]

		if self.flagGrafica is True:
			self.graficaIndividuosFitness(mejoresFitness)
			self.graficaFitnessMedio(fitsMedios)

		return poblacion

	def clasifica(self, dataset, poblacion, indicesTest):
		proporcionesAciertos = []
		numeroAttrs = len(dataset.diccionario.values())
		for individuo in poblacion:
			fitnessIndividuo = 0
			numComparaciones = 0
			compsExitosas = 0
			for index in indicesTest:
				dato = dataset.matrizCodificada[index]
				clasesReglasActivadas = []
				for regla in individuo:
					#compara reglas del individuo con un dato
					value = self.compararReglaDato(regla, dato, numeroAttrs)
					if value is True:
						clasesReglasActivadas.append(regla[numeroAttrs - 1])
				if len(clasesReglasActivadas) != 0:
					maximo = self.claseMayoritaria(clasesReglasActivadas)
					#hay empate en el numero de clases
					if maximo == -1:
						fitnessIndividuo = 0
					else:
						#comparamos la clase mayoritaria con la clase del dato de Train
						numComparaciones += 1
						comparacion = self.comparaClaseDatoMaxima(dato[numeroAttrs - 1], maximo[0])
						if comparacion is True:
							compsExitosas += 1
			if numComparaciones == 0:
				fitnessIndividuo = 0
			else:
				fitnessIndividuo = compsExitosas / numComparaciones
			proporcionesAciertos.append(fitnessIndividuo)
		return proporcionesAciertos

	def error(self,datos,pred):
		# Aqui se compara la prediccion (pred) con las clases reales y se calcula el error
		predAux = np.array(pred)
		clases = datos[:,-1]
		return 1 - np.sum(np.equal(predAux.astype(int), clases.astype(int)))/len(pred)

	def generaBin(self, longitud, clase):
		bin = []
		bit1 = False

		#si hay que generar la clase
		if clase is True:
			for i in range(0, longitud):
				#si ya tenemos un 1, los demasa a 0
				if bit1 is True:
					value = 0
				#si no tenemos ningun 1, generamos aleatorio
				else:
					value = random.randint(0, 1)
					if value == 1:
						bit1 = True

				#si llegamos al ultimo bit y todo son 0s
				if (i == (longitud - 1)) and (bit1 is False):
					value = 1

				bin.append(value)
			return bin

		#si hay que generar un atributo normal
		for i in range(0, longitud):
			value = random.randint(0, 1)
			bin.append(value)
		return bin

	def generaPoblacion(self, dataset):
		#generar poblacion
		poblacion = []
		indicesGuardados = False
		for i in range(0, self.tamano_poblacion):
		#para cada individuo
			#para cada regla
			individuo = []
			numReglas = random.randint(1, self.max_reglas)
			for j in range(0, numReglas):
				regla = []
				#para cada atributo
				cont = 0
				for value in dataset.diccionarioCodificado.values():
					if cont == (len(dataset.diccionarioCodificado.values()) - 1):
						regla.append(self.generaBin(len(value), True))
					else:
						regla.append(self.generaBin(len(value), False)) # guardar en regla el codigo binario de ese atributo
					cont += 1
				reglanp = np.array(regla, dtype=object)
				reglanp.flatten()
				individuo.append(regla)
			poblacion.append(individuo)
		return poblacion

	def fitness(self, poblacion, dataset, indicesTrain):
		#individuo comparar dataset.train[0].codfificado
		#reglas activadas miramos sus clses y cojemos la mayoritaria
		#clasifica.train comparado con clase mayoritaria
		fitnessPoblacion = []
		numeroAttrs = len(dataset.diccionario.values())
		for individuo in poblacion:
			fitnessIndividuo = 0
			numComparaciones = 0
			compsExitosas = 0

			for index in indicesTrain:
				dato = dataset.matrizCodificada[index]
				#comparacion del individuo con todos los datos
				clasesReglasActivadas = []
				for regla in individuo:
					#compara reglas del individuo con un dato
					value = self.compararReglaDato(regla, dato, numeroAttrs)
					if value is True:
						clasesReglasActivadas.append(regla[numeroAttrs - 1])
				if len(clasesReglasActivadas) != 0:
					maximo = self.claseMayoritaria(clasesReglasActivadas)
					#hay empate en el numero de clases
					if maximo == -1:
						fitnessIndividuo = 0
					else:
						#comparamos la clase mayoritaria con la clase del dato de Train
						numComparaciones += 1
						comparacion = self.comparaClaseDatoMaxima(dato[numeroAttrs - 1], maximo[0])
						if comparacion is True:
							compsExitosas += 1

			if numComparaciones == 0:
				fitnessIndividuo = 0
			else:
				fitnessIndividuo = compsExitosas / numComparaciones
			fitnessPoblacion.append(fitnessIndividuo)
		return fitnessPoblacion

	def comparaClaseDatoMaxima(self, claseDato, claseRegla):
		arrayBool = np.logical_and(claseRegla, claseDato)
		if not(True in arrayBool):
			return False
		return True

	def claseMayoritaria(self, clasesReglasActivadas):
		dic = {}
		for i in range(0, len(clasesReglasActivadas)):
			tupla = tuple(clasesReglasActivadas[i])
			if tupla in dic:
				dic[tupla] += 1
			else:
				dic[tupla] = 0

		#devuelve la clase mas repetida
		maximo = max(dic.items(), key=operator.itemgetter(1))

		#si hay empate de numero de clases, se devuelve -1
		if len(maximo) > 2:
			return -1

		return maximo

	def compararReglaDato(self, regla, dato, numAttr):
		#index contiene el indice de inicio y de fin de cada atributo en la regla
		for i in range(0, numAttr - 1):
			#si no se activa uno de los atributos
			arrayBool = np.logical_and(regla[i], dato[i])
			if not(True in arrayBool):
				return False
		return True

	def cruzarPoblacion(self, poblacion, fitness):
		poblacionCruzada = []
		for i in range(0, math.ceil(len(poblacion) * self.probabilidad_cruce)):
			padre1, indiceInnecesario = self.casinoRoulette007(fitness, poblacion, True)
			padre2, indiceInnecesario = self.casinoRoulette007(fitness, poblacion, True)
			padre1Cruzado, padre2Cruzado = self.cruzarPadres(padre1, padre2)
			poblacionCruzada.append(padre1Cruzado)
			poblacionCruzada.append(padre2Cruzado)

		return poblacionCruzada

	def cruzarPadres(self, padre1, padre2):
		posicionCruce = 0
		padre1Cruzado = []
		padre2Cruzado = []

		if len(padre1) < len(padre2):
			posicionCruce = random.randint(1, len(padre1))
		else:
			posicionCruce = random.randint(1, len(padre2))

		padre1Cruzado = padre1[0:posicionCruce] + padre2[posicionCruce:]
		padre2Cruzado = padre2[0:posicionCruce] + padre1[posicionCruce:]

		return padre1Cruzado, padre2Cruzado


	def casinoRoulette007(self, fitness, poblacion, flagOperando):
		totalFitness = sum(fitness)
		numAleat = random.uniform(0, totalFitness)
		suma2 = 0

		listFitnessInverso = []
		for num in fitness:
			if num == 0:
				num = 0.001
			listFitnessInverso.append(1/num)
		totalFitnessInverso = sum(listFitnessInverso)
		numAleat2 = random.uniform(0, totalFitnessInverso)

		for i, num in enumerate(fitness):
			#si queremos cruzar
			if flagOperando is True:
				if suma2 + num > numAleat:
					return poblacion[i], i
				suma2 += num

			#si queremos mutar
			else:
				if num == 0:
					num = 0.001 #si num es 0 hacemos posible la division
				if suma2 + (1/num) > numAleat2:
					return poblacion[i], i
				suma2 += (1/num)
		return "error"

	def mutarIndividuo(self, individuo):
		indiceRegla = random.randint(0, len(individuo) - 1)
		indiceAttr = random.randint(0, len(individuo[indiceRegla]) - 1)
		indiceBit = random.randint(0, len(individuo[indiceRegla][indiceAttr]) - 1)
		if individuo[indiceRegla][indiceAttr][indiceBit] == 1:
			individuo[indiceRegla][indiceAttr][indiceBit] = 0
		else:
			individuo[indiceRegla][indiceAttr][indiceBit] = 1

		return individuo

	def mutarPoblacion(self, poblacionCruzada, fitness):
		poblacionMutada = []
		for i in range(0, math.ceil(len(poblacionCruzada) * self.probabilidad_mutacion)):
			individuo, indiceIndividuo = self.casinoRoulette007(fitness, poblacionCruzada, False)
			individuoMutado= self.mutarIndividuo(individuo)
			poblacionCruzada[indiceIndividuo] = individuoMutado
		poblacionMutada = poblacionCruzada
		return poblacionMutada


if __name__ == '__main__':
	genetico = AlgoritmoGenetico(flagGrafica = True)
	dataset = Datos.Datos('titanic.data', esGenetico = True)
	validacionCruzada = EstrategiaParticionado.ValidacionSimple(0.6, 1)
	particiones = validacionCruzada.creaParticiones(dataset.datos)
	mean = genetico.validacion(validacionCruzada, dataset, seed=None)
	print("media:", mean)
