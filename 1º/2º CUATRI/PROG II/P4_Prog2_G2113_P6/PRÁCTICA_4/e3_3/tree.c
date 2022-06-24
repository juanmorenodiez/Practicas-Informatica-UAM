/**
 * @brief Define el TAD TREE.
 *
 * @file tree.c
 * @author Camilo Jené Conde y Juan Moreno Diez
 * @version 1.0
 * @date 30-04-2019
 * @copyright GNU Public License
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"

typedef struct _NodeBT {
   void* info;
   struct _NodeBT* left;
   struct _NodeBT* right;
 } NodeBT;


 struct _Tree {
   NodeBT *root;

   destroy_elementtree_function_type destroy_element_function;
   copy_elementtree_function_type copy_element_function;
   print_elementtree_function_type print_element_function;
   cmp_elementtree_function_type cmp_element_function;
 };

 /*funciones privadas*/

 NodeBT* nodebt_ini();
 void nodebt_destroy(NodeBT *pn, Tree *pa);

/**
* @brief Inicializa el nodo del árbol.
* @date 15/04/2019
* @author: Camilo Jené Conde y Juan Moreno Diez
*
* @param 
* @return NodeBT*
*/
 NodeBT* nodebt_ini() {
   NodeBT *pn;

   pn = (NodeBT*)malloc(sizeof(NodeBT));

   if (pn == NULL) {
     return NULL;
   }

   pn->info = pn->left = pn->right = NULL;

   return pn;
 }

 /**
 * @brief Destruye el árbol.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @param Tree*
 * @return
 */
 void nodebt_destroy(NodeBT *pn, Tree *pa) {
   if (pn == NULL) {
     return;
   }

   pa->destroy_element_function(pn->info);
   pn->info = NULL;
   free(pn);
 }

 /*funciones recursivas*/
 void tree_free_rec(NodeBT *pn, Tree *pa);
 NodeBT* tree_insert_rec(NodeBT *pn, const void *po, Tree *pa);
 int tree_depth_rec(NodeBT *pn);
 int tree_numNodes_rec(NodeBT *pn);
 Bool tree_find_rec(NodeBT *pn, const void* pe, Tree *pa);
 Status tree_preOrder_rec(FILE *f, const Tree *pa, NodeBT *pn);
 Status tree_inOrder_rec(FILE *f, const Tree *pa, NodeBT *pn);
 Status tree_postOrder_rec(FILE *f, const Tree *pa, NodeBT *pn);

 /**
 * @brief Función para liberar recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @param Tree*
 * @return
 */
 void tree_free_rec(NodeBT *pn, Tree *pa) {
   if (pn == NULL) {
     return;
   }

   if (pn->left) {
     tree_free_rec(pn->left, pa);
   }

   if (pn->right) {
     tree_free_rec(pn->right, pa);
   }

   nodebt_destroy(pn, pa);
 }

 /**
 * @brief Función para insertar recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @param void*
 * @param Tree*
 * @return NodeBT*
 */
 NodeBT* tree_insert_rec(NodeBT *pn, const void *po, Tree *pa) {
   NodeBT *aux = NULL;
   int cmp = 0;

   if (pn == NULL) {
     pn = nodebt_ini();
     if (pn == NULL) {
       return NULL;
     }

     if ((pn->info = pa->copy_element_function(po)) == NULL) {
       nodebt_destroy(pn, pa);
       return NULL;
     }

     return pn;
   }

   cmp = pa->cmp_element_function(po, pn->info);

   if (cmp < 0) {
     aux = tree_insert_rec(pn->left, po, pa);
     if (aux) {
       pn->left = aux;
       return pn;
     }
     else
     return NULL;
   }

   if (cmp > 0){
     aux = tree_insert_rec(pn->right, po, pa);
     if (aux) {
       pn->right = aux;
       return pn;
     }
     else
     return NULL;
   }

   return NULL;
 }

 /**
 * @brief Función para ver la profundidad recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @return int
 */
 int tree_depth_rec(NodeBT *pn) {
   int right, left;

   if (pn == NULL) {
     return -1;
   }

   left = tree_depth_rec(pn->left);
   right = tree_depth_rec(pn->right);

   if (left > right) {
     return 1 + left;
   }else{
     return 1 + right;
   }
 }

 /**
 * @brief Función para ver el número de nodos recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @return int
 */
 int tree_numNodes_rec(NodeBT *pn) {
   if (pn == NULL) {
     return 0;
   }

   return tree_numNodes_rec(pn->left) + tree_numNodes_rec(pn->right) + 1;
  }

  /**
  * @brief Función para encontrar un nodo recursivamente.
  * @date 15/04/2019
  * @author: Camilo Jené Conde y Juan Moreno Diez
  *
  * @param NodeBT*
  * @param void*
  * @param Tree*
  * @return TRUE
  *         FALSE
  */
  Bool tree_find_rec(NodeBT *pn, const void* pe, Tree *pa) {
    int cmp;

    if (pn == NULL) {
      return FALSE;
    }

    cmp = pa->cmp_element_function(pe, pn->info);

    if (cmp < 0) {
      return tree_find_rec(pn->left, pe, pa);
    }

    else if (cmp > 0) {
      return tree_find_rec(pn->right, pe, pa);
    }

    return TRUE;
  }

 /**
 * @brief Función para recorrer el árbol de forma preorden recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @param void*
 * @param Tree*
 * @return OK
 *         ERROR
 */
  Status tree_preOrder_rec(FILE *f, const Tree *pa, NodeBT *pn) {
    if (f == NULL || pa == NULL || pn == NULL) {
      return ERROR;
    }

    pa->print_element_function(f, pn->info);
    tree_preOrder_rec(f, pa, pn->left);
    tree_preOrder_rec(f, pa, pn->right);

    return OK;
  }

 /**
 * @brief Función para recorrer el árbol de forma enorden recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @param void*
 * @param Tree*
 * @return OK
 *         ERROR
 */
  Status tree_inOrder_rec(FILE *f, const Tree *pa, NodeBT *pn) {
    if (f == NULL || pa == NULL || pn == NULL) {
      return ERROR;
    }

    tree_inOrder_rec(f, pa, pn->left);
    pa->print_element_function(f, pn->info);
    tree_inOrder_rec(f, pa, pn->right);

    return OK;
  }

  /**
 * @brief Función para recorrer el árbol de forma postorden recursivamente.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param NodeBT*
 * @param void*
 * @param Tree*
 * @return OK
 *         ERROR
 */
  Status tree_postOrder_rec(FILE *f, const Tree *pa, NodeBT *pn) {
    if (f == NULL || pa == NULL || pn == NULL) {
      return ERROR;
    }

    tree_postOrder_rec(f, pa, pn->left);
    tree_postOrder_rec(f, pa, pn->right);
    pa->print_element_function(f, pn->info);

    return  OK;
  }

  /*funciones publicas*/

 /**
 * @brief Función para iniciar el árbol.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param 
 * @return Tree*
 */
 Tree* tree_ini(destroy_elementtree_function_type f1, copy_elementtree_function_type f2, print_elementtree_function_type f3, cmp_elementtree_function_type f4) {
   Tree *t;

   t = (Tree*)malloc(sizeof(Tree));

   if (t == NULL) {
     return NULL;
   }

   t->root = NULL;

   t->destroy_element_function = f1;
   t->copy_element_function = f2;
   t->print_element_function = f3;
   t->cmp_element_function = f4;

   return t;
 }

 /**
 * @brief Función para ver si el árbol está vacío.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param Tree*
 * @return TRUE
 *         FALSE
 */
 Bool tree_isEmpty( const Tree *pa) {
   if (pa == NULL) {
     return TRUE;
   }

   if (pa->root == NULL) {
     return TRUE;
   }

   return FALSE;
 }

 /**
 * @brief Función para liberar el árbol
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param Tree*
 * @return
 */
 void tree_free(Tree *pa) {
   if (pa == NULL) {
     return;
   }

   tree_free_rec(pa->root, pa);

   free(pa);
 }

 /**
 * @brief Función para insertar un elemento en el árbol.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param void*
 * @param Tree*
 * @return OK
 *         ERROR
 */
 Status tree_insert(Tree *pa, const void *po) {
   NodeBT *pn;

   if (pa == NULL || po == NULL) {
     return ERROR;
   }

   pn = tree_insert_rec(pa->root, po, pa);

   if (pn == NULL) {
     return ERROR;
   }

   if (pa->root == NULL) {
     pa->root = pn;
   }

   return OK;
 }

 /**
 * @brief Función para ver la profundidad.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param Tree*
 * @return int
 */
 int tree_depth(const Tree *pa) {
   if (pa == NULL) {
     return -1;
   }

   return tree_depth_rec(pa->root);
 }

 /**
 * @brief Función para ver el número de nodos.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param Tree*
 * @return int
 */
 int tree_numNodes(const Tree *pa) {
   if (pa == NULL) {
     return -1;
   }

   return tree_numNodes_rec(pa->root);
 }

 /**
 * @brief Función para encontrar el dato.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param void*
 * @param Tree*
 * @return TRUE
 *         FALSE
 */
 Bool tree_find(Tree* pa, const void* pe) {
   if (pa == NULL || pe == NULL) {
     return FALSE;
   }

   return tree_find_rec(pa->root, pe, pa);
 }

/**
 * @brief Función para recorrer el árbol de forma pOSorden.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param FILE*
 * @param Tree*
 * @return OK
 *         ERROR
 */
Status tree_preOrder(FILE *f, const Tree *pa){
  if(!f || !pa){
    return ERROR;
  }

  if(tree_isEmpty(pa) == TRUE){
    return ERROR;
  }

  return tree_preOrder_rec(f, pa, pa->root);
}

/**
 * @brief Función para recorrer el árbol de forma inorden.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param FILE*
 * @param Tree*
 * @return OK
 *         ERROR
 */
Status tree_inOrder(FILE *f, const Tree *pa){
  if(!f || !pa){
    return ERROR;
  }

  if(tree_isEmpty(pa) == TRUE){
    return ERROR;
  }

  return tree_inOrder_rec(f, pa, pa->root);
}

/**
 * @brief Función para recorrer el árbol de forma preorden.
 * @date 15/04/2019
 * @author: Camilo Jené Conde y Juan Moreno Diez
 *
 * @param FILE*
 * @param Tree*
 * @return OK
 *         ERROR
 */
Status tree_postOrder(FILE *f, const Tree *pa){
  if(!f || !pa){
    return ERROR;
  }

  if(tree_isEmpty(pa) == TRUE){
    return ERROR;
  }

  return tree_postOrder_rec(f, pa, pa->root);
}
