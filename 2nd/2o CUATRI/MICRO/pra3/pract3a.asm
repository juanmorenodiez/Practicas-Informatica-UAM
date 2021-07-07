;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 			SBM 2016. Practica 3 - pract3a.asm	 			;
;   Pareja	9																		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_DATA SEGMENT WORD PUBLIC 'DATA' 		; Segmento de datos DATA publico

	CODDEC 		DB 0DH DUP (0)			; Array donde se guardara el codigo de barras en decimal
	IMPAR 		DB ?					; Buffer para realizar calculos intermedios
	RES 		DB ?					

_DATA ENDS


PRACT3A SEGMENT BYTE PUBLIC 'CODE'		; Definicion del segmento de codigo 

PUBLIC	_computeControlDigit, _decodeBarCode	; Hacemos visible y accesible las funciones a implementar desde C

ASSUME CS: PRACT3A, DS:_DATA			; Indicamos los registros por defecto CS Y DS para direccionar las variables contenidas en PRACT3A y _DATA

;__________________________________________________________________________________________________ 
;
; La funcion realizara el computo automatico del digito de control GRIN-13 de la codificacion GS1.
; Recibira un puntero a la cadena completa de caracteres ASCII del codigo de barras y retornara en 
; AX el valor decimal del digito de control.
;__________________________________________________________________________________________________
	
_computeControlDigit PROC FAR			; El prototipo en C es: unsigned char computeControlDigit(char* barCodeASCII);
	PUSH BP								; Salvaguardamos BP en la pila para poder modificarle sin modificar su valor
	MOV BP, SP							; Igualamos BP al contenido de SP
	PUSH BX CX DX SI DI ES				; Salvaguardamos BX CX DX SI DI ES en la pila para poder modificarlos sin modificar su valor
	LES BX, [BP + 6]					; BX = OFFSET barCodeASCII ES = SEG barCodeASCII. 

	MOV AX, 0DH							; Guardamos en AX 0DH, que es el numero de veces que se itera en el bucle ASCII
	MOV SI, 0							; Inicializamos SI a 0
	
	
	;PASAMOS DE CODIGO ASCII A NUMERO EN DECIMAL
	
	ASCII:								; TRANSFORMA A DECIMAL 
	CMP SI, AX							; Comprobamos si ya hemos llegado al ultimo numero del codigo de barras 
	JE CONTINUAR						; Si ya hemos transformado todos los digitos de codigo de barras a decimal, se salta a CONTINUAR
	MOV CL, ES:[BX][SI]					; Guardamos en CL el numero ASCII del digito
	SUB CL, 30H							; RESTAMOS al dato 48=30H (48 es el 0 en ASCII) CL
	MOV CODDEC[SI], CL					; Guardamos en el array CODDEC el numero decimal, CODDEC+SI = CL
	INC SI								; Incrementamos SI para seguir iterando
	JMP ASCII							; Saltamos a ASCII para seguir transformando los digitos de ASCII a decimal
	
	CONTINUAR:							
	MOV SI, 0							; Volvemos a poner SI a 0
	MOV CX, 000AH						; Guardamos en CX 00AH (para calcular el digito de control)
	MOV AL, CODDEC[SI]					; Guardamos en AL el digito mas significativo del codigo de barras, en decimal
	
	;CALCULAMOS EL DIGITO DE CONTROL
	
	CALCULO:							; SUMAMOS LOS NUMEROS IMPARES
	CMP SI, CX							; Comprobamos si ya hemos sumado el ultimo numero impar del codigo de barras 
	JE CONTINUAR2						; Si ya hemos sumado todos los numero impares del codigo de barras, saltamos a CONTINUAR2
	INC SI								; Incrementamos dos veces SI para saltar los numeros pares
	INC SI
	ADD AL, CODDEC[SI]					; Sumamos a AL el numero impar
	JMP CALCULO							; Saltamos a CALCULO (bucle suma numeros impares)
	
	CONTINUAR2:							
	MOV IMPAR, AL						; Guardamos la suma de los numeros impares en la variable IMPAR
	MOV CX, 0DH							; Guardamos en CX 0DH, que es el numero de veces que se itera en el bucle MULTIPLICAR
	MOV SI, 1							; Inicializamos SI a 1, primero numero par
	MOV DL, 3							; Guardamos en DL un 3 para hacer la multiplicacion 
	
	MULTIPLICAR:						; Multiplicamos los numeros pares por 3 y se lo sumamos a IMPAR, que almacena la suma de los numeros impares
	CMP SI, CX							; Comprobamos si ya hemos multiplicado y sumado a IMPAR el ultimo numero par del codigo de barras 
	JE CONTINUAR3						; Si ya hemos sumado todos los numeros pares*3 del codigo de barras, saltamos a CONTINUAR3
	MOV AL, CODDEC[SI]					; Guardamos en AL el digito par en decimal
	MUL DL								; Multiplicamos el digito por 3	AX = AL*DL
	ADD IMPAR, AL						; Sumamos a la variable IMPAR el resultado de la multiplicacion
	INC SI								; Incrementamos dos veces SI para saltar los numeros impares
	INC SI
	JMP MULTIPLICAR						; Saltamos a MULTIPLICAR (bucle suma pares*3 a IMPAR(buffer))
	
	;OBTENEMOS EL NUMERO DE LA DECENA SUPERIOR MAS CERCANA AL VALOR GUARDADO EN LA VARIABLE IMPAR
	
	CONTINUAR3:							
	MOV DL, 0AH							; Guardamos en DL 0AH para hacer la division
	MOV AL, IMPAR						; Guardamos en AL el valor del buffer IMPAR
	DIV DL								; Dividimos el valor de la variable IMPAR por 10(Dividendo=AX, Divisor=DL, Cociente=AL, Resto=AH) 
	SUB DL, AH							; Restamos a 10 el resto de la division para obtener el numero
	MOV AL, IMPAR						; Guardamos en AL el valor del buffer IMPAR
	ADD AL, DL							; Sumamos a AL el numero calculado anteriormente
	SUB AL, IMPAR						; Restamos (IMPAR+NUMERO)-IMPAR 
	MOV AH, 0H							; Convertimos el resultado en una palabra
	JMP FIN								
	
	FIN:
	POP BX CX DX SI DI ES				; Restaura el valor de los registros usados antes de salir
	POP BP								; Restaura el valor de BP antes de salir
	RET									; Termina la funcion computeControlDigit
	
_computeControlDigit ENDP

;__________________________________________________________________________________________________ 
;
; Leera los 13 caracteres de entrada del codigo de barras y obtendra cada campo almacenando en los
; parametros de entrada-salida correspondientes al codigo de pais, el codigo de empresa, el codigo 
; de pais, el codigo de empresa, el codigo de producto y digito de control.
;__________________________________________________________________________________________________
		
_decodeBarCode PROC FAR					; El prototipo en C es: void decodeBarCode(char* in_barCodeASCII, unsigned int* countryCode, unsigned int* companyCode, unsigned long* productCode, unsigned char* controlDigit));
	PUSH BP								; Salvaguardamos BP en la pila para poder modificarle sin modificar su valor
	MOV BP, SP							; Igualamos BP el contenido de SP
	PUSH AX BX CX DX SI DI ES			; Salvaguardamos AX BX CX DX SI DI ES en la pila para poder modificarlos sin modificar su valor
	LES BX, [BP + 6]					; BX = OFFSET in_barCodeASCII  ES = SEG in_barCodeASCII. Guarda el primer parametro de la funcion en BP+6 y despues este pasara a estar en ES:[BX] 
	
	MOV AX, 0DH							; Guardamos en AX 0DH, que es el numero de veces que se itera en el bucle ASCII
	MOV SI, 0							; Inicializamos SI a 0
	
	;PASAMOS DE CODIGO ASCII A NUMERO EN DECIMAL

	ASCII2:								; TRANSFORMA A DECIMAL
	CMP SI, AX							; Comprobamos si ya hemos llegado al ultimo numero del codigo de barras 
	JE COUNTRY_CONTINUAR				; Si ya hemos transformado todos los digitos de codigo de barras a decimal, se salta a CONTINUAR
	MOV CL, ES:[BX][SI]					; Guardamos en CL el numero ASCII del digito
	SUB CL, 30H							; RESTAMOS al dato 48=30H (48 es el 0 en ASCII) CL
	MOV CODDEC[SI], CL					; Guardamos en el array CODDEC el numero decimal, CODDEC+SI = CL
	INC SI								; Incrementamos SI para seguir iterando
	JMP ASCII2							; Saltamos a ASCII2 para seguir transformando los digitos de ASCII a decimal
	
	COUNTRY_CONTINUAR:					; OBTENEMOS LOS 3 DIGITOS DE countryCode 
	MOV SI, 0							; Volvemos a poner SI a 0
	MOV BX, 64H							; Guardamos en BX 64H para multiplicar por 100
	MOV AL, CODDEC[SI]					; Guardamos en AL el digito mas significativo del codigo de barras, en decimal
	CBW									; Guardamos en AH 00H, la extension de signo siempre va a ser 0 porque el numero mas alto que puede haber en AL es 9
	MUL BX								; Multiplicamos el digito por 100	AX = AL*BX   AX = DIGITO*100
	MOV CX, AX							; Guardamos el resultado de la multiplicacion en CX (centenas)(CX se usa de buffer)
	INC SI								; Incrementamos SI para leer el siguiente digito
	MOV AL, CODDEC[SI]					; Guardamos en AL el segundo digito de countryCode
	CBW									; Guardamos en AH 00H
	MOV BX, 0AH							; Guardamos en BX 0AH para multiplicar por 10 el digito
	MUL BX								; Multiplicamos el digito por 10	AX=AL*BX AX=DIGITO*10
	ADD CX, AX							; Sumamos a CX el resultado de la multiplicacion (decenas)
	INC SI								; Incrementamos SI para leer el siguiente digito
	MOV AL, CODDEC[SI]					; Guardamos en AL el digito menos significativo de countryCode
	CBW									; Guardamos en AH 00H
	ADD CX, AX							; Sumamos a CX las unidades
	LES BX, [BP + 10]					; Guardamos en ES:BX la direccion donde se debe guardar countryCode.   BX = OFFSET countryCode	ES = SEG countryCode
	MOV ES:[BX], CX						; Guardamos el resultado de countryCode en la direccion correspondiente
	
	COMPANY:							; OBTENEMOS LOS 4 DIGITOS DE companyCode 
	MOV SI, 0003H						; Ponemos SI a 3, ya que companyCode empieza en la posicion CODDEC[3]
	MOV BX, 3E8H						; Guardamos en BX 3E8H para multiplicar por 1000
	MOV AL, CODDEC[SI]					; Guardamos en AL el primer digito de companyCode
	MOV AH, 0H							; Guardamos en AH 00H
	MUL BX								; Multiplicamos el digito por 1000	DX AX=AX*BX DX AX=DIGITO*1000	
	MOV CX, AX							; Guardamos el resultado de la multiplicacion en CX (unidad de mil)(CX se usa de buffer)
	MOV BX, 64H							; Guardamos en BX 64H para multiplicar por 100
	INC SI								; Incrementamos SI para leer el siguiente digito
	MOV AL, CODDEC[SI]					; Guardamos en AL el segundo digito de companyCode
	MOV AH, 0H							; Guardamos en AH 00H
	MUL BX								; Multiplicamos el digito por 100	DX AX=AX*BX DX AX=DIGITO*100
	ADD CX, AX							; Sumamos a CX el resultado de la multiplicacion (centenas)
	INC SI								; Incrementamos SI para leer el siguiente digito
	MOV AL, CODDEC[SI]					; Guardamos en AL el tercer digito de companyCode
	MOV AH, 0H							; Guardamos en AH 00H
	MOV BX, 0AH							; Guardamos en BX 0AH para multiplicar por 10 el digito
	MUL BX								; Multiplicamos el digito por 10	DX AX=AX*BX DX AX=DIGITO*10
	ADD CX, AX							; Sumamos a CX el resultado de la multiplicacion (decenas)
	INC SI								; Incrementamos SI para leer el ultimo digito
	MOV AL, CODDEC[SI]					; Guardamos en AL el ultimo digito de companyCode
	CBW									; Guardamos en AH 00H
	ADD CX, AX							; Sumamos a CX las unidades
	LES BX,  [BP + 14]					; Guardamos en ES:BX la direccion donde se debe guardar companyCode. BX = OFFSET companyCode	ES = SEG companyCode
	MOV ES:[BX], CX						; Guardamos el resultado de companyCode en la direccion correspondiente
	
	PRODUCT:							; OBTENEMOS LOS 5 DIGITOS DE productCode 
	INC SI								; Incrementamos SI para leer el primer digito de productCode
	MOV DI, [BP+18]						; Guardamos en DI la direccion donde se debe guardar productCode. DI = OFFSET productCode
	MOV CX, 0H							; Limpiamos CX
	MOV AX, 0H							; Limpiamos AX
	MOV BX, 0AH							; Guardamos en BX un 10, que se irá multiplicando por 10 consecutivamente
	MOV DX, 0H
	MOV ES:[DI], CX						; Limpiamos los 4 bytes de productCode
	MOV ES:[DI+2], CX

	FOR_PRODUCT:						; Calculamos productCode
	MUL BX							    ; Multiplicamos DX AX = AX*BX
	ADD AL, CODDEC[SI]				    ; Sumamos a AX el resultado de la multiplicacion (buffer)
	INC SI								; Incrementamos SI para leer el suguiente digito de productCode
	INC CX								; Incrementamos CX indicando asi cual es ultimo digito que hemos leido
	CMP CX, 5							; Comparamos CX con 5 para comprobar si ya hemos leido todos los digitos de productCode
	JNE FOR_PRODUCT						; Mientras no hayamos leido los 5 digitos de productCode, volvemos al bucle FOR_PRODUCT

	MOV ES:[DI], AX						; Lo guardamos en 4 bytes porque es un long
	MOV ES:[DI+2], DX
	
	CONTROL:							; OBTENEMOS EL DIGITO DE controlDigit 
	LES BX, [BP + 22]					; Guardamos en ES:BX la direccion donde se debe guardar controlDigit. BX = OFFSET controlDigit	ES = SEG controlDigit
	MOV SI, 12							; Guardamos 12 en SI ya que vamos a leer el ultimo digito del codigo de barras
	MOV AL, CODDEC[SI]					; Guardamos el digito de control en AL (CODDEC[12])
	MOV ES:[BX], AL						; Guardamos el digito de control en ES:[BX]	
	POP AX BX CX DX SI DI ES			; Restaura el valor de los registros usados antes de salir 
	POP BP								; Restaura el valor de BP antes de salir
	RET									; Termina la funcion decodeBarCode

_decodeBarCode ENDP
	
; FIN DEL SEGMENTO DE CODIGO 
PRACT3A ENDS 
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION 
END  

