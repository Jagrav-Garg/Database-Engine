#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>

#ifndef TREE_H
#define TREE_H

typedef struct Node{
    int key;
    int page_no;
    int slot;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

void index_insert(Node** node,int key,int page,int slot);
bool index_find(int key,int* page,int* slot);
void index_delete(int key);
// void print_backend_test(Node* root);
#endif