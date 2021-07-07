#include <stdio.h>
#include <stdlib.h>

#include "nodo.h"
#include "elestack.h"
#include "stack_fp.h"

int main(int argc, char* argv[]) {
  Node *n1 = NULL;
  EleStack *ele = NULL;
  Stack *ps = NULL;
  int num=0;

  n1 = node_ini();

  if (n1 == NULL) {
    return 1;
  }

  ele = EleStack_ini();

  if (ele == NULL) {
    node_destroy(n1);
    return 1;
  }

  ps = stack_ini((P_stack_ele_destroy)EleStack_destroy, (P_stack_ele_copy)EleStack_copy, (P_stack_ele_print)EleStack_print);
  if (ps == NULL) {
    node_destroy(n1);
    EleStack_destroy(ele);
    return 1;
  }

  n1 = node_setName(n1, "first");
  n1 = node_setId(n1, 111);

  EleStack_setInfo(ele, n1);
  stack_push(ps, ele);

  n1 = node_setName(n1, "second");
  n1 = node_setId(n1, 222);

  EleStack_setInfo(ele, n1);
  stack_push(ps, ele);

  EleStack_destroy(ele);

  fprintf(stdout, "Contenido de la pila: \n");

  num = stack_print(stdout, ps);

  fprintf(stdout, "Caracteres imprimidos: %d\n", num);

  fprintf(stdout, "Vaciando pila. Extracciones:\n");

  while(stack_isEmpty(ps) == FALSE) {
    ele = stack_pop(ps);
    EleStack_print(stdout, ele);
    fprintf(stdout, "\n");
    EleStack_destroy(ele);
  }

  fprintf(stdout, "Contenido de la pila después de vaciar: \n");

  num = stack_print(stdout, ps);

  fprintf(stdout, "Caracteres imprimidos: %d\n", num);

  stack_destroy(ps);
  node_destroy(n1);

  return 0;
}
