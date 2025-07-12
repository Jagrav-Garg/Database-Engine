#include "cache.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

CacheNode* head=NULL;
int curr_cache_size=0;

CacheNode* insert_page(int page_number, Page* page){
    if (curr_cache_size==0){ // If cache is empty, create the first node
        head=(CacheNode*)malloc(sizeof(CacheNode));
        if (!head){
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        head->page_number=page_number;
        head->page=page;
        head->next=NULL;
        curr_cache_size++;
        return head;
    }
    else if (curr_cache_size<CACHE_SIZE){ // If cache is not full, insert at the beginning
        CacheNode* new_node=(CacheNode*)malloc(sizeof(CacheNode));
        if (!new_node){
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        new_node->page_number=page_number;
        new_node->page=page;
        new_node->next=head;
        head=new_node;
        curr_cache_size++;
        return head;
    }
    else{ // If cache is full, remove the last node and insert at the beginning
        CacheNode* temp=head;
        CacheNode* prev=NULL;
        while (temp->next){ // Traverse to the last node
            prev=temp;
            temp=temp->next;
        }
        free(temp); // Free the last node
        prev->next=NULL; 
        CacheNode* new_node=(CacheNode*)malloc(sizeof(CacheNode));
        if (!new_node){
            fprintf(stderr, "Memory allocation failed\n");
            return NULL;
        }
        new_node->page_number=page_number;
        new_node->page=page;
        new_node->next=head;
        head=new_node;
        return head;
    }
}

Page* get_page(int page_number){
    CacheNode* temp=head;
    CacheNode* prev=NULL;
    if (curr_cache_size==0){ // If cache is empty, return NULL
        return NULL;
    }
    while (temp){ // Traverse the cache to find the page
        if (temp->page_number==page_number){
            if (prev){  // If the page is not at the head, move it to the head
                prev->next=temp->next;
                temp->next=head; 
                head=temp; 
            }
            return temp->page; // Return the page if found
        }
        prev=temp;
        temp=temp->next;
    }
    return NULL; 
}


        

            
    