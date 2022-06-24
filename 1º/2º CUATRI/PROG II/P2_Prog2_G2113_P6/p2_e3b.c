#include <stdio.h>
#include "elestack.h"
#include "stack_fp.h"

double mediaEnteros(Stack *ps) {
  Stack *aux = NULL;
  EleStack *ele = NULL;
  int suma=0;
  double media, cont=0;

  if (ps == NULL) {
    return -1;
  }

  aux = stack_ini((P_stack_ele_destroy)EleStack_destroy, (P_stack_ele_copy)EleStack_copy, (P_stack_ele_print)EleStack_print);

  if (aux == NULL) {
    return -1;
  }

  while(stack_isEmpty(ps) == FALSE) {
    cont++;
    ele = stack_pop(ps);
    suma += *(int*)EleStack_getInfo(ele);
    stack_push(aux, ele);
    EleStack_destroy(ele);
  }

  while(stack_isEmpty(aux) == FALSE) {
    ele = stack_pop(aux);
    stack_push(ps, ele);
    EleStack_destroy(ele);
  }

  media = suma/cont;

  stack_destroy(aux);

  return media;
}

int main(int argc, char const *argv[]) {
  Stack *ps=NULL;
  EleStack *ele=NULL;
  int i, num;
  double media;

  if(argc != 2){
    fprintf(stdout, "Error en el número de argumentos. Sintaxis: %s Número \n", argv[0]);
    return 1;
  }

  ps = stack_ini((P_stack_ele_destroy)EleStack_destroy, (P_stack_ele_copy)EleStack_copy, (P_stack_ele_print)EleStack_print);

  if (ps == NULL) {
    return 1;;
  }

  ele = EleStack_ini();
  if (ele == NULL) {
    stack_destroy(ps);
    return -1;
  }

  num = atoi(argv[1]);

  fprintf(stdout, "Pila antes de la llamada a la función:\n");

  for(i=0; i <= num; i++) {
    EleStack_setInfo(ele, &i);
    stack_push(ps, ele);
  }

  stack_print(stdout, ps);

  media = mediaEnteros(ps);

  fprintf(stdout, "La media es: %.5f\n", media);

  fprintf(stdout, "Pila después de la llamada a la función: \n");

  stack_print(stdout, ps);
  EleStack_destroy(ele);
  stack_destroy(ps);

  return 0;
}
