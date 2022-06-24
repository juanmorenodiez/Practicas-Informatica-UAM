#include "generacion.h"

void escribir_cabecera_bss(FILE* fpasm) {
  fprintf(fpasm, "segment .bss\n__esp    resd 1 \n");
}

void escribir_subseccion_data(FILE* fpasm) {
  fprintf(fpasm, "segment .data \n");
  fprintf(fpasm, "msg_error_division db 'Division por cero', 0\n");
  fprintf(fpasm, "msg_error_indice_vector db 'Indice de vector fuera de rango', 0\n");
}

void declarar_variable(FILE* fpasm, char * nombre, int tipo, int tamano) {
  fprintf(fpasm, "_%s resd %d \n", nombre, tamano);
}

void escribir_segmento_codigo(FILE* fpasm) {
  fprintf(fpasm, "segment .text\n");
  fprintf(fpasm, "\tglobal main\n");
  fprintf(fpasm, "\textern print_string, print_endofline, scan_int, print_int, scan_boolean, print_boolean\n");
}

void escribir_inicio_main(FILE* fpasm) {
  fprintf(fpasm, "main:\n");
  fprintf(fpasm, "\tmov dword [__esp], esp\n");
}

void escribir_fin(FILE* fpasm) {
  fprintf(fpasm, "\tjmp near fin\n");
  fprintf(fpasm, "\tfin_error_division:\n");
  fprintf(fpasm, "\tpush dword msg_error_division\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");
  fprintf(fpasm, "\tjmp near fin\n");
  fprintf(fpasm, "\tfin_indice_fuera_rango:\n");
  fprintf(fpasm, "\tpush dword msg_error_indice_vector\n");
  fprintf(fpasm, "\tcall print_string\n");
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");
  fprintf(fpasm, "\tjmp near fin\n");
  fprintf(fpasm, "fin:\n");
  fprintf(fpasm, "\tmov dword esp, [__esp]\n");
  fprintf(fpasm, "\tret");
}

void escribir_operando(FILE* fpasm, char* nombre, int es_variable) {
  if (es_variable == 1) {
    fprintf(fpasm, "\tpush dword _%s\n", nombre);
  }
  else {
    fprintf(fpasm, "\tpush dword %s\n", nombre);
  }
}

void escribir_operando_entero(FILE* fpasm, int entero, int es_variable) {
  if (es_variable == 1) {
    fprintf(fpasm, "\tpush dword _%d\n", entero);
  }
  else {
    fprintf(fpasm, "\tpush dword %d\n", entero);
  }
}

void asignar(FILE* fpasm, char* nombre, int es_variable) {
  if (es_variable == 1) {
    fprintf(fpasm, "\tpop dword eax\n");
    fprintf(fpasm, "\tmov eax, dword [eax]\n");
    fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
  }
  else {
    fprintf(fpasm, "\tpop dword eax\n");
    fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
  }
}

void sumar(FILE* fpasm, int es_variable_1, int es_variable_2) {
  	fprintf(fpasm, "\tpop ebx\n");
  	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tadd eax, ebx\n");

  	fprintf(fpasm, "\tpush dword eax\n");
}

void mas_igual(FILE* fpasm, char* nombre, int es_variable_1, int es_variable_2){
	if (es_variable_1 == 1) {
    	fprintf(fpasm, "\tpush dword _%s\n", nombre);
  	}
  	else {
    	fprintf(fpasm, "\tpush dword %s\n", nombre);
  	}

	fprintf(fpasm, "\tpop eax\n");
  	fprintf(fpasm, "\tpop ebx\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tadd eax, ebx\n");
	fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
	
}

void menos_igual(FILE* fpasm, char* nombre, int es_variable_1, int es_variable_2){
	if (es_variable_1 == 1) {
    	fprintf(fpasm, "\tpush dword _%s\n", nombre);
  	}
  	else {
    	fprintf(fpasm, "\tpush dword %s\n", nombre);
  	}

	fprintf(fpasm, "\tpop ebx\n");
  	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tsub eax, ebx\n");
	fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
	
}

void por_igual(FILE* fpasm,char* nombre, int es_variable_1, int es_variable_2){
	if (es_variable_1 == 1) {
    	fprintf(fpasm, "\tpush dword _%s\n", nombre);
  	}
  	else {
    	fprintf(fpasm, "\tpush dword %s\n", nombre);
  	}

	fprintf(fpasm, "\tpop ebx\n");
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\timul ebx\n");
	fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
}

void entre_igual(FILE* fpasm, char *nombre, int es_variable_1, int es_variable_2) {
	if (es_variable_1 == 1) {
    	fprintf(fpasm, "\tpush dword _%s\n", nombre);
  	}
  	else {
    	fprintf(fpasm, "\tpush dword %s\n", nombre);
  	}

	fprintf(fpasm, "\tpop ebx\n");
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "cmp ebx, 0\n");
	fprintf(fpasm, "je near fin_error_division\n");

  	fprintf(fpasm, "\tmov edx, 0\n");
	fprintf(fpasm, "\tidiv ebx\n");
	fprintf(fpasm, "\tmov dword [_%s], eax\n", nombre);
}

void incremento(FILE* fpasm, char* nombre, int es_variable_1) {
	if (es_variable_1 == 1) {
		fprintf(fpasm, "\tpush dword _%s\n", nombre);
  	}

  	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	fprintf(fpasm, "\tadd eax, 1\n");
  	fprintf(fpasm, "\tpush dword eax\n");
}

void decremento(FILE* fpasm, char* nombre, int es_variable_1) {
	if (es_variable_1 == 1) {
		fprintf(fpasm, "\tpush dword _%s\n", nombre);
  	}

  	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	fprintf(fpasm, "\tdec eax\n");
  	fprintf(fpasm, "\tpush dword eax\n");
}

void restar(FILE* fpasm, int es_variable_1, int es_variable_2) {
  fprintf(fpasm, "\tpop ebx\n");
  fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tsub eax, ebx\n");

  	fprintf(fpasm, "\tpush dword eax\n");
}

void multiplicar(FILE* fpasm, int es_variable_1, int es_variable_2){
	fprintf(fpasm, "\tpop ebx\n");
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\timul ebx\n");

	fprintf(fpasm, "\tpush dword eax\n");
}

void dividir(FILE* fpasm, int es_variable_1, int es_variable_2) {
	fprintf(fpasm, "\tpop ebx\n");
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "cmp ebx, 0\n");
	fprintf(fpasm, "je near fin_error_division\n");

  	fprintf(fpasm, "\tmov edx, 0\n");
	fprintf(fpasm, "\tidiv ebx\n");
	fprintf(fpasm, "\tpush dword eax\n");
}

void potencia(FILE* fpasm, int es_variable_1, int es_variable_2, int etiqueta) {
	fprintf(fpasm, "\tpop ebx\n");
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp ebx, 0\n");
	fprintf(fpasm, "\tje elevado0%d\n", etiqueta);
	fprintf(fpasm, "\tcmp ebx, 1\n");
	fprintf(fpasm, "\tje elevado1%d\n", etiqueta);
	fprintf(fpasm, "\tmov ecx, eax\n");
	fprintf(fpasm, "potencia%d:\n", etiqueta);
	fprintf(fpasm, "\timul ecx\n");
	fprintf(fpasm, "\tdec ebx\n");
	fprintf(fpasm, "\tcmp ebx, 1\n");
	fprintf(fpasm, "\tjne potencia%d\n", etiqueta);
	fprintf(fpasm, "\tjmp finished%d\n", etiqueta);
	fprintf(fpasm, "elevado0%d:\n", etiqueta);
	fprintf(fpasm, "\tmov eax, 1\n");
	fprintf(fpasm, "\tjmp finished%d\n", etiqueta);
	fprintf(fpasm, "elevado1%d:\n", etiqueta);
	fprintf(fpasm, "finished%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword eax\n");
}

void factorial(FILE* fpasm, int es_variable_1, int etiqueta){
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	fprintf(fpasm, "\tcmp eax, 0\n");
	fprintf(fpasm, "\tje factorial0%d\n", etiqueta);
	fprintf(fpasm, "\tcmp eax, 1\n");
	fprintf(fpasm, "\tje factorial1%d\n", etiqueta);
	fprintf(fpasm, "\tmov ebx, eax\n");
	fprintf(fpasm, "factorial%d:\n", etiqueta);
	fprintf(fpasm, "\tdec ebx\n");
	fprintf(fpasm, "\timul ebx\n");
	fprintf(fpasm, "\tcmp ebx, 1\n");
	fprintf(fpasm, "\tjne factorial%d\n", etiqueta);
	fprintf(fpasm, "factorial1%d:\n", etiqueta);
	fprintf(fpasm, "factorial0%d:\n", etiqueta);
	fprintf(fpasm, "fin_factorial%d:\n", etiqueta);
	fprintf(fpasm, "\tpush dword eax\n");
}

void modulo(FILE* fpasm, int es_variable_1, int es_variable_2) {
	fprintf(fpasm, "\tpop ebx\n");
	fprintf(fpasm, "\tpop eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "cmp ebx, 0\n");
	fprintf(fpasm, "je near fin_error_division\n");

  	fprintf(fpasm, "\tmov edx, 0\n");
	fprintf(fpasm, "\tidiv ebx\n");
	fprintf(fpasm, "\tpush dword edx\n");
}


void o(FILE* fpasm, int es_variable_1, int es_variable_2){
	fprintf(fpasm, "\tpop dword edx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov edx, [edx]\n");
	}

	fprintf(fpasm, "\tor eax, edx\n");
	fprintf(fpasm, "\tpush dword eax\n");

}

void y(FILE* fpasm, int es_variable_1, int es_variable_2) {
	fprintf(fpasm, "\tpop dword edx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable_1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable_2 == 1){
		fprintf(fpasm, "\tmov edx, [edx]\n");
	}

	fprintf(fpasm, "\tand eax, edx\n");
	fprintf(fpasm, "\tpush dword eax\n");
}

void cambiar_signo(FILE* fpasm, int es_variable){
	fprintf(fpasm, "\tpop dword eax\n");

  if (es_variable == 1) {
    fprintf(fpasm, "\tmov eax, dword [eax]\n");
  }
	fprintf(fpasm, "\tneg eax\n");
	fprintf(fpasm, "\tpush dword eax\n");
}

void no(FILE* fpasm, int es_variable, int cuantos_no){
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable == 1){
		fprintf(fpasm, "\tmov eax, dword [eax]\n");
	}

  fprintf(fpasm, "\tcmp eax, 1\n");
  fprintf(fpasm, "\tje cambia_1_%d\n", cuantos_no);
  fprintf(fpasm, "\tmov eax, 1\n");
  fprintf(fpasm, "\tjmp a2_%d\n", cuantos_no);
  fprintf(fpasm, "\tcambia_1_%d:\n", cuantos_no);
  fprintf(fpasm, "\tmov eax, 0\n");
  fprintf(fpasm, "\ta2_%d:\n", cuantos_no);
  fprintf(fpasm, "\tpush dword eax\n");
}

void igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tje true%d\n", etiqueta);
	fprintf(fpasm, "\tmov eax, 0\n");
	fprintf(fpasm, "\tjmp false%d\n", etiqueta);
	fprintf(fpasm, "\ttrue%d: \n", etiqueta);
	fprintf(fpasm, "\tmov eax, 1\n");
	fprintf(fpasm, "\tfalse%d: \n", etiqueta);
	fprintf(fpasm, "\tpush eax\n");
}
void distinto(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tje false%d\n", etiqueta);
	fprintf(fpasm, "\tpush 1\n");
	fprintf(fpasm, "\tjmp true%d\n", etiqueta);
	fprintf(fpasm, "\tfalse%d: \n", etiqueta);
	fprintf(fpasm, "\tpush 0\n");
	fprintf(fpasm, "\ttrue%d: \n", etiqueta);

}
void menor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tjle true%d\n", etiqueta);
	fprintf(fpasm, "\tmov eax, 0\n");
	fprintf(fpasm, "\tjmp false%d\n", etiqueta);
	fprintf(fpasm, "\ttrue%d: \n", etiqueta);
	fprintf(fpasm, "\tmov eax, 1\n");
	fprintf(fpasm, "\tfalse%d: \n", etiqueta);
	fprintf(fpasm, "\tpush eax\n");
}
void mayor_igual(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tjge true%d\n", etiqueta);
	fprintf(fpasm, "\tmov eax, 0\n");
	fprintf(fpasm, "\tjmp false%d\n", etiqueta);
	fprintf(fpasm, "\ttrue%d: \n", etiqueta);
	fprintf(fpasm, "\tmov eax, 1\n");
	fprintf(fpasm, "\tfalse%d: \n", etiqueta);
	fprintf(fpasm, "\tpush eax\n");
}
void menor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tjl true%d\n", etiqueta);
	fprintf(fpasm, "\tmov eax, 0\n");
	fprintf(fpasm, "\tjmp false%d\n", etiqueta);
	fprintf(fpasm, "\ttrue%d: \n", etiqueta);
	fprintf(fpasm, "\tmov eax, 1\n");
	fprintf(fpasm, "\tfalse%d: \n", etiqueta);
  	fprintf(fpasm, "\tpush eax\n");

}
void mayor(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta){
	fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tjg true%d\n", etiqueta);
	fprintf(fpasm, "\tmov eax, 0\n");
	fprintf(fpasm, "\tjmp false%d\n", etiqueta);
	fprintf(fpasm, "\ttrue%d: \n", etiqueta);
	fprintf(fpasm, "\tmov eax, 1\n");
	fprintf(fpasm, "\tfalse%d: \n", etiqueta);
	fprintf(fpasm, "\tpush eax\n");
}

void leer(FILE* fpasm, char* nombre, int tipo){
	fprintf(fpasm, "\tpush _%s\n", nombre);

	if(tipo == 0){
		fprintf(fpasm, "\tcall scan_int\n");
	}
	if (tipo == 1) {
		fprintf(fpasm, "\tcall scan_boolean\n");
	}
    fprintf(fpasm, "\tadd esp, 4\n");
}

void escribir(FILE* fpasm, int es_variable, int tipo){
	if (es_variable == 1) {
		fprintf(fpasm, "\tpop eax\n");
    fprintf(fpasm, "\tpush dword [eax]\n");
	}

	if (tipo == 0){
		fprintf(fpasm, "\tcall print_int\n");
	}

	if (tipo == 1) {
		fprintf(fpasm, "\tcall print_boolean\n");
	}
  fprintf(fpasm, "\tadd esp, 4\n");
  fprintf(fpasm, "\tcall print_endofline\n");
}

void ifthenelse_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
	fprintf(fpasm,"\tpop eax\n");

	if(exp_es_variable == 1){
		fprintf(fpasm,"\tmov eax, [eax]\n");
	}

	fprintf(fpasm,"\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_then%d\n", etiqueta);

}

void ifthen_inicio(FILE * fpasm, int exp_es_variable, int etiqueta){
	fprintf(fpasm,"\tpop eax\n");

	if(exp_es_variable == 1){
		fprintf(fpasm,"\tmov eax, [eax]\n");
	}

	fprintf(fpasm,"\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near fin_then%d\n", etiqueta);
}

void ifthen_fin(FILE * fpasm, int etiqueta){
	fprintf(fpasm, "\tfin_then%d:\n", etiqueta);
}

void ifthenelse_fin_then( FILE * fpasm, int etiqueta){
	fprintf(fpasm, "\tjmp near fin_ifelse%d\n", etiqueta);

	fprintf(fpasm, "\tfin_then%d:\n", etiqueta);
}

void ifthenelse_fin( FILE * fpasm, int etiqueta){
	fprintf(fpasm, "\tfin_ifelse%d:\n", etiqueta);
}

void while_inicio(FILE * fpasm, int etiqueta){
	fprintf(fpasm, "\twhile%d:\n", etiqueta);
}

void for_inicio(FILE * fpasm, int etiqueta){
	fprintf(fpasm, "for%d:\n", etiqueta);
}

void while_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta){
	fprintf(fpasm,"\tpop eax\n");

	if(exp_es_variable > 0){
		fprintf(fpasm,"\tmov eax, [eax]\n");
	}

	fprintf(fpasm,"\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near while_fin%d\n", etiqueta);
}

void for_exp_pila (FILE * fpasm, int exp_es_variable, int etiqueta){
	fprintf(fpasm,"\tpop eax\n");

	if(exp_es_variable > 0){
		fprintf(fpasm,"\tmov eax, [eax]\n");
	}

	fprintf(fpasm,"\tcmp eax, 0\n");
	fprintf(fpasm, "\tje near for_fin%d\n", etiqueta);
}

void while_fin( FILE * fpasm, int etiqueta){
	fprintf(fpasm, "\tjmp near while%d\n", etiqueta);
	fprintf(fpasm, "\twhile_fin%d:\n", etiqueta);
}

void for_fin( FILE * fpasm, int etiqueta){
	fprintf(fpasm, "\tjmp near for%d\n", etiqueta);
	fprintf(fpasm, "for_fin%d:\n", etiqueta);
}

void escribir_elemento_vector(FILE * fpasm, char * nombre_vector, int tam_max, int exp_es_direccion) {
  fprintf(fpasm, "\tpop dword eax\n");

	if (exp_es_direccion == 1) {
   	fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

  fprintf(fpasm, "\tcmp eax, 0\n");
  fprintf(fpasm, "\tjl near fin_indice_fuera_rango\n");
  fprintf(fpasm, "\tcmp eax, %d\n", tam_max - 1);
  fprintf(fpasm, "\tjg near fin_indice_fuera_rango\n");
  fprintf(fpasm, "\tmov dword edx, _%s\n", nombre_vector);
  fprintf(fpasm, "\tlea eax, [edx + eax*4]\n");
  fprintf(fpasm, "\tpush dword eax\n");
}

void declararFuncion(FILE * fd_asm, char * nombre_funcion, int num_var_loc) {
  fprintf(fd_asm, "\t_%s:\n", nombre_funcion);
  fprintf(fd_asm, "\tpush ebp\n");
	fprintf(fd_asm, "\tmov ebp, esp\n");
	fprintf(fd_asm, "\tsub esp, %d\n", 4*num_var_loc);
}

void retornarFuncion(FILE * fd_asm, int es_variable) {
  fprintf(fd_asm, "\tpop eax\n");

  if (es_variable == 1) {
    fprintf(fd_asm, "\tmov dword eax, [eax]\n");
  }

  fprintf(fd_asm, "\tmov esp, ebp\n");
  fprintf(fd_asm, "\tpop ebp\n");
  fprintf(fd_asm, "\tret\n");
}

void escribirParametro(FILE* fpasm, int pos_parametro, int num_total_parametros) {
  int d_ebp;
  d_ebp = 4 * (1 + (num_total_parametros - pos_parametro));
  fprintf(fpasm, "\tlea eax,[ebp + %d]\n", d_ebp);
  fprintf(fpasm, "\tpush dword eax\n");
}

void escribirVariableLocal(FILE* fpasm, int posicion_variable_local) {
  int d_ebp;
  d_ebp = 4 * posicion_variable_local;
  fprintf(fpasm, "\tlea eax,[ebp - %d]\n", d_ebp);
  fprintf(fpasm, "\tpush dword eax\n");
}

void asignarDestinoEnPila(FILE* fpasm, int es_variable) {
	fprintf(fpasm, "\tpop dword eax\n");

	if (es_variable == 1) {
    fprintf(fpasm, "\tmov dword eax, [eax]\n");
  }

	fprintf(fpasm, "\tpop dword ebx\n");

	fprintf(fpasm, "\tmov dword [ebx], eax\n");
}

void operandoEnPilaAArgumento(FILE * fd_asm, int es_variable) {
  if (es_variable == 1) {
    fprintf(fd_asm, "\tpop eax\n");
    fprintf(fd_asm, "\tmov eax, [eax]\n");
    fprintf(fd_asm, "\tpush eax\n");
  }
}

void llamarFuncion(FILE * fd_asm, char * nombre_funcion, int num_argumentos) {
  fprintf(fd_asm, "\tcall _%s\n", nombre_funcion);
  fprintf(fd_asm, "\tadd esp, %d*4\n", num_argumentos);
  fprintf(fd_asm, "\tpush dword eax\n");

}

void asignar_local(FILE * fpasm, int n_local, int es_inmediato)
{
	fprintf(fpasm, "pop dword eax\n");
	fprintf(fpasm, "mov dword [ebp+%d], %s\n", n_local*4, es_inmediato? "eax" : "[eax]");

}

void escribir_operando_funcion(FILE* fpasm, int n_parametro) {
	fprintf(fpasm, "mov dword eax, ebp\n");
	fprintf(fpasm, "add eax, %d\n", 4*n_parametro);
	fprintf(fpasm, "push dword eax\n");
}

void compare(FILE* fpasm, int es_variable1, int es_variable2, int etiqueta) {
    fprintf(fpasm, "\tpop dword ebx\n");
	fprintf(fpasm, "\tpop dword eax\n");

	if(es_variable1 == 1){
		fprintf(fpasm, "\tmov eax, [eax]\n");
	}

	if(es_variable2 == 1){
		fprintf(fpasm, "\tmov ebx, [ebx]\n");
	}

	fprintf(fpasm, "\tcmp eax, ebx\n");
	fprintf(fpasm, "\tjl cmp_menor%d\n", etiqueta);
	fprintf(fpasm, "\tje cmp_igual%d\n", etiqueta);
	fprintf(fpasm, "\tjmp cmp_mayor%d\n", etiqueta);
	fprintf(fpasm, "\tcmp_menor%d:\n", etiqueta);
}

void fin_funcion(FILE* fpasm) {
    fprintf(fpasm, "mov eax, 0\n");
    fprintf(fpasm, "mov esp, ebp\n");
    fprintf(fpasm, "pop ebp\n");
    fprintf(fpasm, "ret\n");
}