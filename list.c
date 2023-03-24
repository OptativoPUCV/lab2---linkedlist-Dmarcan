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
  List * lista =(List *)malloc(sizeof(List));
  lista->head=NULL;
  lista->tail=NULL;
  lista->current=NULL;

     return lista;
}

void * firstList(List * list) {
  //La primera retorna el dato del primer nodo de la lista (`head`)
  //y actualiza el current para que apunte a ese nodo. 
  
  if (list->head==NULL)return NULL;
  list->current=list->head;
  return list->head->data;
}

void * nextList(List * list) {
  /*La segunda función retorna el dato del nodo a continuación del current y actualiza el current para que apunte a ese nodo.
    */
  if (list->current==NULL || list->current->next==NULL)return NULL;
  list->current=list->current->next;
  return list->current->data;
  
}

void * lastList(List * list) {
  /* La primera retorna el dato del último elemento en la lista y actualiza el current al nodo correspondiente.
*/
  if (list->tail==NULL)return NULL;
  list->current=list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  /*La segunda función retorna el dato del nodo anterior a current y actualiza el current para que apunte a ese nodo.
    */
  if (list->current==NULL )return NULL;
  list->current=list->current->prev;
  if (list->current==NULL)return NULL;
  return list->current->data;
}

void pushFront(List * list, void * data) {
  /*Programe la función `void pushFront(List * list, void * data)`, la cual agrega un dato al comienzo de la lista. 
> Puede utilizar la función `Node* createNode(void * data)` la cual crea, incializa y retorna un nodo con el dato correspondiente. 
    */
  Node * nodo=createNode(data);
  if(list->head==NULL)
  {
    list->head=nodo;
    list->tail=nodo;
  }
  else
  {
    list->head->prev=nodo;
    nodo->next=list->head;
    list->head=nodo;
  }
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
/*
Programe la función `void pushCurrent(List * list, void* data)`, la cual agrega un dato a continuación del nodo apuntado por `list->current`.
*/
  Node * nodo=createNode(data);
  if (list->current->next==NULL)
  {
    list->current->next=nodo;
    nodo->next=NULL;
    nodo->prev=list->current;
    list->tail=nodo;
  }
  else
  {
    nodo->next=list->current->next;
    list->current->next->prev=nodo;
    nodo->prev=list->current;
    list->current->next=nodo;
    
  }
}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void * popCurrent(List * list) {
  /*Programe la función `void* popCurrent(List * list)`, la cual elimina el nodo que está en la posición del current de la lista enlazada, y además retorna el **dato** del nodo eliminado.
> **Nota**: El current debe quedar apuntando al nodo siguiente del eliminado.
    */
  void * data=list->current->data;
  Node * nodoelimin=list->current;
  
  if (list->current->next==NULL)
  {
    list->tail=list->current->prev;
    list->current->prev->next=NULL;
    free(nodoelimin);
    list->current=list->current->prev;
    return data;
  }
  else
  {
    if (list->current->prev==NULL)
    {
      list->head=list->current->next;
      list->current->next->prev=NULL;
      free(nodoelimin);
      list->current=list->current->next;
      return data;
    }
    else
    {
      list->current->prev->next=list->current->next;
      list->current->next->prev=list->current->prev;
      free(nodoelimin);
      list->current=list->current->next;
      return data;
      
    }
  }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}