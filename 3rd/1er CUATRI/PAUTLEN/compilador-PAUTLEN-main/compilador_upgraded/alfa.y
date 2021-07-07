%{
#include <stdio.h>
#include <string.h>
#include "alfa.h"

int yylex();
void yyerror();
extern FILE * out;
extern int lines;
extern int cols;
extern int morf;

TIPO tipo_actual;
CLASE clase_actual;
int tamano_vector_actual;

INFO_SIMBOLO* read;

INFO_SIMBOLO inserta;

int cuantos_no=0;
int tag_potencias = 0;
int tag_factorial = 0;
int tag_comparaciones=0;
int tag_condicionales=0;
int tag_bucles=0;
int pos_variable_local_actual=0;
int num_variables_locales_actual=0;
int num_parametros_actual = 0;
int pos_parametro_actual = 0;
int es_funcion=0;
int es_llamada=0;
int params = 0;
int hay_return = 0;
int comp_tag = 0;

%}

/* Palabras reservadas */
%token TOK_MAIN
%token TOK_INT
%token TOK_BOOLEAN
%token TOK_ARRAY
%token TOK_FUNCTION
%token TOK_IF
%token TOK_ELSE
%token TOK_WHILE
%token TOK_FOR
%token TOK_SCANF
%token TOK_PRINTF
%token TOK_COMPARE
%token TOK_WITH
%token TOK_RETURN

/* Símbolos */
%token TOK_PUNTOYCOMA
%token TOK_COMA
%token TOK_PARENTESISIZQUIERDO
%token TOK_PARENTESISDERECHO
%token TOK_CORCHETEIZQUIERDO
%token TOK_CORCHETEDERECHO
%token TOK_LLAVEIZQUIERDA
%token TOK_LLAVEDERECHA
%token TOK_ASIGNACION
%token TOK_LONGITUD
%token TOK_MAS
%token TOK_MENOS
%token TOK_DIVISION
%token TOK_POTENCIA
%token TOK_FACTORIAL
%token TOK_ASTERISCO
%token TOK_MODULO
%token TOK_AND
%token TOK_OR
%token TOK_NOT
%token TOK_IGUAL
%token TOK_DISTINTO
%token TOK_MENORIGUAL
%token TOK_MAYORIGUAL
%token TOK_MENOR
%token TOK_MAYOR
%token TOK_MASIGUAL
%token TOK_MENOSIGUAL
%token TOK_PORIGUAL
%token TOK_ENTREIGUAL
%token TOK_INCREMENTO
%token TOK_DECREMENTO

%token <atributos> TOK_IDENTIFICADOR
%token <atributos> TOK_CONSTANTE_ENTERA
%token TOK_TRUE
%token TOK_FALSE

%token TOK_ERROR

%type <atributos> constante_entera
%type <atributos> constante_logica
%type <atributos> constante
%type <atributos> exp

%type <atributos> inicioCmp
%type <atributos> cmpMenor
%type <atributos> cmpIgual

%type <atributos> if_exp
%type <atributos> if_exp_sentencias

%type <atributos> while
%type <atributos> while_exp
%type <atributos> for
%type <atributos> for_1
%type <atributos> for_2
%type <atributos> for_3

%type <atributos> elemento_vector

%type <atributos> fn_name
%type <atributos> fn_declaration
%type <atributos> call_func

%left TOK_MAS TOK_MENOS TOK_OR
%left TOK_POTENCIA TOK_ASTERISCO TOK_DIVISION TOK_MODULO TOK_AND TOK_FACTORIAL 
%left TOK_ENTREIGUAL TOK_PORIGUAL TOK_MASIGUAL TOK_MENOSIGUAL TOK_INCREMENTO TOK_DECREMENTO
%right MENOSU TOK_NOT

%union {
  tipo_atributos atributos;
}
%%

programa: TOK_MAIN TOK_LLAVEIZQUIERDA declaraciones escribirTabla funciones escribirMain sentencias TOK_LLAVEDERECHA {fprintf(out, ";R1:\t<programa> ::= main { <declaraciones> <funciones> <sentencias> }\n");}
        ;

declaraciones: declaracion {fprintf(out, ";R2:\t<declaraciones> ::= <declaracion>\n");}
             | declaracion declaraciones {fprintf(out, ";R3:\t<declaraciones> ::= <declaracion> <declaraciones>\n");}
             ;

declaracion: clase identificadores TOK_PUNTOYCOMA {fprintf(out, ";R4:\t<declaracion> ::= <clase> <identificadores> ;\n");}
           ;

clase: clase_escalar {fprintf(out, ";R5:\t<clase> ::= <clase_escalar>\n");  clase_actual=ESCALAR;}
     | clase_vector {fprintf(out, ";R7:\t<clase> ::= <clase_vector>\n");  clase_actual=VECTOR;}
     ;

clase_escalar: tipo {fprintf(out, ";R9:\t<clase_escalar> ::= <tipo>\n");}
             ;

tipo: TOK_INT {tipo_actual=ENTERO; fprintf(out, ";R10:\t<tipo> ::= int\n");}
    | TOK_BOOLEAN {tipo_actual=BOOLEANO; fprintf(out, ";R11:\t<tipo> ::= boolean\n");}
    ;

clase_vector: TOK_ARRAY tipo TOK_CORCHETEIZQUIERDO constante_entera TOK_CORCHETEDERECHO {
  tamano_vector_actual = $4.valor_numerico; 
  if(tamano_vector_actual<1 || tamano_vector_actual > MAX_TAMANIO_VECTOR) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: El tamanyo del vector excede los limites permitidos (1,64).\n", lines);
    return -1;
  }
  fprintf(out, ";R15:\t<clase_vector> ::= array <tipo> [ <constante_entera> ]\n");}
            ;

identificadores: identificador {fprintf(out, ";R18:\t<identificadores> ::= <identificador>\n");}
               | identificador TOK_COMA identificadores {fprintf(out, ";R19:\t<identificadores> ::= <identificador> , <identificadores>\n");}
               ;

funciones: funcion funciones {fprintf(out, ";R20:\t<funciones> ::= <funcion> <funciones>\n");}
         | {fprintf(out, ";R21:\t<funciones> ::=\n");}
         ;

fn_name : TOK_FUNCTION tipo TOK_IDENTIFICADOR {
    hay_return = 0;
    es_funcion=1;
    read = UsoLocal($3.nombre);
    if(read != NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Declaracion duplicada.\n", lines);
      return -1;
    }

    inserta.lexema = $3.nombre;
    inserta.categoria = FUNCION;
    inserta.clase = ESCALAR; 
    inserta.tipo = tipo_actual;

    strcpy($$.nombre, $3.nombre);
    $$.tipo = tipo_actual;

    DeclararFuncion($3.nombre, &inserta);
    pos_variable_local_actual=0;
    num_variables_locales_actual=0;
    num_parametros_actual = 0;
    pos_parametro_actual = 0;
}

fn_declaration : fn_name TOK_PARENTESISIZQUIERDO parametros_funcion TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA declaraciones_funcion {
    read = UsoLocal($1.nombre);
    if(read == NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Declaracion duplicada.\n", lines);
      return -1;
    }
    read->adicional1 = num_parametros_actual;
    strcpy($$.nombre, $1.nombre);
    $$.tipo = $1.tipo;
    declararFuncion(out, $1.nombre, num_variables_locales_actual);
} 

funcion: fn_declaration sentencias TOK_LLAVEDERECHA {
  if(!hay_return) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Funcion %s sin sentencia de retorno.\n", lines, $1.nombre);
    return -1;
  }
  CerrarFuncion();
  fin_funcion(out);
  read = UsoLocal($1.nombre);
  if(read == NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Declaracion duplicada.\n", lines);
      return -1;
  }
  read->adicional1 = num_parametros_actual;
  es_funcion = 0;
  fprintf(out, ";R22:\t<funcion> ::=function <tipo> <identificador> ( <parametros_funcion> ) { <declaraciones_funcion> <sentencias> }\n");}

parametros_funcion: parametro_funcion resto_parametros_funcion {fprintf(out, ";R23:\t<parametros_funcion> ::= <parametro_funcion> <resto_parametros_funcion>\n");}
                  | {fprintf(out, ";R24:\t<parametros_funcion> ::=\n");}
                  ;

resto_parametros_funcion: TOK_PUNTOYCOMA parametro_funcion resto_parametros_funcion {fprintf(out, ";R25:\t<resto_parametros_funcion> ::= ; <parametro_funcion> <resto_parametros_funcion>\n");}
                        | {fprintf(out, ";R26:\t<resto_parametros_funcion> ::=\n");}
                        ;

parametro_funcion: tipo idpf {
  num_parametros_actual++;
  pos_parametro_actual++;
  fprintf(out, ";R27:\t<parametro_funcion> ::= <tipo> <identificador>\n");}
                 ;

idpf : TOK_IDENTIFICADOR {
    read = UsoLocal($1.nombre);
    if(read != NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Declaracion duplicada.\n", lines);
      return -1;
    }
    inserta.lexema = $1.nombre;
    inserta.categoria = PARAMETRO;
    inserta.clase = ESCALAR;
    inserta.tipo = tipo_actual;
    inserta.adicional1 = num_parametros_actual;

    Declarar($1.nombre, &inserta);
}

declaraciones_funcion: declaraciones {fprintf(out, ";R28:\t<declaraciones_funcion> ::= <declaraciones>\n");}
                     | {fprintf(out, ";R29:\t<declaraciones_funcion> ::=\n");}
                     ;

sentencias: sentencia {fprintf(out, ";R30:\t<sentencias> ::= <sentencia>\n");}
          | sentencia sentencias {fprintf(out, ";R31:\t<sentencias> ::= <sentencia> <sentencias>\n");}
          ;

sentencia: sentencia_simple TOK_PUNTOYCOMA {fprintf(out, ";R32:\t<sentencia> ::= <sentencia_simple> ;\n");}
         | bloque {fprintf(out, ";R33:\t<sentencia> ::= <bloque>\n");}
         ;

sentencia_simple: asignacion {fprintf(out, ";R34:\t<sentencia_simple> ::= <asignacion>\n");}
                | lectura {fprintf(out, ";R35:\t<sentencia_simple> ::= <lectura>\n");}
                | escritura {fprintf(out, ";R36:\t<sentencia_simple> ::= <escritura>\n");}
                | retorno_funcion {fprintf(out, ";R38:\t<sentencia_simple> ::= <retorno_funcion>\n");}
                ;

bloque: condicional {fprintf(out, ";R40:\t<bloque> ::= <condicional>\n");}
      | bucle {fprintf(out, ";R41:\t<bloque> ::= <bucle>\n");}
      | bucle_for {fprintf(out, ";R41:\t<bloque> ::= <bucle>\n");}
      ;

asignacion: TOK_IDENTIFICADOR TOK_ASIGNACION exp  {
    read = UsoLocal($1.nombre);
    if(read==NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", lines, $1.nombre);
      return -1;
    } else {
      if(read->categoria == FUNCION) {
        fprintf(ERR_OUT, "****Error semantico en lin %d: Asignacion incompatible.\n", lines);
        return -1;
      }
      if(read->clase == VECTOR) {
        fprintf(ERR_OUT, "****Error semantico en lin %d: Asignacion incompatible.\n", lines);
        return -1;
      }
      if(read->tipo != $3.tipo) {
        fprintf(ERR_OUT, "****Error semantico en lin %d: Asignacion incompatible.\n", lines);
        return -1;
  
        }
      if (UsoGlobal($1.nombre) == NULL) {
      /* Estamos en una funcion y la variable es local */
        if(read->categoria == PARAMETRO) {
          asignar_local(out, (num_parametros_actual-read->adicional1+1), $3.es_direccion?0:1);
        } else {
          asignar_local(out, -(read->adicional1+1), $3.es_direccion?0:1);
        }

      } else {
        asignar(out, $1.nombre, $3.es_direccion?1:0);
        fprintf(out, ";R43:\t<asignacion> ::= <identificador> = <exp>\n");
    }
  }
}

          | elemento_vector TOK_ASIGNACION exp {
            if($1.tipo != $3.tipo) {
              fprintf(ERR_OUT, "****Error semantico en lin %d: Asignacion incompatible.\n", lines);
              return -1;
            }
            asignarDestinoEnPila(out, $3.es_direccion?1:0);
            fprintf(out, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_INCREMENTO {
            escribir_operando_entero(out, 1, 0);
            escribir_operando(out, $1.nombre, $1.es_direccion?0:1);
            sumar(out, $1.es_direccion?1:0, 1);
            asignar(out, $1.nombre, $1.es_direccion?1:0);
           fprintf(out, ";R45:\t<asignacion> ::= <identificador> = <identificador> + <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_DECREMENTO {
            escribir_operando_entero(out, 1, 0);
            escribir_operando(out, $1.nombre, $1.es_direccion?0:1);
            restar(out, $1.es_direccion?1:0, 1);
            asignar(out, $1.nombre, $1.es_direccion?1:0);
           fprintf(out, ";R45:\t<asignacion> ::= <identificador> = <identificador> - <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_PORIGUAL exp {
           	por_igual(out, $1.nombre, 1, $3.es_direccion?1:0);
            fprintf(out, ";R45:\t<asignacion> ::= <identificador> = <identificador> + <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_ENTREIGUAL exp {
           	entre_igual(out, $1.nombre, 1, $3.es_direccion?1:0);
            fprintf(out, ";R45:\t<asignacion> ::= <identificador> = <identificador> + <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_MASIGUAL exp {
           	mas_igual(out, $1.nombre, 1, $3.es_direccion?1:0);
            fprintf(out, ";R45:\t<asignacion> ::= <identificador> = <identificador> + <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_MENOSIGUAL exp {
           	menos_igual(out, $1.nombre, 1, $3.es_direccion?1:0);
            fprintf(out, ";R45:\t<asignacion> ::= <identificador> = <identificador> + <exp>\n");}
          ;
          | TOK_IDENTIFICADOR TOK_ASIGNACION TOK_LONGITUD TOK_IDENTIFICADOR {
            read = UsoLocal($4.nombre);
            escribir_operando_entero(out, read->adicional1, 0);
            asignar(out, $1.nombre, $1.es_direccion?1:0);
            fprintf(out, ";R44:\t<asignacion> ::= <elemento_vector> = <exp>\n");}
          ;

elemento_vector: TOK_IDENTIFICADOR TOK_CORCHETEIZQUIERDO exp TOK_CORCHETEDERECHO {
  read = UsoLocal($1.nombre);
  if(read == NULL) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", lines, $1.nombre);
    return -1;
  }  
  if(read->categoria == FUNCION) { 
    fprintf(ERR_OUT,"****Error semantico en lin %d: Identificador no valido\n", lines);
    return -1;  
  }  
  if(read->clase == ESCALAR) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Intento de indexacion de una variable que no es de tipo vector.\n", lines);
    return -1;
  }
  $$.tipo = read->tipo;  
  $$.es_direccion = 1;
  if($3.tipo != ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: El indice en una operacion de indexacion tiene que ser de tipo entero.\n", lines);
    return -1;
  }

  escribir_elemento_vector(out, $1.nombre, read->adicional1, $3.es_direccion?1:0);

  fprintf(out, ";R48:\t<elemento_vector> ::= <identificador> [ <exp> ]\n");}
               ;

condicional: if_exp_sentencias TOK_LLAVEDERECHA {
  ifthenelse_fin(out, $1.etiqueta);
  fprintf(out, ";R50:\t<condicional> ::= if ( <exp> ) { <sentencias> }\n");
}
           | if_exp_sentencias TOK_LLAVEDERECHA TOK_ELSE TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
            ifthenelse_fin(out, $1.etiqueta);
            fprintf(out, ";R51:\t<condicional> ::= if ( <exp> ) { <sentencias> } else { <sentencias> }\n");}
           ;
           | cmpIgual TOK_MAYOR TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA TOK_LLAVEDERECHA{
              fprintf(out, "finCmp%d:", $1.etiqueta);
            } ;

inicioCmp: TOK_COMPARE exp TOK_WITH exp TOK_LLAVEIZQUIERDA {
  $$.etiqueta = comp_tag++;
  compare(out, $2.es_direccion?1:0, $4.es_direccion?1:0, $$.etiqueta);
}
;

cmpMenor: inicioCmp TOK_MENOR TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
  fprintf(out, "jmp finCmp%d\n", $1.etiqueta);
  fprintf(out, "cmp_igual%d:\n", $1.etiqueta);
}
;

cmpIgual: cmpMenor TOK_ASIGNACION TOK_LLAVEIZQUIERDA sentencias TOK_LLAVEDERECHA {
  fprintf(out, "jmp finCmp%d\n", $1.etiqueta);
  fprintf(out, "cmp_mayor%d:\n", $1.etiqueta);
}
;

if_exp: TOK_IF TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
    if($3.tipo != BOOLEANO) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Condicional con condicion de tipo int.\n", lines);
      return -1;
    }
    $$.etiqueta = tag_condicionales++;
    ifthen_inicio(out, $3.es_direccion?1:0, $$.etiqueta);
  }

if_exp_sentencias:  if_exp sentencias {
  $$.etiqueta = $1.etiqueta;
  ifthenelse_fin_then(out, $$.etiqueta);
}

bucle: while_exp sentencias TOK_LLAVEDERECHA {
  while_fin(out, $1.etiqueta);
  fprintf(out, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");}
     ;

while: TOK_WHILE TOK_PARENTESISIZQUIERDO {
  $$.etiqueta = tag_bucles++;
  while_inicio(out, $$.etiqueta);
}

while_exp: while exp TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA {
  if($2.tipo != BOOLEANO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Bucle con condicion de tipo int.\n", lines);
    return -1;
  }

  $$.etiqueta = $1.etiqueta;
  while_exp_pila(out, $2.es_direccion?1:0, $$.etiqueta);
};

bucle_for: for_3 sentencias TOK_LLAVEDERECHA {
  for_fin(out, $1.etiqueta);
  fprintf(out, ";R52:\t<bucle> ::= while ( <exp> ) { <sentencias> }\n");}
     ;

for: TOK_FOR TOK_PARENTESISIZQUIERDO {
}

for_1: for sentencia {
  $$.etiqueta = tag_bucles++;
  for_inicio(out, $$.etiqueta);
};

for_2: for_1 exp {
  for_exp_pila(out, $2.es_direccion?1:0, $$.etiqueta);
};

for_3: for_2 sentencia TOK_PARENTESISDERECHO TOK_LLAVEIZQUIERDA{ 
  $$.etiqueta = $1.etiqueta;
};

lectura: TOK_SCANF TOK_IDENTIFICADOR {
    read = UsoLocal($2.nombre);
    if(read == NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", lines, $2.nombre);
      return -1;
    }
    leer(out, $2.nombre, read->tipo); 
    fprintf(out, ";R54:\t<lectura> ::= scanf <identificador>\n");
};

escritura: TOK_PRINTF exp {
	fprintf(out, ";R56:\t<escritura> ::= printf <exp>\n");
	escribir(out, $2.es_direccion, ($2.tipo));}
         ;

retorno_funcion: TOK_RETURN exp {
  if(!es_funcion) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Sentencia de retorno fuera del cuerpo de una funcion.\n", lines);
    return -1;
  }

  hay_return = 1;
  retornarFuncion(out, $2.es_direccion?1:0);
  fprintf(out, ";R61:\t<retorno_funcion> ::= return <exp>\n");}
               ;

exp: exp TOK_MAS exp {
  if($1.tipo==BOOLEANO && $3.tipo == BOOLEANO) {
    o(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
    $$.es_direccion = 0;
    $$.tipo = BOOLEANO;
  }

  if($1.tipo==ENTERO && $3.tipo == ENTERO) {
    sumar(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
    $$.es_direccion = 0;
    $$.tipo = ENTERO;
  }

  fprintf(out, ";R72:\t<exp> ::= <exp> + <exp>\n");
}

   | exp TOK_MENOS exp {
  if($1.tipo!=ENTERO || $3.tipo != ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", lines);
    return -1;
  }
  $$.tipo = ENTERO;
  restar(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
  $$.es_direccion = 0;
    fprintf(out, ";R73:\t<exp> ::= <exp> - <exp>\n");
}

   | exp TOK_DIVISION exp {
  if($1.tipo!=ENTERO || $3.tipo != ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", lines);
    return -1;
  }
  $$.tipo = ENTERO;
  dividir(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
  $$.es_direccion = 0;
    fprintf(out, ";R74:\t<exp> ::= <exp> / <exp>\n");
}
  | exp TOK_MODULO exp {
  if($1.tipo!=ENTERO || $3.tipo != ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", lines);
    return -1;
  }
  $$.tipo = ENTERO;
  modulo(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
  $$.es_direccion = 0;
    fprintf(out, ";R74:\t<exp> ::= <exp> modulo <exp>\n");
}

   | exp TOK_ASTERISCO exp {
  if($1.tipo == ENTERO || $3.tipo == ENTERO) {
    $$.tipo = ENTERO;
    multiplicar(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
    $$.es_direccion = 0;
  }

  if($1.tipo == BOOLEANO || $3.tipo == BOOLEANO) {
    $$.tipo = BOOLEANO;
    y(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
    $$.es_direccion = 0;
  }
  
    fprintf(out, ";R75:\t<exp> ::= <exp> * <exp>\n");
}
  | exp TOK_POTENCIA exp {
  if($1.tipo!=ENTERO || $3.tipo != ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", lines);
    return -1;
  }
  $$.tipo = ENTERO;
  $$.etiqueta = tag_potencias++;
  potencia(out, $1.es_direccion?1:0, $3.es_direccion?1:0, $$.etiqueta);
  $$.es_direccion = 0;
    fprintf(out, ";R75:\t<exp> ::= <exp> ^ <exp>\n");
}

| TOK_FACTORIAL exp {
  if($2.tipo!=ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", lines);
    return -1;
  }
  $$.tipo = ENTERO;
  $$.etiqueta = tag_factorial++;
  factorial(out, $2.es_direccion?1:0, $$.etiqueta);
  $$.es_direccion = 0;
  fprintf(out, ";R75:\t<exp> ::= <exp> ^ <exp>\n");
}

   | TOK_MENOS exp %prec MENOSU {
    if($2.tipo!=ENTERO) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion aritmetica con operandos boolean.\n", lines);
      return -1; 
    }
    $$.tipo = ENTERO;
    cambiar_signo(out, $2.es_direccion?1:0);
    $$.es_direccion = 0;
    fprintf(out, ";R76:\t<exp> ::= - <exp>\n");
}
   | exp TOK_AND exp {
    if($1.tipo!=BOOLEANO || $3.tipo != BOOLEANO) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion logica con operandos int.\n", lines);
      return -1;
    }
    $$.tipo = BOOLEANO;
    y(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
    $$.es_direccion = 0;
    fprintf(out, ";R77:\t<exp> ::= <exp> && <exp>\n");
}
   | exp TOK_OR exp {
    if($1.tipo!=BOOLEANO || $3.tipo != BOOLEANO) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion logica con operandos int.\n", lines);
      return -1;
    }
    $$.tipo = BOOLEANO;
    o(out, $1.es_direccion?1:0, $3.es_direccion?1:0);
    $$.es_direccion = 0;
    fprintf(out, ";R77:\t<exp> ::= <exp> && <exp>\n");
    fprintf(out, ";R78:\t<exp> ::= <exp> || <exp>\n");
  }
   | TOK_NOT exp {
    if($2.tipo!=BOOLEANO) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Operacion logica con operandos int.\n", lines);
      return -1;
    }
    $$.tipo = BOOLEANO;
    no(out, $2.es_direccion?1:0, cuantos_no++);
    $$.es_direccion = 0;
    fprintf(out, ";R79:\t<exp> ::= ! <exp>\n");
}
   | TOK_IDENTIFICADOR {
    strcpy($$.nombre, $1.nombre);
    read = UsoLocal($1.nombre);
    if(read == NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Acceso a variable no declarada (%s).\n", lines, $1.nombre);
      return -1;
    }
    if (UsoGlobal($1.nombre) == NULL) {
      /* Estamos en una funcion y la variable es local */
      if(read->categoria == PARAMETRO) {
        escribir_operando_funcion(out, (num_parametros_actual-read->adicional1)+1);
      } else {
        escribir_operando_funcion(out, -(read->adicional1+1));
      }

    } else {
      if(read->categoria==FUNCION) {
        fprintf(ERR_OUT,"Identificador no valido\n");
        return -1;
    }
    
    escribir_operando(out, $1.nombre, 1);

    }
    $$.es_direccion = 1;
    $$.tipo = read->tipo;

    fprintf(out, ";R80:\t<exp> ::= <identificador>\n");

  }
   | constante {
    $$.tipo =$1.tipo;
    $$.es_direccion = $1.es_direccion;
    escribir_operando(out, $1.nombre, 0);
    fprintf(out, ";R81:\t<exp> ::= <constante>\n");}

   | TOK_PARENTESISIZQUIERDO exp TOK_PARENTESISDERECHO {
    $$.tipo =$2.tipo;
    $$.es_direccion = $2.es_direccion;
    fprintf(out, ";R82:\t<exp> ::= ( <exp> )\n");}

   | TOK_PARENTESISIZQUIERDO comparacion TOK_PARENTESISDERECHO {
    $$.tipo =BOOLEANO;
    $$.es_direccion = 0;
    fprintf(out, ";R82:\t<exp> ::= ( <exp> )\n");
    fprintf(out, ";R83:\t<exp> ::= ( <comparacion> )\n");}
    
   | elemento_vector {fprintf(out, ";R85:\t<exp> ::= <elemento_vector>\n");}
   ;

   | call_func lista_expresiones TOK_PARENTESISDERECHO {
    read = UsoLocal($1.nombre);
    if(read == NULL) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Funcion no declarada (%s).\n", lines, $1.nombre);
      return -1;
    }
    if(read->categoria != FUNCION){
      fprintf(ERR_OUT, "****Error semantico en lin %d: El identificador no es una funcion (%s).\n", lines, $1.nombre);
      return -1;
    }
    if(read->adicional1 != params) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Numero incorrecto de parametros en llamada a funcion.\n", lines);
      return -1;
    }
    es_llamada = 0;
    $$.tipo = read->tipo;
    llamarFuncion(out, $1.nombre, read->adicional1);

    fprintf(out, ";R88:\t<exp> ::= <identificador> ( <lista_expresiones> )\n");}
   ;

call_func: TOK_IDENTIFICADOR TOK_PARENTESISIZQUIERDO {
  if(es_llamada) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: No esta permitido el uso de llamadas a funciones como parametros de otras funciones.\n", lines);
    return -1;
  }
  es_llamada = 1;
  params = 0;
  strcpy($$.nombre, $1.nombre);
}

lista_expresiones: expf resto_lista_expresiones {
  es_llamada = 0;
  params++;
  
  fprintf(out, ";R89:\t<lista_expresiones> ::= <exp> <resto_lista_expresiones>\n");}
                 |   {
                  es_llamada = 0;
                  fprintf(out, ";R90:\t<lista_expresiones> ::=\n");}
                 ;

resto_lista_expresiones: TOK_COMA expf resto_lista_expresiones {
  params++;

  fprintf(out, ";R91:\t<resto_lista_expresiones> ::= , <exp> <resto_lista_expresiones>\n");}
                       |   {fprintf(out, ";R92:\t<resto_lista_expresiones> ::=\n");}
                       ;
expf: exp {
  if($1.es_direccion) {
    operandoEnPilaAArgumento(out, 1);
  }
}


comparacion: exp TOK_IGUAL exp {
  if($1.tipo != ENTERO || $3.tipo != ENTERO) {
    fprintf(ERR_OUT, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", lines);
    return -1;
  }
  igual(out, $1.es_direccion?1:0, $3.es_direccion?1:0, tag_comparaciones++);
  fprintf(out, ";R93:\t<comparacion> ::= <exp> == <exp>\n");
}
           | exp TOK_DISTINTO exp {
            if($1.tipo != ENTERO || $3.tipo != ENTERO) {
              fprintf(ERR_OUT, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", lines);
              return -1;
            }
            distinto(out, $1.es_direccion?1:0, $3.es_direccion?1:0, tag_comparaciones++); 
            fprintf(out, ";R94:\t<comparacion> ::= <exp> != <exp>\n");
            }
           | exp TOK_MENORIGUAL exp {
            if($1.tipo != ENTERO || $3.tipo != ENTERO) {
              fprintf(ERR_OUT, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", lines);
              return -1;
            }
            menor_igual(out, $1.es_direccion?1:0, $3.es_direccion?1:0, tag_comparaciones++);
            fprintf(out, ";R95:\t<comparacion> ::= <exp> <= <exp>\n");}
           | exp TOK_MAYORIGUAL exp {
            if($1.tipo != ENTERO || $3.tipo != ENTERO) {
              fprintf(ERR_OUT, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", lines);
              return -1;
            }
            mayor_igual(out, $1.es_direccion?1:0, $3.es_direccion?1:0, tag_comparaciones++);
            fprintf(out, ";R96:\t<comparacion> ::= <exp> >= <exp>\n");}
           | exp TOK_MENOR exp {
            if($1.tipo != ENTERO || $3.tipo != ENTERO) {
              fprintf(ERR_OUT, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", lines);
              return -1;
            }
            menor(out, $1.es_direccion?1:0, $3.es_direccion?1:0, tag_comparaciones++);
            fprintf(out, ";R97:\t<comparacion> ::= <exp> < <exp>\n");}
           | exp TOK_MAYOR exp {
            if($1.tipo != ENTERO || $3.tipo != ENTERO) {
              fprintf(ERR_OUT, "****Error semantico en lin %d: Comparacion con operandos boolean.\n", lines);
              return -1;
            }
            mayor(out, $1.es_direccion?1:0, $3.es_direccion?1:0, tag_comparaciones++);
            fprintf(out, ";R98:\t<comparacion> ::= <exp> > <exp>\n");}
           ;

constante: constante_entera {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; strcpy($$.nombre, $1.nombre); fprintf(out, ";R99:\t<constante> ::= <constante_logica>\n");}
         | constante_logica {$$.tipo = $1.tipo; $$.es_direccion = $1.es_direccion; strcpy($$.nombre, $1.nombre); fprintf(out, ";R100:\t<constante> ::= <constante_entera>\n");}
         ;

constante_logica: TOK_TRUE {$$.tipo = BOOLEANO; $$.es_direccion = 0; strcpy($$.nombre,"1"); fprintf(out, ";R102:\t<constante_logica> ::= true\n");}
                | TOK_FALSE {$$.tipo = BOOLEANO; $$.es_direccion = 0; strcpy($$.nombre,"0"); fprintf(out, ";R103:\t<constante_logica> ::= false\n");}
                ;

constante_entera: TOK_CONSTANTE_ENTERA { $$.tipo = ENTERO; $$.es_direccion = 0; 
                  fprintf(out, ";R104:\t<constante_entera> ::= <numero>\n");}
                ;
identificador: TOK_IDENTIFICADOR {
    read = UsoLocal($1.nombre);
    if((read != NULL && !es_funcion) || (read != NULL && EsLocal($1.nombre)) ) {
      fprintf(ERR_OUT, "****Error semantico en lin %d: Declaracion duplicada.\n", lines);
      return -1;
    }

    inserta.lexema = $1.nombre;
    inserta.categoria = VARIABLE;
    inserta.clase = clase_actual;
    inserta.tipo = tipo_actual;
    if(clase_actual == VECTOR) {
      inserta.adicional1 = tamano_vector_actual;

    } else {
      inserta.adicional1 = 1;
    }
    if(es_funcion) {
      if(clase_actual == VECTOR) {
        fprintf(ERR_OUT, "****Error semantico en lin %d: Variable local de tipo no escalar.\n", lines);
        return -1;
      }
      inserta.adicional1 = num_variables_locales_actual;
      num_variables_locales_actual++;
      pos_variable_local_actual++;
    } else {
      declarar_variable(out, $1.nombre, tipo_actual,  inserta.adicional1);
        
    }
    Declarar($1.nombre, &inserta);


    fprintf(out, ";R108:\t<identificador> ::= TOK_IDENTIFICADOR\n");}
             ;

    escribirTabla: { escribir_segmento_codigo(out); }

    escribirMain: { escribir_inicio_main(out);}
%%

void yyerror(const char * s) {
    if(!morf) {
        printf("****Error sintactico en [lin %d, col %d]\n", lines, cols);
    }
}