all:
	@echo "Los comandos disponibles para el Makefile de la Práctica 2 son los siguientes:"
	@echo "make compilar"
	@echo "make ayuda_retro"
	@echo "make probar_configuraciones"
	@echo "make ejecutar_problema_best_config"
	@echo "make ayuda_problema_real2"
	@echo "make ejecuta_problema_real2"
	@echo "make ayuda_problema_real6"
	@echo "make ejecuta_problema_real6"
	@echo "make ayuda_predicciones_problema_real2"
	@echo "make ejecuta_predicciones_problema_real2"
	@echo "¡IMPORTANTE!, para poder probar la práctica, la carpeta con los ficheros de entrada debe de estar a la altura del makefile y se debe llamar data"

compilar:
	@echo "Esta instrucción no realiza nada ya que se usa Python"

ayuda_retro:
	@echo "Para probar el algoritmo de retropropagación, realizar la siguiente instrucción"
	@echo python3 main.py --probar_configuraciones problema_real1.txt 0.1
	@echo "Siendo problema_real1.txt el nombre del fichero de donde sacará los datos y 0.1 la constante de aprendizaje"
	@echo "El resto de parámetros se encuentran definidos en listas para ejecutar el algoritmo de retropropagación con el fichero indicado y probar cual es la mejor configuración para dicho problema"

probar_configuraciones:
	@echo "Probando cuales son los mejores parámetros de la red..."
	python3 main.py --probar_configuraciones problema_real1.txt 0.1

ejecutar_problema_best_config:
	python3 main.py --ejecutar_problema_best_config problema_real1.txt 10 1000 0.1

ayuda_problema_real2:
	@echo "Para probar el algoritmo de retropropagación con el problema_real2 realizar la siguiente instrucción"
	@echo "python3 main.py --ejecuta_problema_real2 problema_real2.txt 10 1000 0.1"
	@echo "El primer argumento es el nombre del fichero, el segundo el numero de neuronas en la capa oculta, el tercero el número de épocas y el último la tasa de aprendizaje"
	@echo "En los parámetros, damos los valores que mejores resultados nos haya dado al probar las configuraciones"

ejecuta_problema_real2:
	python3 main.py --ejecuta_problema_real2 problema_real2.txt 10 1000 0.1

ayuda_problema_real6:
	@echo "Para probar el algoritmo de retropropagación con el problema_real6 realizar la siguiente instrucción"
	@echo "python3 main.py --ejecuta_problema_real6 problema_real6.txt 20 5000 0.1"
	@echo "El primer argumento es el nombre del fichero, el segundo el numero de neuronas en la capa oculta, el tercero el número de épocas y el último la tasa de aprendizaje"

ejecuta_problema_real6:
	python3 main.py --ejecuta_problema_real6 problema_real6.txt 20 5000 0.1

ayuda_predicciones_problema_real2:
	@echo "Para probar el algoritmo de retropropagación con el problema_real2 sin etiquetar realizar la siguiente instrucción"
	@echo "python3 main.py --predicciones_problema_real2 problema_real2.txt problema_real2_no_etiquetados.txt 10 1000 0.1"
	@echo "El primer argumento es el nombre del fichero de train, el segundo el nombre del fichero de test, el tercero el numero de neuronas en la capa oculta, el cuarto el número de épocas y el último la tasa de aprendizaje"
	@echo "El fichero ya viene incluido, para probarlo otra vez habrá que eliminar el fichero prediccion_problema_real2.txt localizado en la raíz de la práctica y una vez borrado, ya se podrá ejecutar"

ejecuta_predicciones_problema_real2:
	python3 main.py --predicciones_problema_real2 problema_real2.txt problema_real2_no_etiquetados.txt 10 1000 0.1


	










	
