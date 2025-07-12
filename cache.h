#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include "myutils.h"

#ifndef CACHE_H
#define CACHE_H

#define CACHE_SIZE 25 // Maximum number of pages in the cache

typedef struct CacheNode {
    int page_number; 
    Page* page;             
    struct CacheNode* next;
} CacheNode;

CacheNode* insert_page(int page_number, Page* page);
Page* get_page(int page_number);

#endif