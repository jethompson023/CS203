/* 
    Jeremiah Thompson
    CS 231: Project 2
    Week 2: April 15th, 2022
*/

#include <stdio.h>
#include <stdlib.h>
#define BAD_EXIT 1
 
//#include "myCharType.h"
#include "myDoubleType.h"

typedef struct node{
  struct node *next;
  struct node *previous;
  dataType element;
} nodeType;

typedef struct listHeader{
  struct node *first;
  struct node *last;
}listType;

listType *listCreate();
listType * create();
listType * push(listType *, dataType);
dataType pop(listType *);
dataType peek(listType *);
listType * destroy(listType *);
listType *listInsertAtRear(listType *, dataType);
void printList(listType *);
int isEmpty(listType *);
listType * freeList(listType *);