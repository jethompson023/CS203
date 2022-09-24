/* 
    Jeremiah Thompson
    CS 231: Project 2
    Week 2: April 15th, 2022
*/
//#include "doublyLinkedList.c"
#include "stackADT.h"

listType* create(){
   return listCreate();
}

//This is to take the node data and more it to the top of the stack
listType * push(listType * thisList, dataType data){
    return listInsertAtRear(thisList, data);
}

//This will return and remove data from the top of our stack
dataType pop(listType * thisList){
    struct node* temp = thisList -> last;
    thisList -> last = temp -> previous;
    dataType poppedNode = temp -> element;
    free(temp);
    return poppedNode;
}

dataType peek(listType * thisList){
    return thisList -> last -> element;
}

//Deallocates any and all memory within the Stack
listType * destroy(listType * thisList){
    return freeList(thisList);
}