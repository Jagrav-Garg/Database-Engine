#include "tree.h"
Node* root=NULL;

Node* create_node(int key,int page,int slot){
    Node* new_node=(Node*)malloc(sizeof(Node));
    if (new_node == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    new_node->key=key;
    new_node->page_no=page;
    new_node->slot=slot;
    new_node->left=NULL;
    new_node->right=NULL;
    new_node->height=1;
    return new_node;
}
int max(int a,int b)
{
    return (a>b)?a:b;
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
Node* right_rotate(Node* root)
{
    Node* new_root=root->left;
    Node* temp=new_root->right;

    new_root->right=root;
    root->left=temp;

    root->height=1+max(get_height(root->left),get_height(root->right));
    new_root->height=1+max(get_height(new_root->left),get_height(new_root->right));

    return new_root;
}
Node* left_rotate(Node* root)
{
    Node* new_root=root->right;
    Node* temp=new_root->left;

    new_root->left=root;
    root->right=temp;

    new_root->height=1+max(get_height(new_root->left),get_height(new_root->right));
    root->height=1+max(get_height(root->left),get_height(root->right));

    return new_root;
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
void index_insert(Node** node, int key, int page, int slot)
{
    if(*node==NULL) {
        *node =create_node(key,page,slot);//in case the passed adress contains null, make a new node
        return;
    }
    if((*node)->key<key) index_insert(&((*node)->right),key,page,slot);
    else if(key<(*node)->key) index_insert(&((*node)->left),key,page,slot);
    else return;//if key already exists then do nothing, eat 5 star


    (*node)->height=1+max(get_height((*node)->left),get_height((*node)->right));//update the heights accordingly

    int balance=balance_factor(*node);
    if(balance>1 && key<(*node)->left->key)// this is the left left case 
    {
        *node=right_rotate(*node);
    }
    else if(balance<-1 && key>(*node)->right->key)// this is right right case
    {
        *node=left_rotate(*node);
    }
    else if(balance>1 && key>(*node)->left->key)// this is left right case
    {
        (*node)->left=left_rotate((*node)->left);// left rotate to bring it to left left case
        *node=right_rotate(*node);
    }
    else if(balance<-1 && key<(*node)->right->key)// this is right left case
    {
        (*node)->right=right_rotate((*node)->right);// first right rotate to being it to right right case
        *node=left_rotate(*node);// now do left roataion
    }
    return;
}
// void print_backened_test(Node* root)
// {
//     if(root==NULL) return;
//     printf("%d ",root->key);
//     print_backend_test(root->left);
//     print_backend_test(root->right);
// }