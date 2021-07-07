;**************************************************************************
; SBM 2019. ESTRUCTURA BÁSICA DE UN PROGRAMA EN ENSAMBLADOR
;**************************************************************************

; DEFINICION DEL SEGMENTO DE DATOS

DATOS SEGMENT

		DATO_1 DW 1918H				;Datos de libre elección que utilizamos para escribir en las direccion de memoria físicas calculadas.
		DATO_2 DW 2034H
		DATO_3 DW 0636H

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
		
		;Primera Comprobacion
		
		MOV AX, 0535H	;			Guardamos en AX el valor 0535H;
		MOV DS, AX					;Inicializamos el segmento de datos de tal forma que apunte a la direccion contenida en AX que en este caso es 0535H.
		
		MOV BX, 0210H				;Inicializamos el registro BX con el valor 0210H.
		MOV DI, 1011H					;Inicializamos el registro DI con el valor 1011H.
		
		MOV AX, DATO_1				;En AX se guarda el DATO_1 = 1918H
		MOV DS:[1234H], AX 		;Guardamos en la direccion 06584H la DATO_1 = 1918H
		MOV AL, DS:[1234H]		;Escribe en el registro de un byte AL el contenido de la la posición de memoria 06584H, AL=18H.
		
		;Segunda Comprobacion
		
		MOV AX, [BX]					;Lee el contenido de la posición de memoria física 05560H y lo guarda en el registro AX
		MOV CX, DATO_2   		    ;En CX se guarda el DATO_2 = 2034H
		MOV [BX], CX					;Guardamos en la direccion 05560H el dato 2034H
		MOV DX, [BX] 					;En el registro DX se debe guardar el dato 3420H
		
		;Tercera Comprobacion
		
		MOV AX, DATO_3				;En AX se guarda el DATO_3 = 0636H
		MOV [DI], AL					;Escribe en la posición de memoria 06361H el contenido de AL = 36h
		
		; FIN DEL PROGRAMA

		MOV AX, 4C00H
		INT 21H
INICIO ENDP

; FIN DEL SEGMENTO DE CODIGO

CODE ENDS

; FIN DEL PROGRAMA INDICANDO DONDE COMIENZA LA EJECUCION

END INICIO 