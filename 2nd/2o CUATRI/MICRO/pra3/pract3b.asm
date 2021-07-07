;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; 			SBM 2016. Practica 3 - pract3b.asm	 			;
;   Pareja	9																		;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

_DATA SEGMENT WORD PUBLIC 'DATA' 		; Segmento de datos DATA público

	RESULTADO   DB 5 DUP (?), '$' 		; Variable donde guardamos la trasformacion de decimal a ASCII(buffer)
	DIEZ		DW 000AH				; Variable donde cargamos el valor 10

_DATA ENDS


PRACT3B SEGMENT BYTE PUBLIC 'CODE'		; Definicion del segmento de codigo 

PUBLIC	_createBarCode					; Hacemos visible y accesible la funcion a implementar desde C

ASSUME CS: PRACT3B, DS:_DATA			; Indicamos los registros por defecto CS Y DS para direccionar las variables contenidas en PRACT3B y _DATA
	
;__________________________________________________________________________________________________ 
;
; La funcion debera generar los 13 caracteres ASCII del codigo de barras, leyendo las variables de 
; entrada que se corresponden con cada uno de los campos que lo forman.
;__________________________________________________________________________________________________

_createBarCode PROC FAR					; El prototipo en C es: void createBarCode(unsigned int countryCode, unsigned int companyCode, long int productCode, unsigned char controlDigit, char* out_barCodeASCII);
	PUSH BP								; Salvaguardamos BP en la pila para poder modificarle sin modificar su valor
	MOV BP, SP							; Igualamos BP al contenido de SP
	PUSH AX BX CX DX SI DI ES 			; Salvaguardamos AX BX CX DX SI DI ES en la pila para poder modificarlos sin modificar su valor
	LES DI, [BP + 16]					; DI = OFFSET out_barCodeASCII	ES = SEG out_barCodeASCII. 
	
	COUNTRY:							; OBTENEMOS LOS 3 DIGITOS DE countryCode en ASCII 
	MOV BX, [BP + 6]					; Guardamos en BX el numero countryCode en decimal, unsigned int(ocupa 2 bytes)
	MOV DX, 0H
	CALL printASCII						; Llamamos a la funcion printASCII para transformar el dato guardado en BX a ASCII
	MOV BX, 2							; Guardamos en BX un 2, ya que empezaremos a leer desde RESULTADO[2], porque countryCode tiene 3 digitos
	MOV CX, 5							; Guardamos en CX un 5 para ver si seguimos iterando en el bucle FOR_COUNTRY o no.
	
	FOR_COUNTRY:						; BUCLE PARA LEER EL VALOR ASCII DE countryCode GUARDADO EN  LA VARIABLE RESULTADO
	CMP BX, CX							; Comprobamos si BX y CX son iguales, es decir, si ya hemos leido los 3 digitos de countryCode de RESULTADO
	JE COMPANY							; Si son iguales, saltamos a COMPANY para proceder a obtener companyCode
	MOV AL, RESULTADO[BX]				; Guardamos en AL el digito de countryCode (en ASCII)
	MOV ES:[DI], AL                 	; Guardamos el digito en ASCII de countryCode en la direccion correspondiente SEG out_barCodeASCII : OFFSET out_barCodeASCII : + DI
	INC DI								; Incrementamos DI para escribir el siguiente digito ASCII de countryCode en la siguiente posicion(siguiente byte)
	INC BX								; Incrementamos BX para leer el siguiente digito
	JMP FOR_COUNTRY						; Saltamos a FOR_COUNTRY 
	
	COMPANY:							; OBTENEMOS LOS 4 DIGITOS DE companyCode en ASCII 
	MOV BX, [BP + 8]					; Guardamos en BX el numero companyCode en decimal, unsigned int(ocupa 2 bytes)
	MOV DX, 0H
	CALL printASCII						; Llamamos a la funcion printASCII para transformar el dato decimal guardado en BX a ASCII
	MOV BX, 1							; Guardamos en BX la posicion 1 ya que empezaremos a leer desde RESULTADO[1], porque countryCode tiene 4 digitos
	
	FOR_COMPANY:						; BUCLE PARA LEER EL VALOR ASCII DE companyCode GUARDADO EN  LA VARIABLE RESULTADO, Y GUARDARLO EN LA DIRECCION CORRESPONDIENTE DE out_barCodeASCII
	CMP BX, CX							; Comprobamos si BX y CX son iguales, es decir, si ya hemos leido los 4 digitos de countryCode de RESULTADO
	JE PRODUCT2							; Si son iguales, saltamos a PRODUCT2
	MOV AL, RESULTADO[BX]				; Guardamos en AL el digito de companyCode (en ASCII)
	MOV ES:[DI], AL						; Guardamos el digito en ASCII de companyCode en la direccion correspondiente SEG out_barCodeASCII : OFFSET out_barCodeASCII + DI
	INC DI								; Incrementamos DI para escribir el siguiente digito ASCII de companyCode en la siguiente posicion(siguiente byte)
	INC BX								; Incrementamos BX para leer el siguiente digito en ASCII de companyCode
	JMP FOR_COMPANY						; Saltamos a FOR_COMPANY
	
	PRODUCT2:								; OBTENEMOS LOS 5 DIGITOS DE productCode en ASCII long (ocupa 4 bytes)
	MOV DX, [BP + 12]					; Guardamos en DX la palabra mas significativa, (decenas de mil)
	MOV BX, [BP + 10]					; Guardamos en BX la palabra menos significativa (unidades de mil-centenas-decenas-unidades)
	CALL printASCII				; Llamamos a la funcion printASCIILARGO para transformar el dato de 4 bytes a ASCII
	MOV BX, 0							; Guardamos en BX la posicion 0 ya que empezaremos a leer desde RESULTADO[0], porque productCode tiene 5 digitos
	
	FOR_PRODUCT2:						; BUCLE PARA LEER EL VALOR ASCII DE productCode GUARDADO EN  LA VARIABLE RESULTADO, Y GUARDARLO EN LA DIRECCION CORRESPONDIENTE DE out_barCodeASCII
	CMP BX, CX							; Comprobamos si BX y CX son iguales, es decir, si ya hemos leido los 5 digitos de countryCode de RESULTADO
	JE CONTROL							; Si son iguales, saltamos a CONTROL
	MOV AL, RESULTADO[BX]				; Guardamos en AL el digito de productCode (en ASCII)
	MOV ES:[DI], AL						; Guardamos el digito en ASCII de productCode en la direccion correspondiente SEG out_barCodeASCII : OFFSET out_barCodeASCII + DI	
	INC DI								; Incrementamos DI para escribir el siguiente digito ASCII de productCode en la siguiente posicion(siguiente byte)
	INC BX								; Incrementamos BX para leer el siguiente digito en ASCII de productCode de la variable RESULTADO
	JMP FOR_PRODUCT2					; Saltamos a FOR_PRODUCT2
	
	CONTROL:
	MOV BX, [BP + 14]					; Guardamos en BX el numero controlDigit en decimal, unsigned char(ocupa 1 bytes), pero solo se puede acceder a la pila de palabra en palabra
	MOV DX, 0H
	CALL printASCII						; Llamamos a la funcion printASCII para transformar el dato el dato decimal guardado en BX a ASCII
	MOV AL, RESULTADO[4]				; Guardamos en AL el digito de control de controlDigit (en ASCII)
	MOV ES:[DI], AL						; Guardamos el digito en ASCII de controlDigit en la direccion correspondiente SEG out_barCodeASCII : OFFSET out_barCodeASCII + DI	
	INC DI								; Incrementamos DI para escribir el caracter fin de cadena en la siguiente posicion(siguiente byte)
	MOV BYTE PTR ES:[DI],0				; Guardamos el caracter fin de cadena 0 en ES:[DI]	
		
	POP AX BX CX DX SI DI ES			; Restaura el valor de los registros usados antes de salir
	POP BP 								; Restaura el valor de BP antes de salir
	RET									; Termina la funcion createBarCode
	
_createBarCode ENDP
	
;_______________________________________________________________ 
;  Dividir 16 bits entre 8 bits (Dividendo=AX, 
;  Divisor=operando 8bits, Cociente=AL, Resto=AH)
;
;  Dividir 32 bits entre 16 bits (Dividendo=DX AX, 
;  Divisor=operando 16bits, Cociente=AX, Resto=DX
;
;  La división utilizada es la de 32 bits entre 16 bits ya que
;  para números grandes el resto de la primera división es más
;  grande que el tamaño de AH
;_______________________________________________________________ 

printASCII PROC NEAR 					
	MOV AX, BX							; Guardamos en AX el dato que quiero transformar a ASCII 
	
	MOV SI, 4							; Indice de resultado, empieza por el final
	MOV RESULTADO[0], 30h					; Limpio la variable resultado que se usa de buffer
	MOV RESULTADO[1], 30h
	MOV RESULTADO[2], 30h
	MOV RESULTADO[3], 30h
	MOV RESULTADO[4], 30h
	
	DIVIDIRLAGO: 
		IDIV DIEZ						; Cociente=AX, Resto=DX
		ADD DX, 48						; Sumamos al resto de la division 48 = 30H
		MOV RESULTADO[SI], DL			; Almacenamos el resultado en la variable resultado
		DEC SI							; Recorremos de fin a inicio el array RESULTADO
		CMP AX, 0H						; Si ya no se puede dividir el numero, saltamos a FINIR, que retorna
		JE FINIR							
		MOV DX, 0H
		JMP DIVIDIRLAGO					; Volvemos a dividir , hasta que el cociente sea 0
	FINIR: 
		RET 							; Retorno
		
printASCII ENDP 

; FIN DEL SEGMENTO DE CODIGO 
PRACT3B ENDS 
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION 
END  

