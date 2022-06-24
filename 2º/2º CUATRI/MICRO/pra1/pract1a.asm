;**************************************************************************
; SBM 2019. ESTRUCTURA BÁSICA DE UN PROGRAMA EN ENSAMBLADOR
;**************************************************************************

; DEFINICION DEL SEGMENTO DE DATOS

DATOS SEGMENT

	DATOS_1		DW		6000H		;Declaramos este dato DATOS_1 simplemente para que sea más visible el contenido inicial del segmento DS.

DATOS ENDS

;**************************************************************************
; DEFINICION DEL SEGMENTO DE PILA

PILA SEGMENT STACK "STACK"

	DB 40H DUP (0) 						;ejemplo de inicialización, 64 bytes inicializados a 0

PILA ENDS

;**************************************************************************
; DEFINICION DEL SEGMENTO EXTRA

EXTRA SEGMENT

	RESULT DW 0,0 						;ejemplo de inicialización. 2 PALABRAS (4 BYTES)

EXTRA ENDS

;**************************************************************************
; DEFINICION DEL SEGMENTO DE CODIGO

CODE SEGMENT

ASSUME CS: CODE, DS: DATOS, ES: EXTRA, SS: PILA

; COMIENZO DEL PROCEDIMIENTO PRINCIPAL

INICIO PROC

	; INICIALIZA LOS REGISTROS DE SEGMENTO CON SU VALOR
	MOV AX, DATOS						;Cargamos en el registro AX el contenido de la variable DATOS_1 = 6000H.
	MOV DS, AX							;Cargamos en DS el contenido del registro AX para que DS apunte a la direccion 6000H.
	MOV AX, PILA
	MOV SS, AX
	MOV AX, EXTRA
	MOV ES, AX
	MOV SP, 64 ; CARGA EL PUNTERO DE PILA CON EL VALOR MAS ALTO
	; FIN DE LAS INICIALIZACIONES 

	
	;COMIENZO DEL PROGRAMA 
	MOV AX, 15H						;Guardamos 15H (0015H) en el registro AX 

	MOV BX, 0BBH					;Guardamos BBH (00BBH) en el registro BX 

	MOV CX, 3412H					;Guardamos 3412H en el registro CX 

	MOV DX, CX						;Guardamos el valor de CX en el registro DX

	;MOV BH, [5536H]
	;MOV BL, [5537H]
	MOV AX, DS:[5536H]			;Guardamos en el registro AX el contenido de la memoria de la direccion DS:[5536H], AH = [5537H], AL = [5536H].
	MOV BL, AH							;Guardamos en la parte baja del registro BX(BL) el contenido del registro AH (contenido de la direccion de memoria DS:[5537H]).
	MOV BH, AL							;Guardamos en la parte alta del registro BX(BH) el contenido  del registro AL (contenido de la direccion de memoria DS:[5536H]).

	MOV AX, 5000H					;Guardamos 5000H en el registro AX.
	MOV DS, AX						;Movemos el segmento de datos a la direccion almacenada en AX.
	MOV DS:[0005H], CH			;Guardamos en la posicion de memoria DS[0005H] (50005H de DS) el contenido del registro CH de un byte.

	MOV AX, [SI]						;Guardamos el registro AX el contenido de la memoria de la direccion marcada por [SI] respecto DS.

	MOV BX, DS:[BP+10]			;Guardamos en el registro BX el contenido de la memoria almacenado en la direccion marcada por [BP + 10] (offset 10 en este caso) respecto DS.

; FIN DEL PROGRAMA

MOV AX, 4C00H
INT 21H
INICIO ENDP

; FIN DEL SEGMENTO DE CODIGO

CODE ENDS

; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION

END INICIO 