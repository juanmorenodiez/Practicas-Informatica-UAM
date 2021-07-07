write_log(S) :- open('error_logs.txt', append, Out), write(Out, S), write(Out, '\n'), close(Out).

/***************
* EJERCICIO 1. sum_pot_prod/4
*
*	ENTRADA:
*		X: Vector de entrada de numeros de valor real.
*		Y: Vector de entrada de numeros de valor real.
*		Potencia: Numero de valor entero, potencia.
*	SALIDA:
*		Resultado: Numero de valor real resultado de la operacion sum_pot_prod.
*
****************/
/* control de errores para la longitud */
sum_pot_prod([], [_|_], _, _) :- print('ERROR 1.2 Longitud.'), !, fail.
sum_pot_prod([_|_], [], _, _) :- print('ERROR 1.2 Longitud.'), !, fail.
/* control de errores para la potencia */
sum_pot_prod(_, _, Potencia, _) :- Potencia < 1, write_log('ERROR 1.1 Potencia.'), !, fail.

/* predicado */
sum_pot_prod([], [], Potencia, 0).
sum_pot_prod([H1|T1], [H2|T2], Potencia, Resultado) :- sum_pot_prod(T1, T2, Potencia, R), Resultado is R+(H1*H2)^Potencia.


/***************
* EJERCICIO 2. segundo_penultimo/3
*
*       ENTRADA:
*               L: Lista de entrada de numeros de valor real.
*       SALIDA:
*               X : Numero de valor real. Segundo elemento.
*		Y : Numero de valor real. Penultimo elemento.
*
****************/
segundo([_,S|_], S).

penultimo([P,_], P).
penultimo([_|T], P) :- penultimo(T, P).

/* control de errores lista con tamaño < 2 */

/* tam = 0 */
segundo_penultimo([], X, Y) :- write_log('ERROR 2.1 Longitud.'), !, fail.
/* tam = 1 */
segundo_penultimo([_|T], X, Y) :- T == [], write_log('ERROR 2.1 Longitud.'), !, fail.
segundo_penultimo(L, X, Y) :- segundo(L,X), penultimo(L,Y).

/***************
* EJERCICIO 3. sublista/5
*
*       ENTRADA:
*		L: Lista de entrada de cadenas de texto.
*		Menor: Numero de valor entero, indice inferior.
*		Mayor: Numero de valor entero, indice superior.
*		E: Elemento, cadena de texto.
*       SALIDA:
*		Sublista: Sublista de salida de cadenas de texto.
*
****************/
/* longitud de la lista, se guarda en N */
list_length([], 0).
list_length([H|T], N) :- list_length(T, N1), N is N1+1.

/* control de errores */
sublista(L, Menor, Mayor, E, Sublista) :- not(member(E, L)), write_log('ERROR 3.1 Elemento.'), !, fail.
sublista(L, Menor, Mayor, E, Sublista) :- Menor >= Mayor, write_log('ERROR 3.2 Indices.'), !, fail.
sublista(L, Menor, Mayor, E, Sublista) :- list_length(L, N), Mayor >= N, write_log('ERROR 3.2 Indices.'), !, fail.
sublista(L, Menor, Mayor, E, Sublista) :- slice(L, Menor, Mayor, Sublista).

/* particion de la lista entre dos numeros */
slice([X|_],1,1,[X]).
slice([X|Xs],1,K,[X|Ys]) :- K > 1, K1 is K - 1, slice(Xs,1,K1,Ys).
slice([_|Xs],I,K,Ys) :- I > 1, I1 is I - 1, K1 is K - 1, slice(Xs,I1,K1,Ys).

/***************
* EJERCICIO 4. espacio_lineal/4
*
*       ENTRADA:
*               Menor: Numero de valor entero, valor inferior del intervalo.
*               Mayor: Numero de valor entero, valor superior del intervalo.
*               Numero_elementos: Numero de valor entero, numero de valores de la rejilla.
*       SALIDA:
*               Rejilla: Vector de numeros de valor real resultante con la rejilla.
*
****************/
rejilla(I, P, U, [U]) :- X is U-P, X < I.
rejilla(I, P, U, [P|R]) :- N is P+I, rejilla(I,N,U,R).

espacio_lineal(Menor, Mayor, _, _) :- Menor >= Mayor, write_log('ERROR 4.1 Indices.'), !, fail.
espacio_lineal(Menor, Mayor, Numero_elementos, Rejilla) :- N1 is Numero_elementos-1, rejilla(Mayor/N1, Menor, Mayor, Rejilla).

/***************
* EJERCICIO 5. normalizar/2
*
*       ENTRADA:
*		Distribucion_sin_normalizar: Vector de numeros reales de entrada. Distribucion sin normalizar.
*       SALIDA:
*		Distribucion: Vector de numeros reales de salida. Distribucion normalizada.
*
****************/
/* suma de la lista y control de errores */
list_sum([], 0).
list_sum([Head|_], _) :- Head < 0, write_log('ERROR 5.1 Negativos.'), !, fail.
list_sum([Head|Tail], Sum) :- list_sum(Tail,SumTemp), Sum is Head + SumTemp.

normalizar_rec([], [], _).
normalizar_rec([X|Xs], [Y|Ys], S) :- Y is X/S, normalizar_rec(Xs, Ys, S).

normalizar(L, Distribucion) :- list_sum(L, Sum), normalizar_rec(L, Distribucion, Sum).

/***************
* EJERCICIO 6. divergencia_kl/3
*
*       ENTRADA:
*		D1: Vector de numeros de valor real. Distribucion.
*		D2: Vector de numeros de valor real. Distribucion.
*       SALIDA:
*		KL: Numero de valor real. Divergencia KL.
*
****************/

existen_ceros([]) :- !, fail.
existen_ceros([X|R]) :- X=:=0.
existen_ceros([_|R]) :- existen_ceros(R).

divergencia_kl(D1, _, _) :- existen_ceros(D1), write_log('ERROR 6.1. Divergencia KL no definida.'), !, fail.
divergencia_kl(_, D2, _) :- existen_ceros(D2), write_log('ERROR 6.1. Divergencia KL no definida.'), !, fail.
/* para implementar el ultimo error tendriamos que hacer algo de este estilo, pero no nos funciona */
/* divergencia_kl(D1, D2, _) :- list_sum(D1, Sum1), list_sum(D2, Sum2), Sum1+Sum2 =\= 2.0, write_log('ERROR 6.1. Divergencia KL definida solo para distribuciones.'), !, fail. */

divergencia_kl([], [], 0).
divergencia_kl([H1|T1], [H2|T2], KL) :- divergencia_kl(T1, T2, KL1), KL is H1*log(H1/H2)+KL1.

/* PROBLEMA DE LAS 8 REINAS */

% P90 (**) Eight queens problem

% This is a classical problem in computer science. The objective is to
% place eight queens on a chessboard so that no two queens are attacking
% each other; i.e., no two queens are in the same row, the same column,
% or on the same diagonal. We generalize this original problem by
% allowing for an arbitrary dimension N of the chessboard.

% We represent the positions of the queens as a list of numbers 1..N.
% Example: [4,2,7,3,6,8,5,1] means that the queen in the first column
% is in row 4, the queen in the second column is in row 2, etc.
% By using the permutations of the numbers 1..N we guarantee that
% no two queens are in the same row. The only test that remains
% to be made is the diagonal test. A queen placed at column X and
% row Y occupies two diagonals: one of them, with number C = X-Y, goes
% from bottom-left to top-right, the other one, numbered D = X+Y, goes
% from top-left to bottom-right. In the test predicate we keep track
% of the already occupied diagonals in Cs and Ds.

% The first version is a simple generate-and-test solution.

% queens_1(N,Qs) :- Qs is a solution of the N-queens problem

queens_1(N,Qs) :- range(1,N,Rs), permu(Rs,Qs), test(Qs).

% range(A,B,L) :- L is the list of numbers A..B

range(A,A,[A]).
range(A,B,[A|L]) :- A < B, A1 is A+1, range(A1,B,L).

% permu(Xs,Zs) :- the list Zs is a permutation of the list Xs

permu([],[]).
permu(Qs,[Y|Ys]) :- del(Y,Qs,Rs), permu(Rs,Ys).

del(X,[X|Xs],Xs).
del(X,[Y|Ys],[Y|Zs]) :- del(X,Ys,Zs).

% test(Qs) :- the list Qs represents a non-attacking queens solution

test(Qs) :- test(Qs,1,[],[]).

% test(Qs,X,Cs,Ds) :- the queens in Qs, representing columns X to N,
% are not in conflict with the diagonals Cs and Ds

test([],_,_,_).
test([Y|Ys],X,Cs,Ds) :-
	C is X-Y, \+ memberchk(C,Cs),
	D is X+Y, \+ memberchk(D,Ds),
	X1 is X + 1,
	test(Ys,X1,[C|Cs],[D|Ds]).

%--------------------------------------------------------------

% Now, in version 2, the tester is pushed completely inside the
% generator permu.

queens_2(N,Qs) :- range(1,N,Rs), permu_test(Rs,Qs,1,[],[]).

permu_test([],[],_,_,_).
permu_test(Qs,[Y|Ys],X,Cs,Ds) :-
	del(Y,Qs,Rs),
	C is X-Y, \+ memberchk(C,Cs),
	D is X+Y, \+ memberchk(D,Ds),
	X1 is X+1,
	permu_test(Rs,Ys,X1,[C|Cs],[D|Ds]).


/***************
* EJERCICIO 7. producto_kronecker/3
*
*       ENTRADA:
*		Matriz_A: Matriz de numeros de valor real.
*		Matriz_B: Matriz de numeros de valor real.
*       SALIDA:
*		Matriz_bloques: Matriz de bloques (matriz de matrices) de numeros reales.
*
****************/
producto_kronecker(Matriz_A, Matriz_B, Matriz_bloques) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8a. distancia_euclidea/3
*
*       ENTRADA:
*               X1: Vector de numeros de valor real.
*               X2: Vector de numeros de valor real.
*       SALIDA:
*               D: Numero de valor real. Distancia euclidea.
*
****************/
distancia_euclidea(X1, X2, D) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8b. calcular_distancias/3
*
*       ENTRADA:
*               X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*               X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*
****************/
calcular_distancias(X_entrenamiento, X_test, Matriz_resultados) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8c. predecir_etiquetas/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Matriz_resultados: Matriz de numeros de valor real donde cada fila es un vector con la distancia de un punto de test al conjunto de entrenamiento X_entrenamiento.
*       SALIDA:
*               Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
predecir_etiquetas(Y_entrenamiento, K, Matriz_resultados, Y_test) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8d. predecir_etiqueta/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
predecir_etiqueta(Y_entrenamiento, K, Vec_distancias, Etiqueta) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8e. calcular_K_etiquetas_mas_relevantes/4
*
*       ENTRADA:
*               Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*               K: Numero de valor entero.
*               Vec_distancias: Vector de valores reales correspondiente a una fila de Matriz_resultados.
*       SALIDA:
*		K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*
****************/
calcular_K_etiquetas_mas_relevantes(Y_entrenamiento, K, Vec_distancias, K_etiquetas) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8f. calcular_etiqueta_mas_relevante/2
*
*       ENTRADA:
*               K_etiquetas: Vector de valores alfanumericos de una distribucion categorica.
*       SALIDA:
*               Etiqueta: Elemento de valor alfanumerico.
*
****************/
calcular_etiqueta_mas_relevante(K_etiquetas, Etiqueta) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.

/***************
* EJERCICIO 8g. k_vecinos_proximos/5
*
*       ENTRADA:
*		X_entrenamiento: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector.
*		Y_entrenamiento: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_entrenamiento.
*		K: Numero de valor entero.
*		X_test: Matriz de numeros de valor real donde cada fila es una instancia representada por un vector. Instancias sin etiquetar.
*       SALIDA:
*		Y_test: Vector de valores alfanumericos de una distribucion categorica. Cada etiqueta corresponde a una instancia de X_test.
*
****************/
k_vecinos_proximos(X_entrenamiento, Y_entrenamiento, K, X_test, Y_test) :- print('Error. Este ejercicio no esta implementado todavia.'), !, fail.
