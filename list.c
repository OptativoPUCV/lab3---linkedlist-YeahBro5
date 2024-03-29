#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
  List* lista = (List*)malloc(sizeof(List));
  if (lista == NULL)
  {
    return NULL;
  }
  lista->head = NULL;
  lista->tail = NULL;
  lista->current = NULL;
  
  return lista;
}

void * firstList(List * list) {
  if (list == NULL || list -> head == NULL)
  {
    return NULL;
  }
  list->current = list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if (list == NULL || list -> current == NULL || list->current->next == NULL)
  {
    return NULL;
  }
  
  list->current = list->current->next;
  return list->current->data;
}

void * lastList(List * list) {
  if (list == NULL  || list->tail == NULL)
  {
    return NULL;
  }

  list->current = list->tail;
  return list->tail->data;

}

void * prevList(List * list) {
  
  if (list == NULL || list->current == NULL || list->current->prev == NULL)
  {
      return NULL;
  }

  list->current = list->current->prev;
  return list->current->data;
}

void pushFront(List * list, void * data) {
 
  Node * nuevoNodo = createNode(data);
  if (list->head == NULL)
  {
    list->head = nuevoNodo;
  }
  else
  {
    nuevoNodo->next = list->head;
    list->head->prev = nuevoNodo;
    list->head = nuevoNodo;
  }

  if (list->tail == NULL)
  {
    list->tail = nuevoNodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
  if (list == NULL)
  {
    return;
  }
  
  Node* nuevoNodo = (Node *)malloc(sizeof(Node));
  nuevoNodo->data = data;
  nuevoNodo->next = list->current->next;
  nuevoNodo->prev = list->current;

  if (list->current->next == NULL)
  {
    list->tail = nuevoNodo;
  }
  else
  {
    list->current->next->prev = nuevoNodo;
  }
  list->current->next = nuevoNodo;
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) 
{

  //if (list == NULL || list->current == NULL)
  //{
    //return;
  //}

  if (list->current->prev == NULL)
  {
    list->head = list->current->next;
    list->current->next->prev = NULL;
  }

  if (list->current->next == NULL)
  {
    list->tail = list->current->prev;
    list->current->prev->next = NULL;
  }
  else
  {
    list->current->prev->next = list->current->next;
    list->current->next->prev = list->current->prev;
    
  }


  free(list->current);

}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}