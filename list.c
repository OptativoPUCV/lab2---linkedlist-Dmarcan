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
  if (lista==NULL)EXIT_FAILURE;
  lista->head=NULL;
  lista->tail=NULL;
  lista->current=NULL;

     return lista;
}

void * firstList(List * list) {
  if (list->head==NULL)return NULL;
  list->current=list->head;
  return list->head->data;
}

void * nextList(List * list) {
  if (list->current==NULL || list->current->next==NULL)return NULL;
  list->current=list->current->next;
  return list->current->data;
  
}

void * lastList(List * list) {
  if (list->tail==NULL)return NULL;
  list->current=list->tail;
  return list->tail->data;
}

void * prevList(List * list) {
  if (list->current==NULL )return NULL;
  list->current=list->current->prev;
  if (list->current==NULL)return NULL;
  return list->current->data;
}

void pushFront(List * list, void * data) {
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
  void * data=list->current->data;
  Node * nodoelimin=list->current;
  
  if (list->current->next==NULL)
  {
    list->tail=list->current->prev;
    list->current->prev->next=NULL;
    list->current=list->current->prev;
    free(nodoelimin);
    return data;
  }
  else
  {
    if (list->current->prev==NULL)
    {
      list->head=list->current->next;
      list->current->next->prev=NULL;
      list->current=list->current->next;
      free(nodoelimin);
      return data;
    }
    else
    {
      list->current->prev->next=list->current->next;
      list->current->next->prev=list->current->prev;
      list->current=list->current->next;
      free(nodoelimin);
      return data;
    }
  }
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}