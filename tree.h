#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#ifndef AVL_H
#define AVL_H

typedef struct Node{
    int key;
    int page_no;
    int slot;
    struct Node* left;
    struct Node* right;
    int height;
} Node;

void index_insert(int key,int page,int slot);
bool index_find(int64_t key,int* page,int* slot);
void index_delete(int64_t key);
#endif