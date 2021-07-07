#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "types.h"
#include "list.h"

typedef struct _NodeList{
	void* info;
	struct _NodeList *next;
}NodeList;

struct _List {
	NodeList *last;

	destroy_element_function_type destroy_element_function;
	copy_element_function_type copy_element_function;
	print_element_function_type print_element_function;
	cmp_element_function_type cmp_element_function;
};

NodeList* nodelist_ini();
void nodelist_destroy(NodeList* nodelist);

NodeList* nodelist_ini(){
	NodeList* pn = NULL;

	pn = (NodeList*) malloc (sizeof(NodeList));

	if(!pn){
		return NULL;
	}

	pn->info = NULL;
	pn->next = NULL;

	return pn;
}

void nodelist_destroy(NodeList* nodelist){
	if(nodelist != NULL){
		free(nodelist->info);
		free(nodelist);
	}
}

void list_destroy(List* list) {
	if (list == NULL) {
		return;
	}

	while (list_isEmpty(list) == FALSE) {
		list->destroy_element_function(list_extractFirst(list));
	}

	free(list);
}



Status list_insertLast (List* list, const void *pelem){
	NodeList* pn = NULL, *qn = NULL;

	if(!list || !pelem){
		return ERROR;
	}

	pn = nodelist_ini();

	if(!pn){
		return ERROR;
	}

	pn->info = list->copy_element_function(pelem);

	if(!pn->info){
		nodelist_destroy(pn);
		return ERROR;
	}

	if(list_isEmpty(list) == TRUE){
		list->last = pn;
		return OK;
	}

	qn = list->last;
	while (qn->next != NULL) {
		qn = qn->next;
	}

	qn->next = pn;

	return OK;
}

void* list_extractFirst(List* list){
	NodeList* pn = NULL;
	void *pe = NULL;

	if(!list || list_isEmpty(list) == TRUE){
		return NULL;
	}

	pn = list->last;
	pe = pn->info;
	pn->info = NULL;

	list->last = pn->next;

	nodelist_destroy(pn);

	return pe;
}

Bool list_isEmpty(const List* list){
	if (list == NULL) {
		return TRUE;
	}

	if(list->last == NULL) {
		return TRUE;
	}

	return FALSE;
}

int list_size (const List* list){
  NodeList* pn = NULL;
	int cantidad = 0;

	if(!list){
		return -1;
	}

	if(list_isEmpty(list) == TRUE){
		return cantidad;
	}else{
		for(pn = list->last, cantidad = 1; pn->next != NULL ; pn = pn->next){
			cantidad++;
      printf("Bucle correcto\n");
		}
    printf("Sale del bucle bien\n");
	}
	return cantidad;
}

/* ---------------------------------------------------------------------------------------------------- */

List* list_ini (destroy_element_function_type f1, copy_element_function_type f2, print_element_function_type f3, cmp_element_function_type f4){
  List *pl;

  pl = (List*)malloc(sizeof(List));

  if (pl == NULL) {
    return NULL;
  }

  pl->last = NULL;

  pl->destroy_element_function = f1;
  pl->copy_element_function = f2;
  pl->print_element_function = f3;
  pl->cmp_element_function = f4;

  return pl;
}

Status list_insertFirst (List* list, const void *pelem) {
  NodeList *nl = NULL;

  if (list == NULL || pelem == NULL) {
    return ERROR;
  }

  nl = nodelist_ini();

  if (nl == NULL) {
    return ERROR;
  }

  nl->info = list->copy_element_function(pelem);

  if (nl->info == NULL) {
    nodelist_destroy(nl);
    return ERROR;
  }

  nl->next = list->last;
  list->last = nl;

  return OK;
}

Status list_insertInOrder (List *list, const void *pelem) {
  NodeList *nl = NULL, *nl1 = NULL, *nl2 = NULL;

  if (list == NULL|| pelem == NULL) {
    return ERROR;
  }

  nl = nodelist_ini();

  if (nl == NULL) {
    return ERROR;
  }

  nl->info = list->copy_element_function(pelem);

  if (!list->last) {
    list->last = nl;
    return OK;
  }

  if(list->cmp_element_function(nl->info, list->last->info) < 0) {
    nl->next = list->last;
    list->last = nl;
    return OK;
  }

  nl1 = nl->next;
  nl2 = list->last;

  while (nl1) {
    if (list->cmp_element_function(nl->info, nl1->info) < 0) {
      nl2->next = nl;
      nl->next = nl1;
      return OK;
    }

    nl1 = nl1->next;
    nl2 = nl2->next;
  }

  if (!nl1) {
    nl2->next = nl1;
    return OK;
  }

  return ERROR;
}

void * list_extractLast (List* list) {
  NodeList *nl = NULL;
  void * elem = NULL;

  if (list == NULL || list_isEmpty(list) == TRUE) {
    return NULL;
  }

	if (!list->last->next) {
		elem = list->last->info;
		list->last->info = NULL;
		nodelist_destroy(list->last);
		list->last = NULL;
		return elem;
	}

	nl = list->last;
	while (nl->next->next != NULL) {
		nl = nl->next;
	}

	elem = nl->next->info;
	list->last->info = NULL;
	nodelist_destroy(nl->next);
	nl->next = NULL;

	return elem;
}

const void* list_get (const List* list, int index) {
  NodeList *nl = NULL;
  int i = 1;

  if (list == NULL || i <= 0) {
    return NULL;
  }

  if (list_isEmpty(list) == TRUE) {
    return NULL;
  }

  nl = list->last;

  while (nl->next) {
    nl = nl->next;
    i++;

    if (i == index) {
      return nl;
    }
  }

  return NULL;
}

int list_print(FILE *fd, const List* list) {
  int bytes = 0;
  NodeList *pl = NULL;

  if (fd == NULL || list == NULL) {
    return -1;
  }

  if (list_isEmpty(list) == TRUE) {
    return bytes;
  }

  pl = list->last;

  while (pl) {
    bytes += list->print_element_function(fd, pl->info);
    pl = pl->next;
  }

  return bytes;
}
