#include <stdio.h>
#include "stack_elestack.h"
#include "nodo.h"

int main(int argc, char const *argv[]) {
  Node *n1 = NULL;
  EleStack *ele = NULL;
  Stack *ps = NULL;
  int num=0;

  /* INICIALIZA EL NODO n1 */
  n1 = node_ini();

  if (n1 == NULL) {
    return 1;
  }

/* INICIALIZA EL ELEMENTO ele */
  ele = EleStack_ini();

  if (ele == NULL) {
    node_destroy(n1);
    return 1;
  }

  /* INICIALIZA LA PILA ps */
  ps = stack_ini();

  if (ps == NULL) {
    node_destroy(n1);
    EleStack_destroy(ele);
    return 1;
  }

  /* ASIGNA EL NOMBRE Y LA ID DEL NODO Y LO INTRODUCE AL ELEMENTO PARA INTRODUCIRLO EN LA PILA */
  n1 = node_setName(n1, "first");
  n1 = node_setId(n1, 111);

  EleStack_setInfo(ele, n1);
  stack_push(ps, ele);

  n1 = node_setName(n1, "second");
  n1 = node_setId(n1, 222);

  EleStack_setInfo(ele, n1);
  stack_push(ps, ele);

  EleStack_destroy(ele);

  /* IMPRIME EL CONTENIDO DE LA PILA Y LOS CARÁCTERES */
  fprintf(stdout, "Contenido de la pila:");

  num = stack_print(stdout, ps);

  fprintf(stdout, "Caracteres impresos: %d\n", num);

  fprintf(stdout, "Vaciando pila. Extracciones:\n");

  while(stack_isEmpty(ps) == FALSE) {
    ele = stack_pop(ps);
    num = EleStack_print(stdout, ele);
    fprintf(stdout, "\n");
    EleStack_destroy(ele);
  }

  fprintf(stdout, "Contenido de la pila después de vaciar: \n");

  num = stack_print(stdout, ps);

  fprintf(stdout, "Caracteres impresos: %d\n", num);

  /* DESTRUYE TODO LA RESERVA DE MEMORIA HECHA DURANTE LA EJECUCIÓN DEL PROGRAMA */
  node_destroy(n1);
  stack_destroy(ps);


  return 0;


}
