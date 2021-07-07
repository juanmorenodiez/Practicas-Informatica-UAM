;******************************************************************************* 
; CALCULA UN DETERMINANTE ESTATICO 
; ENCUENTRAN EN LAS POSICIONES DE MEMORIA 0 Y 1 DEL SEGMENTO DE 
; DATOS. EL VALOR DE CADA NUMERO DEBE SER INFERIOR A 9. EL RESULTADO 
; SE ALMACENA EN DOS PALABRAS DEL SEGMENTO EXTRA, EN LA PRIMERA 
; PALABRA EL MENOS SIGNIFICATIVO Y EN LA SEGUNDA EL MAS 
; SIGNIFICATIVO. SE UTILIZA UNA RUTINA PARA CALCULAR EL FACTORIAL. 
;*******************************************************************************

; DEFINICION DEL SEGMENTO DE DATOS 

DATOS SEGMENT 

	MATRIZ 	DB -1,-2,3					;DECLARAMOS UNA MATRIZ 3X3
			DB 4,5,6
			DB 7,8,2

	DATOSPORTECLADO  	DB 37 DUP (?)	;DATOS LEIDOS POR TECLADO
				
	DIAGPRINCIPAL 		DW 2 DUP (?)	;RESULTADO PARCIAL DE LA DIAGONAL PRINCIPAL
	
	DIAGINVERSA			DW 2 DUP (?)	;RESULTADO PARCIAL DE LA DIAGONAL INVERSA
	
	RESULTADOS 			DW 16 DUP (?) 	;RESULTADOS PARCIALES DEL DETERMIANTE

	MULTPARC 			DW 2 DUP(?)		

	DETERMINANTE DW ?					;RESULTADO FINAL DEL DETERMINANTE
	
	CLR_PANT 	DB 	1BH,"[2","J$"		;BORRA LA PANTALLA
	
	INICIO		DB 	"CALCULO DE UN DETERMINANTE", 13,10, "$"
	
	MENU 		DB "_______________MENU________________", 13,10, "$"
	
	OPCION1 	DB 	"1) Calcular el determinante con valores por defecto", 13,10, "$"
	
	OPCION2 	DB 	"2) Calcular el determinante con valores introducidos por teclado", 13,10, "$"
	
	INTRODUCE 	DB 	"Elija una opcion para calcular el determinante, introduciendo 1 o 2: $", 13, 10, '$'
	
	ELECCION	DB 	1BH,"[15;1fElija una opcion para calcular el determinante, introduciendo 1 o 2: $$"
	
	NUMELEGIDO	DB 	4 DUP (?)
	
	OP2 		DB 	"Ha elegido la opcion 2, introduzca los valores separados por espacios (LOS NUMEROS DE 0 AL 9 CON UN 0 DELANTE), de la matriz: ", 13,10, "$"
	
	DIEZ		DW 10				
	
	DECIMAL 	DW ?
	
	RESULTADO   DB 6 DUP (?),'$' 		;NUMERO ENTRE –32768 a 32768
	
	TEXTO 		DB "|",13,10,"$"		;DECLARACION DE SIMBOLOS PARA LA MATRIZ
	
	TEXTO1		DB "|A| =", "$"
	
	TEXTO2		DB "        |","$"		
	
	TEXTO4 		DB "      |", "$"
	
	TEXTO3		DB "        |",13,10,"$"
	
	TEXTO5		DB "   |","$"
	
	IGUAL		DB "| = ","$"
	
	BAJA		DB 13,10,"$"
	
DATOS ENDS 


; DEFINICION DEL SEGMENTO DE PILA 

PILA    SEGMENT STACK "STACK" 
    DB   40H DUP (0) 
PILA ENDS 


; DEFINICION DEL SEGMENTO EXTRA 

EXTRA     SEGMENT 
    
EXTRA ENDS 


; DEFINICION DEL SEGMENTO DE CODIGO 

CODE    SEGMENT 
    ASSUME CS:CODE, DS:DATOS, ES: EXTRA, SS:PILA 

; COMIENZO DEL PROCEDIMIENTO PRINCIPAL 

START PROC 
    ;INICIALIZA LOS REGISTROS DE SEGMENTO CON SUS VALORES 
    MOV AX, DATOS 
    MOV DS, AX 

    MOV AX, PILA 
    MOV SS, AX 

    MOV AX, EXTRA 
    MOV ES, AX 

    ; CARGA EL PUNTERO DE PILA CON EL VALOR MAS ALTO 
    MOV SP, 64 

    ; FIN DE LAS INICIALIZACIONES 

    ;COMIENZO DEL PROGRAMA 
	
	
	MOV AH,9								; BORRA LA PANTALLA
	MOV DX, OFFSET CLR_PANT
	INT 21H
	
	MOV DX, OFFSET INICIO					;MUESTRA: _____CALCULO DE UN DETERMINANTE...						
	INT 21h 								;EJECUTA EL SERVICIO DEL SISTEMA OPERATIVO
	
	MOV DX,OFFSET MENU						;MUESTRA MENU...
	INT 21H

	MOV DX,OFFSET OPCION1					;MUESTRA "...
	INT 21H
	
	MOV DX,OFFSET OPCION2					;MUESTRA "...
	INT 21H
	
	MOV DX,OFFSET INTRODUCE					;MUESTRA "...
	INT 21H
                  
	MOV AH,0AH								;ALMACENA EL NUMERO TECLEADO
	MOV DX,OFFSET NUMELEGIDO
	MOV NUMELEGIDO[0],4						;MAXIMO NUMERO DE CARACTERES
	INT 21H
	
	CMP BYTE PTR NUMELEGIDO[2], 032H		;VERIFICA SI EL NUMERO INTRODUCIDO POR TECLADO ES 2
	JE LEER									;SI EL NUMERO TECLEADO ES 2 SALTA A LEER QUE SOBREESCRIBE LA MATRIZ CON LOS VALORES INTRODUCIDOS
	CALL CALCULAR							;CALCULA EL DETERMINANTE INDEPENDIENTEMENTE DE LA OPCION ELEGIDA
	CALL MUESTRA							;MUESTRA POR PANTALLA LA MATRIZ Y EL RESULTADO
	
	JMP ADIOS								;FINALIZA EL PROGRAMA

START ENDP 
;______________________________________________________________________________________________________________________________________________
; SUBRUTINA PARA LEER LOS DATOS POR TECLADO 
; ENTRADA INPUT DEL TECLADO
; SALIDA  DATOSPORTECLADO
;______________________________________________________________________________________________________________________________________________

LEER PROC NEAR 
	MOV AH,9								;BORRA LA PANTALLA
	MOV DX, OFFSET CLR_PANT
	INT 21H

	MOV DX,OFFSET OP2						;MUESTRA INSTRUCCIONES PARA METER NUMEROS A LA MATRIZ"...
	INT 21H

    MOV AH,0AH								;LLAMADA A LA INSTRUCCION DE LECTURA 
	MOV DX,OFFSET DATOSPORTECLADO			;GUARDAMOS LOS DATOS TECLEADOS EN LA VARIABLE DATOSPORTECLADO
	MOV DATOSPORTECLADO[0],37 				;GUARDAMOS EN EL PRIMER BYTE DE LA VARIABLE EL NUMERO MAXIMO DE DATOS QUE SE PUEDEN LEER
	INT 21H 								;EJECUTA EL SERVICIO DEL SISTEMA OPERATIVO
	
	CALL ASCII_DEC							;LLAMADA A FUNCION PARA TRANSFORMAR DE ASCII A DECIMAL
	CALL CALCULAR
	CALL MUESTRA							;UNA VEZ LOS DATOS EN DECIMAL DE IMPRIME LA MATRIZ RESULTANTE
	JMP ADIOS								;FIN DEL PROGRAMA 

LEER ENDP 

;______________________________________________________________________________________________________________________________________________
; SUBRUTINA PARA CALCULAR EL DETERMINANTE DE UNA MATRIZ 3X3 
; ENTRADA MATRIZ
; SALIDA  RESULTADOS
;______________________________________________________________________________________________________________________________________________


CALCULAR PROC NEAR
	;INDICE = FILA * COLUMNAS + COLUMNNA

	MOV AL, MATRIZ 						;GUARDAMOS EL DATO MATRIZ[0][0] EN AL
	MOV CL, MATRIZ[1*3+1]				;GUARDAMOS EL DATO MATRIZ[1][1] EN CL
	IMUL CL								;AX = AL*CL
	MOV MULTPARC, AX					;GUARDAMOS EN MULTPARC EL RESULTADO DE LA MULTIPLICACION
	
	MOV AL, MATRIZ[2*3+2]				;GUARDAMOS EL DATO MATRIZ[2][2] EN AL
	CBW									;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV CX, MULTPARC					;GUARDAMOS EN CX EL RESULTADO DE LA MULTIPLICACION PARCIAL ANTERIOR, GUARDADO EN LA VARIABLE MULTPARC
	IMUL CX								;DX:AX = AX*CX
	MOV DIAGPRINCIPAL[0], DX			;GUARDAMOS DX (RESULTADO DE LA MULTIPLICACION) EN DIAGPRINCIPAL[0]
	MOV DIAGPRINCIPAL[2], AX			;GUARDAMOS AX (RESULTADO DE LA MULTIPLICACION) EN DIAGPRINCIPAL[1]
	MOV MULTPARC, 00000000H				;LIMPIAMOS MULTPARC PARA QUE GUARDE DATOS BASURA
	
	MOV AL, MATRIZ[0*3+2] 				;HACEMOS ITERADAMENTE LO EXPLICADO ANTERIORMENTE PARA LOS DEMAS DATOS DE LA MATRIZ
	CBW
	MOV CL, MATRIZ[1*3+1]
	IMUL CL
	MOV MULTPARC, AX
	
	MOV AL, MATRIZ[2*3+0]
	CBW
	MOV CX, MULTPARC
	IMUL CX
	MOV DIAGINVERSA[0], DX
	MOV DIAGINVERSA[2], AX
	MOV MULTPARC, 00000000H
	
	MOV AL, MATRIZ[1*3+0] 				
	CBW
	MOV CL, MATRIZ[2*3+1]				
	IMUL CL
	MOV MULTPARC, AX
	
	MOV AL, MATRIZ[0*3+2]
	CBW
	MOV CX, MULTPARC
	IMUL CX
	MOV RESULTADOS[0], DX
	MOV RESULTADOS[2], AX
	MOV MULTPARC, 00000000H
	
	MOV AL, MATRIZ[0*3+1] 			
	CBW
	MOV CL, MATRIZ[1*3+2]				
	IMUL CL
	MOV MULTPARC, AX
	
	MOV AL, MATRIZ[2*3+0]
	CBW
	MOV CX, MULTPARC
	IMUL CX
	MOV RESULTADOS[4], DX
	MOV RESULTADOS[6], AX
	MOV MULTPARC, 00000000H
	
	MOV AL, MATRIZ[0*3+1] 				
	CBW
	MOV CL, MATRIZ[1*3+0]			
	IMUL CL
	MOV MULTPARC, AX
	
	MOV AL, MATRIZ[2*3+2]
	CBW
	MOV CX, MULTPARC
	IMUL CX
	MOV RESULTADOS[8], DX
	MOV RESULTADOS[10], AX
	MOV MULTPARC, 00000000H
	
	MOV AL, MATRIZ[1*3+2] 			
	CBW
	MOV CL, MATRIZ[2*3+1]				
	IMUL CL
	MOV MULTPARC, AX
	
	MOV AL, MATRIZ[0]
	CBW
	MOV CX, MULTPARC
	IMUL CX
	MOV RESULTADOS[12], DX
	MOV RESULTADOS[14], AX
	MOV MULTPARC, 00000000H
	
	CALL SUMA						;LLAMAMOS A LA FUNCION SUMA QUE SUMARA TODOS LOS RESULTADOS PARCIALES 
	JMP FIN							;UNA VEZ SUMADOS SE RETORNA AL PROGRAMA PRINCIPAL
	
CALCULAR ENDP

;______________________________________________________________________________________________________________________________________________
; SUBRUTINA PARA SUMAR LOS RESULTADOS PARCIALES DEL DETERMINANTE
; ENTRADA RESULTADOS
; SALIDA  DETERMIANTE
;______________________________________________________________________________________________________________________________________________

SUMA PROC NEAR					
	MOV AX, DIAGPRINCIPAL[2]		;GUARDAMOS EN AX EL RESULTADO DE LA MULTIPLICACION DE LA DIAGONAL PRINCIPAL
	MOV BX, RESULTADOS[2]			;GUARDAMOS EN BX EL RESULTADO DE UNA DE LAS MULTIPLICACIONES PARCIALES
	ADD AX, BX						;SUMAMOS AMBOS RESULTADOS AX = AX+BX
	MOV BX, RESULTADOS[6]			;GUARDAMOS BX EL RESULTADO DE UNA DE LAS MULTIPLICACIONES PARCIALES
	ADD AX, BX						;SUMAMOS AMBOS RESULTADOS AX = AX+BX
	MOV DETERMINANTE, AX			;GUARDAMOS EL RESULTADO DE LAS 3 PRIMERAS SUMAS EN LA VARIABLE DETERMINANTE
	
	MOV AX, DIAGINVERSA[2]			;GUARDAMOS EN AX EL RESULTADO DE LA MULTIPLICACION DE LA DIAGONAL INVERSA
	MOV BX, RESULTADOS[10]			;GUARDAMOS EN BX EL RESULTADO DE UNA DE LAS MULTIPLICACIONES PARCIALES
	ADD AX, BX						;SUMAMOS AMBOS RESULTADOS AX = AX+BX
	MOV BX, RESULTADOS[14]			;GUARDAMOS BX EL RESULTADO DE UNA DE LAS MULTIPLICACIONES PARCIALES
	ADD AX, BX						;SUMAMOS AMBOS RESULTADOS AX = AX+BX
	
	MOV BX, DETERMINANTE 			;GUARDAMOS EN BX LA SUMA DE LAS 3 PRIMERAS MULTIPLICACIONES
	SUB BX, AX						;RESTAMOS A BX LA SUMA DE LAS 3 RESTATES MULTIPLICACIONES	BX = BX-AX
	MOV DETERMINANTE, BX			;GUARDAMOS EL RESULTADO DE LA OPERACION EN LA VARIABLE DETERMINANTE
	JMP FIN							;RETORNO DE LA FUNCION
	
SUMA ENDP

;______________________________________________________________________________________________________________________________________________
; SUBRUTINA PARA TRANSFORMAR LOS NUMERO INTRODUCIDOS POR TECLADO (EN ASCII) A NUMEROS DECIMALES PARA PODER HACER EL DETERMINANTE
; ENTRADA DATOSPORTECLADO
; SALIDA  MATRIZ (SOBREESCRIBE)
;______________________________________________________________________________________________________________________________________________

ASCII_DEC PROC NEAR
	MOV DI, 0H							;INICIALIZACION DE INDICE DE MATRIZ (DONDE ESCRIBIREMOS LOS DATOS INTRODUCIDOS POR TECLADO EN DECIMAL)
	MOV CX, 0H							;BUFFER
	MOV SI, 1H							;INICIALIZACION DE INDICE DE DATOSPORTECLADO (EMPIEZA EN 1 PORQUE EN LA POSICION 0 SE GUARDA EL NUMERO MAXIMO DE CARACTERES PERMITIDO)
	
;PASAMOS DE CODIGO ASCII A UN NUMERO EN DECIMAL

	ASCII:								
	INC SI								;INCREMENTAMOS SI
	CMP DI, 09H							;VERIFICAMOS SI YA HEMOS TRANFORMADO LOS 9 DATOS
	JE FIN								;SI YA LOS HEMOS TRANSFORMADO RETORNAMOS
	CMP DATOSPORTECLADO[SI], 20H		;COMPROBAMOS SI ESTAMOS LEYENDO UN ESPACIO EN BLANCO
	JE ASCII							;SI ES ASI, SALTAMOS A LA ETIQUETA ASCII, QUE INCREMENTARA EL INDICE SI
	CMP DATOSPORTECLADO[SI],2DH			;COMPROBAMOS SI EL NUMERO QUE ESTAMOS LEYENDO ES NEGATIVO ('-' = 2DH)
	JE NEGATIVO							;SI ES NEGATIVO SALTAMOS A LA ETIQUETA NEGATIVO 
	JNE POSITIVO						;SI ES POSITIVO SALTAMOS A LA ETIQUETA POSITIVO 
	
	NEGATIVO:							;TRANFORMA A DECIMAL SOLO NUMEROS NEGATIVOS
	INC SI								;INCREMENTAMOS SI PORQUE SABEMOS QUE ES EL SIGO '-'
	SUB DATOSPORTECLADO[SI], 30H		;RESTAMOS AL DATO 48 = 30H (48 ES EL 0 EN ASCII)
	MOV AL, DATOSPORTECLADO[SI]			;GUARDAMOS EN AL EL RESULTADO DE LA RESTA
	MOV DL, 0AH							;GUARDAMOS EN DL UN 10 
	MUL DL								;MULTIPLICACION SIN SIGNO PORQUE DESPUES HACEMOS EL C2	AX = AL*DL	(COGEMOS LAS DECENAS)
	MOV MATRIZ[DI], AL					;GUARDAMOS EL RESULTADO(EN DECIMAL) EN LA MATRIZ
	INC SI								;INCREMENTAMOS SI
	SUB DATOSPORTECLADO[SI], 30H		;RESTAMOS AL DATO 48 = 30H (48 ES EL 0 EN ASCII) (UNIDADES)
	MOV AL, DATOSPORTECLADO[SI]			;GUARDAMOS EN AL EL RESULTADO DE LA RESTA
	ADD MATRIZ[DI], AL 					;SUMAMOS AL DATO INTRODUCIDO ANTERIORMENTE LAS UNIDADES
	NEG MATRIZ[DI]						;HACEMOS EL COMPLEMENTO A 2 DEL RESULTADO FINAL
	INC DI								;INCREMENTAMOS DI
	JMP ASCII
	
	POSITIVO:							;TRANFORMA A DECIMAL SOLO NUMEROS POSITIVOS
	SUB DATOSPORTECLADO[SI], 30H		;RESTAMOS AL DATO 48 = 30H (48 ES EL 0 EN ASCII)
	MOV AL, DATOSPORTECLADO[SI]			;GUARDAMOS EN AL EL RESULTADO DE LA RESTA
	MOV DL, 0AH							;GUARDAMOS EN DL UN 10 
	MUL DL								;AX = AL*DL	(COGEMOS LAS DECENAS)
	MOV MATRIZ[DI], AL					;GUARDAMOS EL RESULTADO(EN DECIMAL) EN LA MATRIZ
	INC SI								;INCREMENTAMOS SI
	SUB DATOSPORTECLADO[SI], 30H		;RESTAMOS AL DATO 48 = 30H (48 ES EL 0 EN ASCII)
	MOV AL, DATOSPORTECLADO[SI]			;GUARDAMOS EN AL EL RESULTADO DE LA RESTA
	ADD MATRIZ[DI], AL 					;SUMAMOS AL DATO INTRODUCIDO ANTERIORMENTE LAS UNIDADES
	INC DI								;INCREMENTAMOS DI
	JMP ASCII							;SALTO A ASCII (AL SIGUIENTE DATO)
	

ASCII_DEC ENDP

FIN: 
    RET 
	
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
	MOV AX, BX						;GUARDAMOS EN AX EL DATO QUE QUIERO TRANFORMAR A ASCII
	MOV DX, 0H						;GUARDAMOS EN DX UN 0H
	MOV SI, 5						;INDICE DE RESULTADO, EMPIEZA POR EL FINAL
	MOV RESULTADO[0], 0				;LIMPIO LA VARIABLE RESULTADO QUE SE USA DE BUFFER
	MOV RESULTADO[1], 0
	MOV RESULTADO[2], 0
	MOV RESULTADO[3], 0
	MOV RESULTADO[4], 0
	MOV RESULTADO[5], 0
	CMP BH, 0FFH					;COMPROBAMOS SI EL NUMERO ES NEGATIVO
	JE C2							;SI ES NEGATIVO SALTO A LA ETIQUETA C2, QUE HARA EL COMPLEMENTO A 2 DE ESE DATO
		
DIVIDIR: 
	IDIV DIEZ						;Cociente=AX, Resto=DX
	ADD DX, 48						;SUMAMOS AL RESTO DE LA DIVISION 48 = 30H
	MOV RESULTADO[SI], DL			;ALMACENAMOS EL RESULTADO EN LA VARIABLE RESULTADO
	SUB SI, 1						;RECORREMOS DE FIN A INCIO EL ARRAY RESULTADO
	CMP AX, 0H						;SI YA NO SE PUEDE DIVIDIR EL NUMERO SALTAMOS A FINI, QUE RETORNA
	JE FINI							
	MOV DX, 0H						;GUARDAMOS EN DX UN 0H
	JMP DIVIDIR						;VOLVEMOS A DIVIDIR, HASTA QUE EL COCIENTE SEA 0
FINI: 
	RET 							;RETORNO
C2:
	MOV RESULTADO[2], 2DH			;GUARDAMOS EN RESULTADO EL '-' DEL NUMERO NEGATIVO
	NEG BX							;HACEMOS EL COMPLEMENTO A 2 DEL NUMERO PARA QUE O TRANFORME A UN DECIMAL POSTIVO MUY ALTO
	MOV AX,BX						;GUARDAMOS EL NUMERO EN AX
	JMP DIVIDIR						;SALTAMOS A DIVIDIR, YA SABIENDO QUE EL NUMERO TIENE UN '-'
printASCII ENDP 

;______________________________________________________________________________________________________________________________________________
; SUBRUTINA PARA IMPRIMIR LA MATRIZ Y EL RESULTADO DEL DETERMINANTE
; ENTRADA MATRIZ, DETERMINANTE
; SALIDA  POR PANTALLA
;______________________________________________________________________________________________________________________________________________


MUESTRA PROC NEAR

	MOV AH,9						;BORRA LA PANTALLA
	MOV DX, OFFSET CLR_PANT			
	INT 21H

	MOV DI, 0						;GUARDAMOS EN DI UN 0
	MOV AL, MATRIZ[DI]				;GUARDAMOS EL DATO MATRIZ[0] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE IMPRIMIRA EL VALOR DE MATRIZ[0]

	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN TEXTO2 
	MOV DX, OFFSET TEXTO2
	INT 21H					
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI (0+1=1)
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[1] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[1] DE DECIMAL A ASCII

	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[2] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[2] DE DECIMAL A ASCII
	
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO	
	MOV DX, OFFSET RESULTADO
	INT 21H
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN TEXTO		
	MOV DX, OFFSET TEXTO			
	INT 21H								
	MOV DX, OFFSET TEXTO1			;IMPRIME POR PANTALLA LO QUE HAYA EN TEXTO1
	INT 21H
	MOV DX, OFFSET TEXTO5			;IMPRIME POR PANTALLA LO QUE HAYA EN TEXTO5
	INT 21H

	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[3] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[3] DE DECIMAL A ASCII

	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO		
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[4] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[4] DE DECIMAL A ASCII
	
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO		
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[5] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[5] DE DECIMAL A ASCII
	
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO	
	MOV DX, OFFSET RESULTADO
	INT 21H
					
	MOV DX, OFFSET IGUAL			;IMPRIME POR PANTALLA LO QUE HAYA EN IGUAL
	INT 21H		
	
	MOV BX, DETERMINANTE			;IMPRIMO EL RESULTADO DEL DETERMINANTE
	MOV AX, BX
	CALL printASCII					;CONVIERTO EL RESULTADO DEL DETERMINANTE DE DECIMAL A ASCII
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO		
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	MOV DX, OFFSET BAJA				;IMPRIME POR PANTALLA LO QUE HAYA EN BAJA
	INT 21H	

				
	MOV DX, OFFSET TEXTO2			;IMPRIME POR PANTALLA LO QUE HAYA EN TEXTO2
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[6] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[6] DE DECIMAL A ASCII
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO	
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[7] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[7] DE DECIMAL A ASCII
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO			
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	INC DI							;INCREMENTA EL VALOR DE DI
	MOV AL, MATRIZ[DI]				;GUARDAMOS EN DATO MATRIZ[8] EN AL
	CBW								;EXTENDEMOS EN SIGNO DEL DATO GUARDADO EN AL	AX = SIGNO_EXTENDIDO(AL)
	MOV BX, AX						;GUARDAMOS EN BX, AX
	CALL printASCII					;LLAMAMOS A LA FUNCION PRINTASCII QUE PASA MATRIZ[8] DE DECIMAL A ASCII
	MOV AH,9						;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO
	MOV DX, OFFSET RESULTADO
	INT 21H
	
	MOV DX, OFFSET TEXTO			;IMPRIME POR PANTALLA LO QUE HAYA EN RESULTADO
	INT 21H
	RET								;RETORNO
MUESTRA ENDP

ADIOS PROC NEAR
; FIN DEL PROGRAMA 
    MOV AX, 4C00H 
    INT 21H
ADIOS ENDP
	
; FIN DEL SEGMENTO DE CODIGO 
CODE ENDS 
; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION 
END START 

