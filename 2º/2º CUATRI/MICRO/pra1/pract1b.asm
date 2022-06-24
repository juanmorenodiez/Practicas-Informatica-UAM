;**************************************************************************
; SBM 2019. ESTRUCTURA BÁSICA DE UN PROGRAMA EN ENSAMBLADOR
;**************************************************************************

; DEFINICION DEL SEGMENTO DE DATOS

DATOS SEGMENT

		CONTADOR 		DB 	?																	;Reservamos memoria para una variable, CONTADOR, de un byte de tamaño, sin inicializarla.
		TOME 				DW 	0CAFEH														;Reservamos memoria para una variable, TOME, de dos bytes de tamaño y la inicializamos con el valor CAFEH. 
		TABLA100 		DB 	100 DUP (?)													;Reservamos 100 bytes para una tabla llamada TABLA100 con DUP que reserva 100 veces un byte sin inicializarlo.
		ERROR1 			DB 	"Atención: Entrada de datos incorrecta."			;Declaramos una variable de cadena de caracteres ERROR1.

DATOS ENDS

;**************************************************************************
; DEFINICION DEL SEGMENTO DE PILA

PILA SEGMENT STACK "STACK"

		DB 40H DUP (0) ;ejemplo de inicialización, 64 bytes inicializados a 0

PILA ENDS

;**************************************************************************
; DEFINICION DEL SEGMENTO EXTRA

EXTRA SEGMENT

		RESULT DW 0,0 ;ejemplo de inicialización. 2 PALABRAS (4 BYTES)

EXTRA ENDS

;**************************************************************************
; DEFINICION DEL SEGMENTO DE CODIGO

CODE SEGMENT

ASSUME CS: CODE, DS: DATOS, ES: EXTRA, SS: PILA

; COMIENZO DEL PROCEDIMIENTO PRINCIPAL

INICIO PROC

		; COMIENZO DEL PROGRAMA

		MOV 	AL, ERROR1[3-1]				;Guardo en el registro AL de un byte, el tercer carácter de la cadena ERROR1 "e" valor ASCII 101 o 65H.
		MOV 	TABLA100[63H], AL			;Copio en la posicion 63H de TABLA100 el contenido del registro AL = 65H;
		
		MOV 	AX, TOME						;Guardo en el registro AX de dos bytes, el contenido de la variable TOME.
		MOV 	TABLA100[23H], AH			;Copio el contenido del registro AH en la posición 23H de TABLA100.
		MOV 	TABLA100[24H], AL			;Copio el contenido del registro AL en la posición 24H de TABLA100.
		
		MOV 	AX, TOME						;Guardo en el registro AX de dos bytes, el contenido de la variable TOME, AH = CA AL =FE.
		MOV 	CONTADOR, AH				;Copio el byte más significativo de TOME, que es CA guardado en el registro AH, en la variable CONTADOR.

		; FIN DEL PROGRAMA

		MOV 	AX, 4C00H 
		INT 		21H
		
INICIO ENDP

; FIN DEL SEGMENTO DE CODIGO

CODE ENDS

; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION

END INICIO 