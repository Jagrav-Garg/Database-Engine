#include "tree.h"
Node* root=NULL;

Node* create_node(int key,int page,int slot){
    Node* new_node=(Node*)malloc(sizeof(Node));
    new_node->key=key;
    new_node->page_no=page;
    new_node->slot=slot;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->height=1;
    return new_node;
}
int get_height(Node* node)
{
    if(node==NULL) return 0;
    return (node->height);
}
int balance_factor(Node* node)
{
    if(node==NULL) return 0;
    return get_height(node->left)-get_height(node->right);
}
Node* left_rotate(Node* root)
{
    
}
struct Node* index_insert( Node* node,int key,int page,int slot)
{
    if(node==NULL){
        return create_node(key,page,slot);
    }
    if(node->key<key) node->right=index_insert(node->right,key,page,slot);

}
Node* search(Node* root,int key)
{
    if(root==NULL){
        return NULL;
    }
    if(root->key==key) return root;
    else if(root->key<key) return search(root->right,key);
    else return search(root->left,key);
}