#include<stdio.h>
#include<stdlib.h>

#ifndef AVL_H
#define AVL_H

typedef struct{
    int roll;
    int value[2]; // value[0] is page number(page_index), value[1] is row number(slot_index)
    Node *left,*right;// left and right pointers for AVL tree structure
} Node;



#endif