# -*- coding: utf-8 -*-
import pandas as pd
import numpy as np


def isNominal(str):
	if str.isdigit() is True:
		#is digit true
		return False
	try:
		float(str)
	except ValueError:
		#is nominal
		return True
	#is float
	return False

def storeDifferent(valList):
	lst = []
	finalList = []
	dic = {}
	i = 0
	for val in valList:
		if val not in lst: #si el valor no esta repetido lo guardamos
			lst.append(val)
	for val in sorted(lst):
		dic[val] = i #asignamos un numero a ese valor
		i += 1
	return dic


class Datos:

	# TODO: procesar el fichero para asignar correctamente las variables nominalAtributos, datos y diccionario
	def __init__(self, nombreFichero):
		self.nominalAtributos = []
		self.datos = np.array(())
		self.diccionario = {}
		numeroAtributos = 0
		onlyData = []

		with open(nombreFichero, 'r') as file:
			firstLine = file.readline()
			cols = firstLine.split(",")
			numeroAtributos = len(cols)

			for line in file:
				onlyData.append(line.replace('\n','').split(","))

			#guardamos el array bidimensional
			self.datos = np.array(onlyData)

			#guardamos en onlyData el array con todos los datos y ver si son nominales o numericos
			onlyData = np.array(onlyData).flatten()

			i = 0
			while i < len(self.datos[0]):
                #vemos si el primer elemento de cada columna es nominal o no
				try:
					if isNominal(self.datos[0][i]) is True:
						self.nominalAtributos.append(True)
					else:
						self.nominalAtributos.append(False)
					i += 1
				except ValueError:
					print("el dato ", self.datos[0][i], "es de tipo no permitido")

			df1 = pd.read_csv(nombreFichero)
			df2 = pd.read_csv(nombreFichero, usecols=df1.columns) #guardamos los nombres de las columnas

			#guardamos en diccionario los diccionarios de las diferentes columnas
			j = 0
			for el in df2:
				if self.nominalAtributos[j] == True: #si la columna es de nominales
					self.diccionario[el] = storeDifferent(df2[el])
				else:	#si la columna es de numeros, metemos un diccionario vacio
					self.diccionario[el] = {}
				j += 1
            #cambiar valores nominales por los del diccionario
			i = 0
			#para cada columna
			while i < len(self.datos[0]):
				if self.nominalAtributos[i]:
					j = 0
					#para cada fila
					while j < (len(self.datos)):
						val = self.getVal(self.datos[j][i], self.diccionario[df1.columns[i]])
						self.datos[j][i] = val
						j += 1
				i += 1

	def getVal(self, dato, valoresPosibles):
		#sacamos el valor correspondiente del deccionario de la columna
		val = valoresPosibles[dato]
		return val

	# TODO: implementar en la práctica 1
	def extraeDatos(self, idx):
		return self.datos[idx, :]

#if __name__ == '__main__':
#    x = Datos("german.data")
#    print("Nominal: \n")
#    print(x.nominalAtributos)
#    print("Datos: ")
#    print(x.datos)
#    print("\n")
#    print("Diccionario: ")
#    print(x.diccionario)